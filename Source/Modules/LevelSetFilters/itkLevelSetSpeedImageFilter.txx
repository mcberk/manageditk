/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkLevelSetSpeedImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkLevelSetSpeedImageFilter_txx
#define __itkLevelSetSpeedImageFilter_txx

#include "itkLevelSetSpeedImageFilter.h"
#include "itkProgressAccumulator.h"
#include "itkNumericTraits.h"
#include "itkGradientMagnitudeRecursiveGaussianImageFilter.h"
#include "itkSigmoidImageFilter.h"
#include "itkRescaleIntensityImageFilter.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkMaskImageFilter.h"

namespace itk {

template <class TInputImage, class TOutputImage>
LevelSetSpeedImageFilter<TInputImage, TOutputImage>
::LevelSetSpeedImageFilter()
{
  this->ProcessObject::SetNumberOfRequiredInputs( 1 );

  m_GaussianNormalizeAcrossScale = false;
  m_GaussianSigma = 1.0;
  m_SigmoidAlpha = -1.0;
  m_SigmoidBeta = 1.0;
  m_ThresholdLower = -1000.0;
  m_ThresholdUpper = 1000.0;
  m_OutputMinimum = -1.0;
  m_OutputMinimum = 1.0;
}

template <class TInputImage, class TOutputImage>
void
LevelSetSpeedImageFilter<TInputImage, TOutputImage>
::GenerateInputRequestedRegion()
{
  // Call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();
  
  // We need all the input
  InputImagePointer input = const_cast<InputImageType *>(this->GetInput());
  if ( input )
    input->SetRequestedRegion( input->GetLargestPossibleRegion() );
}


template <class TInputImage, class TOutputImage>
void 
LevelSetSpeedImageFilter<TInputImage, TOutputImage>
::EnlargeOutputRequestedRegion(DataObject *)
{
  // We need all the output
  this->GetOutput()->SetRequestedRegion( this->GetOutput()->GetLargestPossibleRegion() );
}


template<class TInputImage, class TOutputImage>
void
LevelSetSpeedImageFilter<TInputImage, TOutputImage>
::GenerateData()
{
  // Filter typedefs
  typedef GradientMagnitudeRecursiveGaussianImageFilter<TInputImage, TOutputImage>
    GradientFilterType;
  typedef SigmoidImageFilter<TOutputImage, TOutputImage>
    SigmoidFilterType;
  typedef RescaleIntensityImageFilter<TOutputImage, TOutputImage>
    RescaleFilterType;
  typedef BinaryThresholdImageFilter<TInputImage, TOutputImage>
    ThresholdFilterType;
  typedef MaskImageFilter<TOutputImage, TOutputImage, TOutputImage>
    MaskFilterType;

  // Allocate the output
  this->AllocateOutputs( );
  
  // Get the inputs and outputs
  InputImagePointer input = (InputImageType*)this->GetInput( );
  OutputImagePointer output = (OutputImageType*)this->GetOutput( );

  // Setup the progress accumulator
  ProgressAccumulator::Pointer progress = ProgressAccumulator::New ();
  progress->SetMiniPipelineFilter( this );
  progress->ResetProgress( );

  // Create filters
  GradientFilterType::Pointer filterGrad = GradientFilterType::New( );
  SigmoidFilterType::Pointer filterSigmoid = SigmoidFilterType::New( );
  RescaleFilterType::Pointer filterRescale = RescaleFilterType::New( );
  ThresholdFilterType::Pointer filterThreshold = ThresholdFilterType::New( );
  MaskFilterType::Pointer filterMask = MaskFilterType::New( );

  // Register filters with progress accumulator
  progress->RegisterInternalFilter( filterGrad, 0.6f );
  progress->RegisterInternalFilter( filterSigmoid, 0.1f );
  progress->RegisterInternalFilter( filterRescale, 0.1f );
  progress->RegisterInternalFilter( filterThreshold, 0.1f );
  progress->RegisterInternalFilter( filterMask, 0.1f );

  // Setup pipeline
  filterGrad->SetInput( input );
  filterSigmoid->SetInput( filterGrad->GetOutput() );
  filterRescale->SetInput( filterSigmoid->GetOutput() );
  filterThreshold->SetInput( input );
  filterMask->SetInput1( filterRescale->GetOutput() );
  filterMask->SetInput2( filterThreshold->GetOutput() );
  
  // We can release the data as the pipeline executes
  filterGrad->ReleaseDataFlagOn();
  filterSigmoid->ReleaseDataFlagOn();
  filterRescale->ReleaseDataFlagOn();
  filterThreshold->ReleaseDataFlagOn();

  // Setup filter parameters
  filterGrad->SetNormalizeAcrossScale( m_GaussianNormalizeAcrossScale );
  filterGrad->SetSigma( m_GaussianSigma );
  filterSigmoid->SetAlpha( m_SigmoidAlpha );
  filterSigmoid->SetBeta( m_SigmoidBeta );
  filterRescale->SetOutputMinimum( m_OutputMinimum );
  filterRescale->SetOutputMaximum( m_OutputMaximum );
  filterThreshold->SetLowerThreshold( m_ThresholdLower );
  filterThreshold->SetUpperThreshold( m_ThresholdUpper );
  filterThreshold->SetOutsideValue( NumericTraits<OutputImagePixelType>::Zero );
  filterThreshold->SetInsideValue( NumericTraits<OutputImagePixelType>::One );
  filterMask->SetOutsideValue( m_OutputMinimum );

  // Update the mini-pipeline
  filterMask->GraftOutput( this->GetOutput() );
  filterMask->Update( );
  this->GraftOutput( filterMask->GetOutput() );
  progress->UnregisterAllFilters( );
  this->SetProgress( 1.0f );
}


template<class TInputImage, class TOutputImage>
void
LevelSetSpeedImageFilter<TInputImage, TOutputImage>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);

  os << indent << "GaussianNormalizeAcrossScale: ";
  os << m_GaussianNormalizeAcrossScale  << std::endl;
  os << indent << "SigmoidAlpha: "   << m_SigmoidAlpha   << std::endl;
  os << indent << "SigmoidBeta: "    << m_SigmoidBeta    << std::endl;
  os << indent << "ThresholdLower: " << m_ThresholdLower << std::endl;
  os << indent << "ThresholdUpper: " << m_ThresholdUpper << std::endl;
  os << indent << "OutputMinimum: "  << m_OutputMinimum  << std::endl;
  os << indent << "OutputMaximum: "  << m_OutputMaximum  << std::endl;
}
  
}// end namespace itk
#endif
