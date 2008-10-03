/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkScaleShiftImageFilter.h,v $
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkScaleShiftImageFilter_h
#define __itkScaleShiftImageFilter_h

#include "itkUnaryFunctorImageFilter.h"

namespace itk
{
  
/** \class ScaleShiftImageFilter
 * \brief Applies a scaling then a shift pixel-wise to the input image.
 * 
 * Applies the following transform to each pixel in the image:
 *
 * \f[
 * f(x) = ( x * scale ) + shift
 * \f]
 *
 * This is the dual to the ShiftScaleImageFilter.
 * This filter is useful for manually applying the DICOM slope/intercept linear transformation.
 * 
 * \ingroup IntensityImageFilters  Multithreaded
 *
 */

namespace Function {  
template< class TInput, class TOutput>
class ScaleShift
{
public:
  ScaleShift() {
    m_Scale = 1.0;
    m_Shift = 0.0;
  }
  ~ScaleShift() {};
  bool operator!=( const ScaleShift & other ) const
  {
    if( m_Scale != other.m_Scale || m_Shift != other.m_Shift )
      {
      return true;
      }
    return false;
  }
  bool operator==( const ScaleShift & other ) const
  {
    return !(*this != other);
  }

  inline TOutput operator()( const TInput & A )
  {
    typedef NumericTraits<TInput>::RealType RealType;
    const RealType x = static_cast< RealType >( A );
    const RealType scale = static_cast< RealType >( m_Scale );
    const RealType shift = static_cast< RealType >( m_Shift);
    const RealType out = ( x * scale ) + shift;
    return static_cast< TOutput >( out );
  }
  void SetScale( double scale ) {
    m_Scale = scale;
  }
  double GetScale() const {
    return m_Scale;
  }
  void SetShift( double shift ) {
    m_Shift = shift;
  }
  double GetShift() const {
    return m_Shift;
  }
private:
  double  m_Scale;
  double  m_Shift;
};
}


template <class TInputImage, class TOutputImage>
class ITK_EXPORT ScaleShiftImageFilter :
    public
UnaryFunctorImageFilter<TInputImage,TOutputImage,
                        Function::ScaleShift<
  typename TInputImage::PixelType, 
  typename TOutputImage::PixelType>   >
{
public:
  /** Standard class typedefs. */
  typedef ScaleShiftImageFilter  Self;
  typedef UnaryFunctorImageFilter<TInputImage,TOutputImage, 
                                  Function::ScaleShift< typename TInputImage::PixelType,
                                                        typename TOutputImage::PixelType> >  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  typedef typename TOutputImage::PixelType OutputPixelType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);
  
  /** Set the scale value. */
  void SetScale( double scale )
  {
    if( scale == this->GetFunctor().GetScale() )
      {
      return;
      }
    this->GetFunctor().SetScale( scale );
    this->Modified();
  }

  /** Get the scale value. */
  double GetScale( )
  {
    return this->GetFunctor().GetScale();
  }

  /** Set the shift value. */
  void SetShift( double shift )
  {
    if( shift == this->GetFunctor().GetShift() )
      {
      return;
      }
    this->GetFunctor().SetShift( shift );
    this->Modified();
  }

  /** Get the shift value. */
  double GetShift( )
  {
    return this->GetFunctor().GetShift();
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
  ScaleShiftImageFilter() {}
  virtual ~ScaleShiftImageFilter() {}

private:
  ScaleShiftImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk

#endif
