/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImageFunction.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date: 2008-06-21 09:20:09 +0200 (Sat, 21 Jun 2008) $
  Revision:  $Revision: 18 $

  Portions of this code are covered under the ITK and VTK copyright.
  See http://www.itk.org/HTML/Copyright.htm for details.
  See http://www.vtk.org/copyright.php for details.

  Copyright (c) 2007-2008 Daniel Mueller

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  
=============================================================================*/

#pragma once
#pragma warning( disable : 4635 ) // Disable warnings about XML doc comments

#ifndef __itkManagedImageFunction_cxx
#define __itkManagedImageFunction_cxx

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

// Include some useful ManagedITK files
#include "itkManagedIndex.cxx"
#include "itkManagedContinuousIndex.cxx"
#include "itkManagedPoint.cxx"
#include "itkManagedOffset.cxx"
#include "itkManagedPixelType.cxx"
#include "itkManagedPixel.cxx"
#include "itkManagedImage.cxx"

namespace itk
{

///<summary>
///This class is a managed replacement for itk::ImageFunction.
///</summary>
///<remarks>
///ImageFunction is a baseclass for all objects that evaluates
///a function of an image at index, continuous index or point.
///</remarks>
public ref class itkImageFunction abstract : itkObject
{

public:
    ///<summary>Set the input image to the function object.</summary>
    ///<param name="inputImage">The input image as an itkImage.</param>
	virtual void SetInputImage(itkImageBase^ inputImage) = 0;

    ///<summary>Set the input image to the function object.</summary>
    ///<param name="itkInputImagePtr">The input image as an IntPtr.</param>
	virtual void SetInputImage( IntPtr itkInputImagePtr ) = 0;
	
    /** Get the input image to the function object. */
	// TODO: virtual itkImage^ GetInputImage( ) = 0;

    ///<summary>Evaluate the function at specified physical location.</summary>
    ///<param name="point">The geometric location in physical space.</param>
    ///<returns>The pixel value at the given physical location.</returns>
    virtual itkPixel^ Evaluate( itkPoint^ point ) = 0;
    
    ///<summary>Evaluate the function at specified discrete location.</summary>
    ///<param name="index">The discrete location in image space.</param>
    ///<returns>The pixel value at the given discrete location.</returns>
    virtual itkPixel^ EvaluateAtIndex( itkIndex^ index ) = 0;

    ///<summary>Evaluate the function at specified continuous location.</summary>
    ///<param name="cindex">The continuous location in image space.</param>
    ///<returns>The pixel value at the given continuous location.</returns>
    virtual itkPixel^ EvaluateAtContinuousIndex( itkContinuousIndex^ cindex ) = 0;

}; // end ref class

} // end namespace itk

#endif
