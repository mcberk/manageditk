/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkBinaryClosingImageFilter.txx,v $
  Language:  C++

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkBinaryClosingImageFilter_txx
#define __itkBinaryClosingImageFilter_txx

#include "itkBinaryClosingImageFilter.h"
#include "itkBinaryErodeImageFilter.h"
#include "itkBinaryDilateImageFilter.h"
#include "itkProgressAccumulator.h"

namespace itk {

template<class TInputImage, class TOutputImage, class TKernel>
BinaryClosingImageFilter<TInputImage, TOutputImage, TKernel>
::BinaryClosingImageFilter()
  : m_Kernel()
{
  m_ForegroundValue = NumericTraits<InputPixelType>::max();
  m_BackgroundValue = NumericTraits<OutputPixelType>::NonpositiveMin();
}

template <class TInputImage, class TOutputImage, class TKernel>
void 
BinaryClosingImageFilter<TInputImage, TOutputImage, TKernel>
::GenerateInputRequestedRegion()
{
  // call the superclass' implementation of this method
  Superclass::GenerateInputRequestedRegion();
  
  // We need all the input.
  InputImagePointer input = const_cast<InputImageType *>(this->GetInput());
  if( input )
    {
    input->SetRequestedRegion( input->GetLargestPossibleRegion() );
    }
}


template <class TInputImage, class TOutputImage, class TKernel>
void 
BinaryClosingImageFilter<TInputImage, TOutputImage, TKernel>
::EnlargeOutputRequestedRegion(DataObject *)
{
  this->GetOutput()->SetRequestedRegion( 
                              this->GetOutput()->GetLargestPossibleRegion() );
}

template<class TInputImage, class TOutputImage, class TKernel>
void
BinaryClosingImageFilter<TInputImage, TOutputImage, TKernel>
::GenerateData()
{
  // Allocate the outputs
  this->AllocateOutputs();

  /** set up erosion and dilation methods */
  typename BinaryDilateImageFilter<TInputImage, TOutputImage, TKernel>::Pointer
    dilate = BinaryDilateImageFilter<TInputImage, TOutputImage, TKernel>::New();

  typename BinaryErodeImageFilter<TOutputImage, TOutputImage, TKernel>::Pointer
    erode = BinaryErodeImageFilter<TOutputImage, TOutputImage, TKernel>::New();

  dilate->SetKernel( this->GetKernel() );
  dilate->SetForegroundValue( m_ForegroundValue );
  dilate->SetBackgroundValue( m_BackgroundValue );
  dilate->ReleaseDataFlagOn();
  erode->SetKernel( this->GetKernel() );
  erode->SetForegroundValue( m_ForegroundValue );
  erode->SetBackgroundValue( m_BackgroundValue );
  erode->ReleaseDataFlagOn();
  
  /** set up the minipipeline */
  ProgressAccumulator::Pointer progress = ProgressAccumulator::New();
  progress->SetMiniPipelineFilter(this);
  progress->RegisterInternalFilter(erode, .5f);
  progress->RegisterInternalFilter(dilate, .5f);
  
  dilate->SetInput( this->GetInput() );
  erode->SetInput(  dilate->GetOutput() );
  erode->GraftOutput( this->GetOutput() );

  /** execute the minipipeline */
  erode->Update();

  /** graft the minipipeline output back into this filter's output */
  this->GraftOutput( erode->GetOutput() );
}

template<class TInputImage, class TOutputImage, class TKernel>
void
BinaryClosingImageFilter<TInputImage, TOutputImage, TKernel>
::PrintSelf(std::ostream &os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Kernel: " << m_Kernel << std::endl;
  os << indent << "ForegroundValue: " << m_ForegroundValue << std::endl;
  os << indent << "BackgroundValue: " << m_BackgroundValue << std::endl;
}

}// end namespace itk
#endif
