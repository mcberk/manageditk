/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImageToMeshFilter.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date$
  Revision:  $Revision$

  Portions of this code are covered under the ITK and VTK copyright.
  See http://www.itk.org/HTML/Copyright.htm for details.
  See http://www.vtk.org/copyright.php for details.

  Copyright (c) 2008 Dan Mueller

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

#ifndef __itkManagedImageToMeshFilter_cxx
#define __itkManagedImageToMeshFilter_cxx

// Include some useful ManagedITK files
#include "itkManagedImageBase.cxx"
#include "itkManagedMeshSource.cxx"

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
///This class is a managed replacement for itk::ImageToMeshFilter.
///</summary>
///<remarks>
///ImageToMeshFilter is the base class for all process objects that output
///Mesh data and require image data as input. Specifically, this class
///defines the SetInput() method for defining the input to a filter.
///</remarks>
public ref class itkImageToMeshFilter abstract : itkMeshSource
{

protected:
    ///<summary>Protected constructor.</summary>
    ///<param name="name">A string representing the name of the ProcessObject.</param>
	itkImageToMeshFilter( String^ name ) : itkMeshSource( name )
	{ }

public:
    ///<summary>Set the first input of the filter object.</summary>
    ///<param name="input">The input as an itkDataObject.</param>
	virtual void SetInput(itkDataObject^ input) = 0;

    ///<summary>Set the specified input of the filter object.</summary>
    ///<param name="input">The input as an itkDataObject.</param>
	virtual void SetInput(unsigned int index, itkDataObject^ input) = 0;
	
    ///<summary>Set the specified input of the filter object.</summary>
    ///<param name="itkDataObjectPtr">The input as an IntPtr.</param>
    virtual void SetInput( unsigned int index, IntPtr itkDataObjectPtr ) = 0;

    ///<summary>Set the first input of the filter object.</summary>
    ///<param name="itkDataObjectPtr">The input as an IntPtr.</param>
    virtual void SetInput( IntPtr itkDataObjectPtr ) = 0;

}; // end ref class

} // end namespace itk

#endif