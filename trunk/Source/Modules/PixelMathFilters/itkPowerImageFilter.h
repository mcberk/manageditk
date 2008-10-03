/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkPowerImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkPowerImageFilter_h
#define __itkPowerImageFilter_h

#include "itkUnaryFunctorImageFilter.h"

namespace itk
{
  
/** \class PowerImageFilter
 * \brief Raises the image pixel-wise to the given power.
 * 
 * Applies the following transform to each pixel in the image:
 *
 * \f[
 * f(x) = x^{Exponent}
 * \f]
 *
 * Every output pixel is equal to f(x). Where x is the intensity of the
 * homologous input pixel, and Exponent is a user-provided constant.
 * 
 * \ingroup IntensityImageFilters  Multithreaded
 *
 */

namespace Function {  
template< class TInput, class TOutput>
class Power
{
public:
  Power() {
    m_Exponent = 1.0;
  }
  ~Power() {};
  bool operator!=( const Power & other ) const
  {
    if( m_Power != other.m_Power)
      {
      return true;
      }
    return false;
  }
  bool operator==( const Power & other ) const
  {
    return !(*this != other);
  }

  inline TOutput operator()( const TInput & A )
  {
    const double x = static_cast<double>( A );
    const double y = vcl_pow( x, m_Exponent );
    return static_cast<TOutput>( y );
  }
  void SetExponent( double exponent ) {
    m_Exponent = exponent;
  }
  double GetExponent() const {
    return m_Exponent;
  }
private:
  double  m_Exponent;
};
}


template <class TInputImage, class TOutputImage>
class ITK_EXPORT PowerImageFilter :
    public
UnaryFunctorImageFilter<TInputImage,TOutputImage,
                        Function::Power<
  typename TInputImage::PixelType, 
  typename TOutputImage::PixelType>   >
{
public:
  /** Standard class typedefs. */
  typedef PowerImageFilter  Self;
  typedef UnaryFunctorImageFilter<TInputImage,TOutputImage, 
                                  Function::Power< typename TInputImage::PixelType,
                                                   typename TOutputImage::PixelType> >  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  typedef typename TOutputImage::PixelType OutputPixelType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
  void SetExponent( double exponent )
  {
    if( exponent == this->GetFunctor().GetExponent() )
      {
      return;
      }
    this->GetFunctor().SetExponent( exponent );
    this->Modified();
  }

  double GetExponent( )
  {
    return this->GetFunctor().GetExponent();
  }


#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(InputConvertibleToDoubleCheck,
    (Concept::Convertible<typename TInputImage::PixelType, double>));
  itkConceptMacro(OutputAdditiveOperatorsCheck,
    (Concept::AdditiveOperators<OutputPixelType>));
  itkConceptMacro(DoubleConvertibleToOutputCheck,
    (Concept::Convertible<double, OutputPixelType>));
  itkConceptMacro(OutputTimesDoubleCheck,
    (Concept::MultiplyOperator<OutputPixelType, double>));
  itkConceptMacro(OutputDoubleAdditiveOperatorsCheck,
    (Concept::AdditiveOperators<OutputPixelType, OutputPixelType, double>));
  /** End concept checking */
#endif

protected:
  PowerImageFilter() {}
  virtual ~PowerImageFilter() {}

private:
  PowerImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk

#endif
