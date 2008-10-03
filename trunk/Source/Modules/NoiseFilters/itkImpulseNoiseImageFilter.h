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
#ifndef __itkImpulseNoiseImageFilter_h
#define __itkImpulseNoiseImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkUnaryFunctorImageFilter.h"

#include <stdlib.h>

namespace itk
{

/** \class ImpulseNoiseFunctor
 * \brief Pixel functor that adds impulse noise as Salt & Pepper
 */
template < class TPixel >
class ImpulseNoiseFunctor
{
public:

  ImpulseNoiseFunctor()
  {
    m_Probability = 0.01f;
  }

  float GetProbability() const
  {
    return m_Probability;
  }

  void SetProbability( float prob )
  {
    m_Probability = prob;
  }
  
  void SetOutputMinimum( TPixel min ) {
    m_OutputMinimum = min;
  }

  void SetOutputMaximum( TPixel max ) {
    m_OutputMaximum = max;
  }

  TPixel GetOutputMinimum() const {
    return m_OutputMinimum;
  }

  TPixel GetOutputMaximum() const {
    return m_OutputMaximum;
  }

  float GetNextRandom()
  {
    // Get a random number from [0,1]
    return (float)rand()/(RAND_MAX+1.0);
  }

  TPixel operator()( TPixel value )
  {
    // Get the minimum and maximum output values
    static const float min = static_cast<float>( m_OutputMinimum );
    static const float max = static_cast<float>( m_OutputMaximum );

    // There is a 50% chance of salt vs pepper
    float e = 0.0f;
    float var = GetNextRandom();
    float salt_pepper = GetNextRandom() > 0.5 ? min : max;

    if ( var < m_Probability )
      {
      e = 1.0f;
      }

    // Compute the output value
    float output = (1.0f - e) * static_cast<float>( value ) + e*salt_pepper;

    // Clamp the output value in valid range
    output = ( output < min ? min : output );
    output = ( output > max ? max : output );

    return static_cast< TPixel > ( output );
  }

private:
  TPixel m_OutputMinimum;
  TPixel m_OutputMaximum;
  float m_Probability;
};

/** \class ImpulseNoiseImageFilter
 * \brief Adds impulse noise to the input image
 *
 * Adds impulse noise to the input image, according to a probabilistic
 * model.  The noise is 50% salt and 50% pepper.
 *
 * \author Gavin Baker <gavinb at cs_mu_oz_au>
 *
 * \ingroup ImageToImageFilters
 */
template <class TInputImage >
class ITK_EXPORT ImpulseNoiseImageFilter :
    public ImageToImageFilter< TInputImage, TInputImage >
{
public:
  /** Standard class typedefs. */
  typedef ImpulseNoiseImageFilter Self;
  typedef ImageToImageFilter<TInputImage, TInputImage>  Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory */
  itkNewMacro(Self);  

  /** Run-time type information (and related methods). */
  itkTypeMacro(ImpulseNoiseImageFilter, ImageToImageFilter);

  /** Superclass typedefs. */
  typedef typename Superclass::OutputImageRegionType OutputImageRegionType;
  typedef typename Superclass::OutputImagePointer    OutputImagePointer;

  /** Some convenient typedefs. */
  typedef TInputImage InputImageType;
  typedef typename InputImageType::Pointer        InputImagePointer;
  typedef typename InputImageType::ConstPointer   InputImageConstPointer;
  typedef typename InputImageType::RegionType     InputImageRegionType;
  typedef typename InputImageType::PixelType      InputImagePixelType;
  typedef typename InputImageType::PixelType      InputPixelType;

  /** ImageDimension constants */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  virtual void GenerateData();

  /**
   *    Returns the probability density for the noise.
   *    The default is 0.01.
   */
  float GetProbability() const
  {
    return m_NoiseFilter->GetFunctor().GetProbability();
  }

  /**
   *    Specifies the probability [0,1] that a given voxel will be affected
   *    by noise.
   */
  void SetProbability( float prob )
  {
    return m_NoiseFilter->GetFunctor().SetProbability( prob );
    this->Modified();
  }

  /** Set the minimum output value. */
  void SetOutputMinimum( InputImagePixelType min )
  {
    if( min == m_NoiseFilter->GetFunctor().GetOutputMinimum() )
      {
      return;
      }
    m_NoiseFilter->GetFunctor().SetOutputMinimum( min );
    this->Modified();
  }

  /** Get the minimum output value. */
  InputImagePixelType GetOutputMinimum( )
  {
    return m_NoiseFilter->GetFunctor().GetOutputMinimum();
  }

  /** Set the maximum output value. */
  void SetOutputMaximum( InputImagePixelType max )
  {
    if( max == m_NoiseFilter->GetFunctor().GetOutputMaximum() ) 
      {
      return;
      }
    m_NoiseFilter->GetFunctor().SetOutputMaximum( max );
    this->Modified();
  }

  /** Get the maximum output value. */
  InputImagePixelType GetOutputMaximum( )
  {
    return m_NoiseFilter->GetFunctor().GetOutputMaximum();
  }

protected:

  ImpulseNoiseImageFilter();

  virtual void PrintSelf(std::ostream& os, Indent indent) const;

private:

  ImpulseNoiseImageFilter(const Self&);  // intentionally not implemented
  void operator=(const Self&);      // intentionally not implemented

public:

  typedef UnaryFunctorImageFilter<
    InputImageType,
    InputImageType,
    ImpulseNoiseFunctor< typename InputImageType::PixelType > >
  NoiseFilterType;

private:

  typename NoiseFilterType::Pointer m_NoiseFilter;
};

} /* end namespace itk */

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkImpulseNoiseImageFilter.txx"
#endif

#endif /* __itkImpulseNoiseImageFilter_h */
