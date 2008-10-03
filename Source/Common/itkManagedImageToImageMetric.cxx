/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImageToImageMetric.cxx
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

#ifndef __itkManagedImageToImageMetric_cxx
#define __itkManagedImageToImageMetric_cxx

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

// Include some useful ManagedITK files
#include "itkManagedSingleValuedCostFunction.cxx"
#include "itkManagedImageBase.cxx"
#include "itkManagedTransform.cxx"
#include "itkManagedImageFunction.cxx"

namespace itk
{

///<summary>
///This class is a managed replacement for itk::ImageToImageMetric.
///</summary>
///<remarks>
///ImageToImageMetric computes the similarity between regions of two images.
///It expects a Transform and an Interpolator to be plugged in.
///
///This class computes a value that measures the similarity between the Fixed
///image and the transformed Moving image. The Interpolator is used to compute
///intensity values on non-grid positions resulting from mapping points through 
///the Transform.
///</remarks>
public ref class itkImageToImageMetric abstract : itkSingleValuedCostFunction
{

public:
	///<summary>Set the fixed image.</summary>
	virtual void SetFixedImage( itkImageBase^ image ) = 0;

    ///<summary>Set the fixed image.</summary>
	virtual void SetFixedImage( IntPtr imagePtr ) = 0;

	///<summary>Get the fixed image.</summary>
    ///<param name="image">The itkImageBase to become the fixed image.</param>
	virtual void GetFixedImage( itkImageBase^ image ) = 0;

	///<summary>Set the moving image.</summary>
	virtual void SetMovingImage( itkImageBase^ image ) = 0;

    ///<summary>Set the moving image.</summary>
	virtual void SetMovingImage( IntPtr imagePtr ) = 0;

	///<summary>Get the moving image.</summary>
    ///<param name="image">The itkImageBase to become the moving image.</param>
	virtual void GetMovingImage( itkImageBase^ image ) = 0;

	///<summary>Set the transform.</summary>
	virtual void SetTransform( itkTransform^ transform ) = 0;

	///<summary>Get the transform.</summary>
    ///<param name="transform">The itkTransform to become the transform.</param>
	virtual void GetTransform( itkTransform^ transform ) = 0;

	///<summary>Set the interpolator.</summary>
	virtual void SetInterpolator( itkImageFunction^ interpolator ) = 0;

	///<summary>Get the interpolator.</summary>
    ///<param name="interpolator">The itkImageFuction to become the interpolator.</param>
	virtual void GetInterpolator( itkImageFunction^ interpolator ) = 0;

	///<summary>Get the number of pixels considered in the computation.</summary>
	property unsigned int NumberOfPixelsCounted 
	{ 
		virtual unsigned int get() = 0;
	}

	///<summary>Get/set whether the gradient should be computed or not.</summary>
	property bool ComputeGradient 
	{ 
		virtual bool get() = 0;
		virtual void set( bool value ) = 0;
	}

	///<summary>Get the gradient image.</summary>
    ///<param name="image">The itkImageBase to become the gradient image.</param>
	virtual void GetGradientImage( itkImageBase^ image ) = 0;

	///<summary>Set the parameters defining the Transform.</summary>
	virtual void SetTransformParameters( itkArray<double>^ parameters ) = 0;

	///<summary>
	///Initialize the Metric by making sure that all the components are present
	///and plugged together correctly.
	///</summary>
	virtual void Initialize( ) = 0;

}; // end ref class

} // end namespace itk

#endif
