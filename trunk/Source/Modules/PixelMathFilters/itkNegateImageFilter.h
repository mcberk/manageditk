/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkNegateImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkNegateImageFilter_h
#define __itkNegateImageFilter_h

#include "itkUnaryFunctorImageFilter.h"
#include "itkConceptChecking.h"

namespace itk
{
  
/** \class NegateImageFilter
 * \brief Computes the pixel-wise negation of the value.
 * 
 * \ingroup IntensityImageFilters  Multithreaded
 */
namespace Function {  
  
template< class TInput, class TOutput>
class Negate
{
public:
  Negate() {}
  ~Negate() {}
  bool operator!=( const Negate & ) const
  {
    return false;
  }
  bool operator==( const Negate & other ) const
  {
    return !(*this != other);
  }
  inline TOutput operator()( const TInput & A )
  { return (TOutput)( -A ); }
}; 
}

template <class TInputImage, class TOutputImage>
class ITK_EXPORT NegateImageFilter :
    public
UnaryFunctorImageFilter<TInputImage,TOutputImage, 
                        Function::Negate<
  typename TInputImage::PixelType, 
  typename TOutputImage::PixelType>   >
{
public:
  /** Standard class typedefs. */
  typedef NegateImageFilter  Self;
  typedef UnaryFunctorImageFilter<TInputImage,TOutputImage, 
                                  Function::Negate< typename TInputImage::PixelType,
                                                    typename TOutputImage::PixelType> >  Superclass;
  typedef SmartPointer<Self>   Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(ConvertibleCheck,
    (Concept::Convertible<typename TInputImage::PixelType,
                          typename TOutputImage::PixelType>));
  itkConceptMacro(InputGreaterThanIntCheck,
    (Concept::GreaterThanComparable<typename TInputImage::PixelType, int>));
  /** End concept checking */
#endif

protected:
  NegateImageFilter() {}
  virtual ~NegateImageFilter() {}

private:
  NegateImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

};

} // end namespace itk


#endif
