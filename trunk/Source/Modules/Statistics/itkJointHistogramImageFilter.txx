/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkJointHistogramImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkJointHistogramImageFilter_txx
#define __itkJointHistogramImageFilter_txx

#include "itkJointHistogramImageFilter.h"
#include "itkJoinImageFilter.h"
#include "itkMinimumMaximumImageCalculator.h"
#include "itkGradientMagnitudeImageFilter.h"
#include "itkImageToHistogramGenerator.h"
#include "itkScalarImageToHistogramGenerator.h"
#include "itkHistogramToImageFilter.h"
#include "itkHistogramToIntensityImageFilter.h"
#include "itkHistogramToProbabilityImageFilter.h"
#include "itkHistogramToLogProbabilityImageFilter.h"
#include "itkHistogramToEntropyImageFilter.h"
#include "itkCastImageFilter.h"

namespace itk
{

/**
 * Constructor
 */
template <class TInputImage, class TOutputImage>
JointHistogramImageFilter<TInputImage, TOutputImage>
::JointHistogramImageFilter()
{
  this->SetNumberOfRequiredInputs( 2 );
  this->m_NumberOfBins = NumberOfBinsType( 2 );
  this->m_NumberOfBins.Fill( 256 );
  this->m_MarginalScale = 2.0;
  this->m_Mapping = Self::LogProbability;
}

/**
 * Standard PrintSelf method.
 */
template <class TInputImage, class TOutputImage>
void
JointHistogramImageFilter<TInputImage, TOutputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "NumberOfBins: " << m_NumberOfBins << std::endl;
  os << indent << "MarginalScale: " << m_MarginalScale << std::endl;
  os << indent << "Mapping: ";
  switch (m_Mapping)
    {
    case Self::Intensity: os << "Intensity";
    case Self::Entropy: os << "Entropy";
    case Self::Probability: os << "Probability";
    case Self::LogProbability: os << "LogProbability";
    }
  os << std::endl;
}

template <class TInputImage, class TOutputImage>
void
JointHistogramImageFilter<TInputImage,TOutputImage>
::GenerateInputRequestedRegion()
{
  Superclass::GenerateInputRequestedRegion();
  unsigned int numInputs =
    static_cast<unsigned int>(this->GetNumberOfValidRequiredInputs());
  for (unsigned int i=0; i<numInputs; i++)
    {
    if ( this->GetInput(i) )
      {
      InputImagePointer input =
        const_cast< InputImageType * >( this->GetInput(i) );
      input->SetRequestedRegionToLargestPossibleRegion();
      }
    }
}

template <class TInputImage, class TOutputImage>
void
JointHistogramImageFilter<TInputImage,TOutputImage>
::GenerateOutputInformation()
{
  typename OutputImagePointer outputPtr = this->GetOutput();

  if ( !outputPtr)
    {
    return;
    }
    
  // Get the size
  OutputSizeType outputSize;
  outputSize[0] = m_NumberOfBins[0];
  outputSize[1] = m_NumberOfBins[1];

  // Get the spacing and origin
  OutputImageType::SpacingType outputSpacing;
  outputSpacing.Fill( 1.0 );
  OutputImageType::PointType outputOrigin;
  outputOrigin.Fill( 0.0 );

  // Setup the output
  OutputImageRegionType outputRegion;
  outputRegion.SetSize( outputSize );
  outputPtr->SetRegions( outputRegion );
  outputPtr->SetSpacing( outputSpacing );
  outputPtr->SetOrigin( outputOrigin );
}

template <class TInputImage, class TOutputImage>
void
JointHistogramImageFilter<TInputImage,TOutputImage>
::EnlargeOutputRequestedRegion(DataObject *output)
{
  Superclass::EnlargeOutputRequestedRegion( output );
  output->SetRequestedRegionToLargestPossibleRegion();
}

template <class TInputImage, class TOutputImage>
void
JointHistogramImageFilter<TInputImage,TOutputImage>
::GenerateData()
{
  unsigned int numInputs =
    static_cast<unsigned int>(this->GetNumberOfValidRequiredInputs());

  if ( numInputs != 2 )
    {
    itkExceptionMacro("The number of inputs must be 2, " <<
                       numInputs << " provided.");
    }
    
  // Join the inputs
  this->SetProgress( 0.0f );
  typedef itk::JoinImageFilter< TInputImage, TInputImage > JoinFilterType;
  typedef JoinFilterType::OutputImageType JoinOutputImageType;
  JoinFilterType::Pointer joinFilter = JoinFilterType::New();
  for (unsigned int i=0; i<numInputs; i++)
    {
     joinFilter->SetInput( i, this->GetInput(i) );
    }
  joinFilter->Update();
  
  // Generate the histogram
  this->SetProgress( 0.33f );
  typedef itk::Statistics::ImageToHistogramGenerator< JoinOutputImageType >
    HistogramGeneratorType;
  typedef HistogramGeneratorType::SizeType SizeType;
  typedef HistogramGeneratorType::HistogramType HistogramType;
  HistogramGeneratorType::Pointer generator = HistogramGeneratorType::New();
  generator->SetInput( joinFilter->GetOutput() );
  if ( SizeType::GetSizeDimension() != m_NumberOfBins.Size() )
    {
    itkExceptionMacro("The number of bins does not match the number of inputs. " <<
                      "Expected " << SizeType::GetSizeDimension() <<
                       " bins, but got " << m_NumberOfBins.Size());
    }

  SizeType size;
  for (unsigned int i=0; i<numInputs; i++)
    {
    size[i] = m_NumberOfBins[i];
    }
  generator->SetNumberOfBins( size );
  generator->SetMarginalScale( m_MarginalScale );
  //generator->SetHistogramMin(  -0.5 );
  //generator->SetHistogramMax( 255.5 );
  generator->Compute();
  const HistogramType * histogram = generator->GetOutput();

  // Setup the output (it must have the same size as the histogram) 
  OutputImagePointer output = this->GetOutput();
  OutputImageRegionType outputRegion( histogram->GetSize() );
  output->SetRegions( outputRegion );
  output->Allocate();

  // Convert the histogram to an image
  this->SetProgress( 0.66f );
  if (m_Mapping == Self::Intensity)
    {
    typedef HistogramToIntensityImageFilter< HistogramType >
		HistogramToImageFilterType;
    typedef CastImageFilter< HistogramToImageFilterType::OutputImageType, TOutputImage >
		CastFilterType;
    HistogramToImageFilterType::Pointer filterHistogramToImage = 
		HistogramToImageFilterType::New();
    CastFilterType::Pointer filterCast = CastFilterType::New();
    filterHistogramToImage->SetInput( histogram );
	filterHistogramToImage->Update( );
    filterCast->SetInput( filterHistogramToImage->GetOutput() );
    filterCast->GraftOutput( output );
    filterCast->Update( );
    }
  else if (m_Mapping == Self::Entropy)
    {
    typedef HistogramToEntropyImageFilter< HistogramType >
		HistogramToImageFilterType;
    typedef CastImageFilter< HistogramToImageFilterType::OutputImageType, TOutputImage >
		CastFilterType;
    HistogramToImageFilterType::Pointer filterHistogramToImage = 
		HistogramToImageFilterType::New();
    CastFilterType::Pointer filterCast = CastFilterType::New();
    filterHistogramToImage->SetInput( histogram );
	filterHistogramToImage->Update( );
    filterCast->SetInput( filterHistogramToImage->GetOutput() );
    filterCast->GraftOutput( output );
    filterCast->Update( );
    }
  else if (m_Mapping == Self::Probability)
    {
    typedef HistogramToProbabilityImageFilter< HistogramType >
		HistogramToImageFilterType;
    typedef CastImageFilter< HistogramToImageFilterType::OutputImageType, TOutputImage >
		CastFilterType;
    HistogramToImageFilterType::Pointer filterHistogramToImage = 
		HistogramToImageFilterType::New();
    CastFilterType::Pointer filterCast = CastFilterType::New();
    filterHistogramToImage->SetInput( histogram );
	filterHistogramToImage->Update( );
    filterCast->SetInput( filterHistogramToImage->GetOutput() );
    filterCast->GraftOutput( output );
    filterCast->Update( );
    }
  else if (m_Mapping == Self::LogProbability)
    {
    typedef HistogramToLogProbabilityImageFilter< HistogramType >
		HistogramToImageFilterType;
    typedef CastImageFilter< HistogramToImageFilterType::OutputImageType, TOutputImage >
		CastFilterType;
    HistogramToImageFilterType::Pointer filterHistogramToImage = 
		HistogramToImageFilterType::New();
    CastFilterType::Pointer filterCast = CastFilterType::New();
    filterHistogramToImage->SetInput( histogram );
	filterHistogramToImage->Update( );
	HistogramToImageFilterType::OutputImageType::Pointer histOutput = filterHistogramToImage->GetOutput();
    filterCast->SetInput( filterHistogramToImage->GetOutput() );
    filterCast->GraftOutput( output );
    filterCast->Update( );
    }

  // Graft output
  this->GraftOutput( output );
  this->SetProgress( 1.00f );
}

} // end namespace itk

#endif
