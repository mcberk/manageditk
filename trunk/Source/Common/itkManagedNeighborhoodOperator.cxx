/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedNeighborhoodOperator.cxx
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

#ifndef __itkManagedNeighborhoodOperator_cxx
#define __itkManagedNeighborhoodOperator_cxx

// Include some useful ITK headers

// Include some useful ManagedITK files
#include "itkManagedNeighborhood.cxx"

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Diagnostics;

namespace itk
{

///<summary>
///This class is a managed wrapper for itk::Neighborhood.
///</summary>
public ref class itkNeighborhoodOperator abstract : itk::itkNeighborhood
{
public:
    ///<summary>Default constructor.</summary>
	itkNeighborhoodOperator(){}

	///<summary>Get/set the dimensional direction (dimension number) of a directional operator.</summary>
	property unsigned long Direction { virtual unsigned long get()=0; virtual void set(unsigned long value)=0; }

	///<summary>
	///Creates the operator with length only in the specified direction. 
	///The radius of the operator will be 0 except along the axis on which
    ///the operator will work.
	///</summary>
	virtual void CreateDirectional() = 0;

}; // end ref class

} // end namespace itk

#endif