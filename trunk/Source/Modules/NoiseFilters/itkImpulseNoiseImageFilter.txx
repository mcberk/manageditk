/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $
  Author:    Gavin Baker <gavinb@cs.mu.oz.au>

  Copyright (c) 2004 Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkImpulseNoiseImageFilter.h"
#include "itkNumericTraits.h"

namespace itk
{

template <class TInputImage>
ImpulseNoiseImageFilter<TInputImage>
::ImpulseNoiseImageFilter()
{
  m_NoiseFilter = NoiseFilterType::New();
  m_NoiseFilter->GetFunctor().SetOutputMinimum( itk::NumericTraits< InputPixelType >::min() );
  m_NoiseFilter->GetFunctor().SetOutputMaximum( itk::NumericTraits< InputPixelType >::max() );
}

template <class TInputImage>
void
ImpulseNoiseImageFilter<TInputImage>
::GenerateData()
{
  this->AllocateOutputs();

  // Setup grafted pipeline for composite filter

  m_NoiseFilter->SetInput( this->GetInput() );
  m_NoiseFilter->GraftOutput( this->GetOutput() );
  m_NoiseFilter->Update();
  this->GraftOutput( m_NoiseFilter->GetOutput() );
}

template <class TInputImage>
void
ImpulseNoiseImageFilter<TInputImage>
::PrintSelf(std::ostream& os,
            Indent indent) const
{
  os
    << indent << "ImpulseNoiseImageFilter"
    << "\n  Prob: " << this->GetProbability()
    << std::endl;
}

} /* namespace itk */
