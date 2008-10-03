/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedTransform.cxx
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

#ifndef __itkManagedTransform_cxx
#define __itkManagedTransform_cxx

// Include some useful ManagedITK files
#include "itkManagedObject.cxx"
#include "itkManagedArray.cxx"
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
///This abstract class is a managed replacement for itk::Transform.
///</summary>
///<remarks>
///Transform points and vector from an input space to an output space.
///                                                                          
///This abstract class define the generic interface for a geometrical
///transformation from one space to another. The class provides methods
///for mapping points, vectors and covariant vectors from the input space
///to the output space.
///                                                                          
///Given that transformation are not necesarily invertible, this basic class
///does not provide the methods for back transfromation. Back transform
///methods are implemented in derived classes where appropriate.
///</remarks>
public ref class itkTransform abstract : itkObject
{

public:
    ///<summary>Get the number of parameters that completely define the Transfom.</summary>
	property unsigned int NumberOfParameters
    { 
		virtual unsigned int get() = 0;
	}

    ///<summary>Get/set the transformation parameters.</summary>
	property itkArray<double>^ Parameters
    {
		virtual itkArray<double>^ get() = 0;
		virtual void set( itkArray<double>^ parameters ) = 0;
	}
	
    ///<summary>Return the inverse of the transform.</summary>
    ///<param name="inverse">The managed instance to become the inverse transform.</param>
    ///<returns>True if the inverse exists, false otherwise.</returns>
    virtual bool GetInverse(itkTransform^ inverse) = 0;

    ///<summary>Apply the transform to a point, mapping it from the input to the output space.</summary>
    ///<param name="point">The point to transform.</param>
    ///<returns>A new instance of the transformed point.</returns>
    virtual itkPoint^ TransformPoint( itkPoint^ point ) = 0; 

    ///<summary>Apply the transform to a vector, mapping it from the input to the output space.</summary>
    ///<param name="vector">The vector to transform.</param>
    ///<returns>A new instance of the transformed point.</returns>
    virtual itkVector^ TransformVector( itkVector^ vector ) = 0;

}; // end ref class

} // end namespace itk

#endif