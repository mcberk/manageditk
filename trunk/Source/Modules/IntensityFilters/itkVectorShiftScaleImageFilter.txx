/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkVectorShiftScaleImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkVectorShiftScaleImageFilter_txx
#define _itkVectorShiftScaleImageFilter_txx

#include "itkVectorShiftScaleImageFilter.h"

#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIterator.h"
#include "itkNumericTraits.h"
#include "itkProgressReporter.h"

namespace itk {

template<class TInputImage, class TOutputImage>
VectorShiftScaleImageFilter<TInputImage, TOutputImage>
::VectorShiftScaleImageFilter()
{
  m_Shift = NumericTraits<RealType>::Zero;
  m_Scale = NumericTraits<RealType>::One;
  m_UnderflowCount = 0;
  m_OverflowCount = 0;
  m_ThreadUnderflow.SetSize(1);
  m_ThreadOverflow.SetSize(1);
}

template<class TInputImage, class TOutputImage>
VectorShiftScaleImageFilter<TInputImage, TOutputImage>
::~VectorShiftScaleImageFilter()
{
}

template<class TInputImage, class TOutputImage>
void
VectorShiftScaleImageFilter<TInputImage, TOutputImage>
::BeforeThreadedGenerateData ()
{
  int numberOfThreads = this->GetNumberOfThreads();

  //  Allocate and initialize the thread temporaries
  m_ThreadUnderflow.SetSize(numberOfThreads);
  m_ThreadUnderflow.Fill(0);
  m_ThreadOverflow.SetSize(numberOfThreads);
  m_ThreadOverflow.Fill(0);
}

template<class TInputImage, class TOutputImage>
void
VectorShiftScaleImageFilter<TInputImage, TOutputImage>
::AfterThreadedGenerateData ()
{
  int numberOfThreads = this->GetNumberOfThreads();

  m_UnderflowCount = 0;
  m_OverflowCount = 0;

  // Accumulate counts for each thread
  for( int i = 0; i < numberOfThreads; i++)
    {
    m_UnderflowCount += m_ThreadUnderflow[i];
    m_OverflowCount += m_ThreadOverflow[i];
    }
}

template<class TInputImage, class TOutputImage>
void
VectorShiftScaleImageFilter<TInputImage, TOutputImage>
::ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread,
                       int threadId) 
{
  RealType value;
  InputImagePixelType valueInput;
  OutputImagePixelType valueOutput;
  ImageRegionConstIterator<TInputImage>  it (this->GetInput(), outputRegionForThread);
  ImageRegionIterator<TOutputImage> ot (this->GetOutput(), outputRegionForThread);
  it.GoToBegin();
  ot.GoToBegin();
  
  // support progress methods/callbacks
  ProgressReporter progress(this, threadId, outputRegionForThread.GetNumberOfPixels());
          
  // shift and scale each input pixel component
  while (!it.IsAtEnd())
    {
    valueInput = it.Get();
    valueOutput = OutputImagePixelType();

    // do for each component
    for(unsigned int i=0; i<InputImagePixelType::Length; i++)
      {
      value = (static_cast<RealType>(valueInput[i]) + m_Shift) * m_Scale;
      if (value < NumericTraits<OutputImagePixelValueType>::NonpositiveMin())
        {
        valueOutput[i] = NumericTraits<OutputImagePixelValueType>::NonpositiveMin();
        m_ThreadUnderflow[threadId]++;
        }
      else if (value > NumericTraits<OutputImagePixelValueType>::max())
        {
        valueOutput[i] = NumericTraits<OutputImagePixelValueType>::max();
        m_ThreadOverflow[threadId]++;
        }
      else
        {
        valueOutput[i] = static_cast<OutputImagePixelValueType>( value );
        }
      }
    
    // set the output value
    ot.Set( valueOutput );

    ++it;
    ++ot;

    progress.CompletedPixel();
    }
}

template <class TInputImage, class TOutputImage>
void 
VectorShiftScaleImageFilter<TInputImage, TOutputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);

  os << indent << "Shift: "  << m_Shift << std::endl;
  os << indent << "Scale: "  << m_Scale << std::endl;
  os << indent << "Computed values follow:" << std::endl;
  os << indent << "UnderflowCount: "  << m_UnderflowCount << std::endl;
  os << indent << "OverflowCount: "  << m_OverflowCount << std::endl;
}


}// end namespace itk
#endif
