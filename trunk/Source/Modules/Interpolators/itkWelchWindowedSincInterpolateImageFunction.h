/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkWelchWindowedSincInterpolateImageFunction.h
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __itkWelchWindowedSincInterpolateImageFunction_h
#define __itkWelchWindowedSincInterpolateImageFunction_h

#include "itkWindowedSincInterpolateImageFunction.h"

namespace itk
{
template <class TInputImage,
          unsigned int VRadius,
          class TBoundaryCondition=ConstantBoundaryCondition<TInputImage>,
		  class TCoordRep=double>
class ITK_EXPORT WelchWindowedSincInterpolateImageFunction : 
  public WindowedSincInterpolateImageFunction<TInputImage,
                                              VRadius,
											  Function::WelchWindowFunction<VRadius>,
											  TBoundaryCondition,
											  TCoordRep>
{
public:
  /** Standard class typedefs. */
  typedef WelchWindowedSincInterpolateImageFunction Self;
  typedef WindowedSincInterpolateImageFunction<TInputImage,
	                                           VRadius,
											   Function::WelchWindowFunction<VRadius>,
											   TBoundaryCondition,
											   TCoordRep> Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

protected:
  WelchWindowedSincInterpolateImageFunction() {}
  virtual ~WelchWindowedSincInterpolateImageFunction() {}

private:
  WelchWindowedSincInterpolateImageFunction(const Self&); //purposely not implemented
  void operator=(const Self&);                            //purposely not implemented
};

} // end namespace itk

#endif