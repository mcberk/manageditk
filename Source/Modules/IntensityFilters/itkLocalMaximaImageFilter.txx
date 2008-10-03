/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkLocalMaximaImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkLocalMaximaImageFilter_txx
#define __itkLocalMaximaImageFilter_txx

#include "itkLocalMaximaImageFilter.h"
#include "itkProgressReporter.h"
#include "itkNumericTraits.h"
#include "itkImageRegionIterator.h"
#include "itkConstShapedNeighborhoodIterator.h"
#include "itkConnectedComponentAlgorithm.h"
#include "itkConstantBoundaryCondition.h"
#include "itkMinimumMaximumImageCalculator.h"

namespace itk {

template <class TInputImage, class TOutputImage>
LocalMaximaImageFilter<TInputImage, TOutputImage>
::LocalMaximaImageFilter()
{
  m_FullyConnected = false;
  m_ForegroundValue = NumericTraits<OutputImagePixelType>::max();
  m_BackgroundValue = NumericTraits<OutputImagePixelType>::NonpositiveMin();
}

template <class TInputImage, class TOutputImage>
void
LocalMaximaImageFilter<TInputImage, TOutputImage>
::GenerateInputRequestedRegion()
{
  // Call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();
  
  // We need all the input
  InputImagePointer input = 
    const_cast<InputImageType *>(this->GetInput());
  if ( input )
    input->SetRequestedRegion( input->GetLargestPossibleRegion() );
}


template <class TInputImage, class TOutputImage>
void 
LocalMaximaImageFilter<TInputImage, TOutputImage>
::EnlargeOutputRequestedRegion(DataObject *)
{
  // We need all the output
  this->GetOutput()->SetRequestedRegion
    ( this->GetOutput()->GetLargestPossibleRegion() );
}


template<class TInputImage, class TOutputImage>
void
LocalMaximaImageFilter<TInputImage, TOutputImage>
::GenerateData()
{
  typedef MinimumMaximumImageCalculator< InputImageType > MinMaxCalculatorType;
  typedef ConstShapedNeighborhoodIterator< InputImageType > InputIterator;
  typedef ImageRegionIterator< OutputImageType > OutputIterator;

  // Allocate the output
  this->AllocateOutputs();

  // Setup the progress reporter
  ProgressReporter progress( this, 0, 
    this->GetOutput()->GetRequestedRegion().GetNumberOfPixels() );

  // Compute the minimum in the input image
  // NOTE: We ensure that the minimum can not be a local maxima,
  //       therefore "flat" images will not have any maxima.
  MinMaxCalculatorType::Pointer calc = MinMaxCalculatorType::New();
  calc->SetImage( this->GetInput() );
  calc->ComputeMinimum();
  InputImagePixelType minimumValueInInput = calc->GetMinimum();

  // Setup the input neighbourhood iterator
  Size< ImageDimension > kernelRadius;
  kernelRadius.Fill(1);
  InputIterator nitIn( kernelRadius,
                       this->GetInput(),
                       this->GetOutput()->GetRequestedRegion() );
  setConnectivity( &nitIn, m_FullyConnected );

  // Override the boundary condition
  // NOTE: This means that no border pixels will be local maxima
  ConstantBoundaryCondition< InputImageType > bcIn;
  bcIn.SetConstant( NumericTraits< InputImagePixelType >::max() );
  nitIn.OverrideBoundaryCondition( &bcIn );

  // Iterate over input and output
  OutputIterator itOut(this->GetOutput(), 
                       this->GetOutput()->GetRequestedRegion() );
  for( itOut.GoToBegin(), nitIn.GoToBegin();
      !itOut.IsAtEnd();
      ++itOut, ++nitIn )
    {
    // Assume center is a local
    bool centerIsLocal = true;
    typename InputIterator::ConstIterator nitN;
    for ( nitN = nitIn.Begin(); !nitN.IsAtEnd(); ++nitN )
      {
      InputImagePixelType center = nitIn.GetCenterPixel();
      if ( center == minimumValueInInput || nitN.Get() > center )
        {
        // Center is not local, flag and break
        centerIsLocal = false;
        break;
        }
      }

    // Set output value
    if ( centerIsLocal )
      itOut.Set( m_ForegroundValue );
    else
      itOut.Set( m_BackgroundValue );
      
    // Update progress
    progress.CompletedPixel();
    }
}


template<class TInputImage, class TOutputImage>
void
LocalMaximaImageFilter<TInputImage, TOutputImage>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "FullyConnected: "  << m_FullyConnected << std::endl;
}
  
}// end namespace itk
#endif
