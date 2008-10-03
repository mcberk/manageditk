/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedMatrixOffsetTransform.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date: 2008-03-09 19:29:02 +0100 (Sun, 09 Mar 2008) $
  Revision:  $Revision: 8 $

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

#ifndef __itkManagedMatrixOffsetTransform_cxx
#define __itkManagedMatrixOffsetTransform_cxx

// Include some useful ManagedITK files
#include "itkManagedTransform.cxx"
#include "itkManagedMatrix.cxx"
#include "itkManagedOffset.cxx"
#include "itkManagedPoint.cxx"
#include "itkManagedVector.cxx"

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

namespace itk
{

///<summary>
///This abstract class is a managed replacement for itk::MatrixOffsetTransform.
///</summary>
///<remarks>
///This class serves as a base class for transforms that can be expressed
///as a linear transformation plus a constant offset (e.g., affine, similarity
///and rigid transforms). This base class also provides the concept of
///using a center of rotation and a translation instead of an offset.
///</remarks>
public ref class itkMatrixOffsetTransform abstract : itkTransform
{

public:
	///<summary>Get/set the matrix.</summary>
    ///<remarks>To define an affine transform, you must set the matrix, center, and translation OR the matrix and offset.</remarks>
	property itkMatrix^ Matrix
	{
		virtual itkMatrix^ get() = 0;
		virtual void set(itkMatrix^ value) = 0;
	}

	///<summary>Get/set the offset.</summary>
    ///<remarks>To define an affine transform, you must set the matrix, center, and translation OR the matrix and offset.</remarks>
	property itkVector^ Offset
	{
		virtual itkVector^ get() = 0;
		virtual void set(itkVector^ value) = 0;
	}

	///<summary>Get/set the center of rotation.</summary>
    ///<remarks>To define an affine transform, you must set the matrix, center, and translation OR the matrix and offset.</remarks>
	property itkPoint^ Center
	{
		virtual itkPoint^ get() = 0;
		virtual void set(itkPoint^ value) = 0;
	}

	///<summary>Get/set the translation.</summary>
    ///<remarks>To define an affine transform, you must set the matrix, center, and translation OR the matrix and offset.</remarks>
	property itkVector^ Translation
	{
		virtual itkVector^ get() = 0;
		virtual void set(itkVector^ value) = 0;
	}

    ///<summary>Set the matrix to identity and the offset to zeros.</summary>
    virtual void SetIdentity( ) = 0;


}; // end ref class

} // end namespace itk

#endif