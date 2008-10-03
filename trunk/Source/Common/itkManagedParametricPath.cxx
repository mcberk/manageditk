/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedPath.cxx
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

#ifndef __itkManagedPath_cxx
#define __itkManagedPath_cxx

// Include some useful ManagedITK files
#include "itkManagedDataObject.cxx"
#include "itkManagedIndex.cxx"
#include "itkManagedContinuousIndex.cxx"

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

#define itkParametricPathInputType  System::Double
#define itkParametricPathOutputType itkContinuousIndex

///<summary>
///This abstract class is a managed replacement for itk::ParametricPath.
///</summary>
///<remarks>
///Represent a path through ND image space.
///</remarks>
public ref class itkParametricPath abstract : itkDataObject
{

public:
    ///<summary>Get the number of dimensions this path contains.</summary>
	property unsigned int Dimension
	{ 
		virtual unsigned int get( ) = 0;
	}

	///<summary>
    ///Get/set the start of the path.
    ///For most types of paths, the path will begin at zero.
    ///This value can be overridden in children, and is necessary for
    ///iterators to know how to go to the beginning of a path.
    ///</summary>
	property itkParametricPathInputType StartOfInput
	{
		virtual itkParametricPathInputType get( ) = 0;
	}
	
	///<summary>
    ///Get/set the end of the path.
    ///This value is sometimes used by IncrementInput() to go to the end of a path.
    ///</summary>
	property itkParametricPathInputType EndOfInput
	{
		virtual itkParametricPathInputType get( ) = 0;
	}

    ///<summary>Evaluate the path at specified location along the path.</summary>
	virtual itkParametricPathOutputType^ Evaluate ( itkParametricPathInputType input ) = 0;

	///<summary>Evaluate the path at specified location along the path.</summary>
	virtual itkIndex^ EvaluateToIndex ( itkParametricPathInputType input ) = 0;

}; // end ref class

} // end namespace itk

#endif