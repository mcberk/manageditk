/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedNeighborhood.cxx
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

#ifndef __itkManagedNeighborhood_cxx
#define __itkManagedNeighborhood_cxx

// Include some useful ManagedITK files
#include "itkManagedSize.cxx"
#include "itkManagedOffset.cxx"
#include "itkManagedPixelType.cxx"
#include "itkManagedPixel.cxx"

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
public ref class itkNeighborhood abstract : System::Collections::IEnumerable, itk::INativePointer
{
protected:
	String^ m_MangledTypeString;

public:
    ///<summary>Default constructor.</summary>
	itkNeighborhood(){}

	///<summary>
	///Get/set the pointer to the native ITK object associated with
	///this wrapper instance.
	///</summary>
	///<returns>The pointer to the native ITK object.</returns>
	property IntPtr NativePointer{ virtual IntPtr get()=0; virtual void set ( IntPtr value )=0; }

	///<summary>Get a string representing the type instance of this INativePointer.</summary>
	///<example>"IUC2", "IF3", "IUC2IUC2".</example>
	property String^ MangledTypeString
	{ 
		virtual String^ get() { return this->m_MangledTypeString; }
	}

	///<summary>Get the size (the total length of the sides) of the neighborhood.</summary>
	property itkSize^ Size { virtual itkSize^ get()=0; }

	///<summary>Get/set the radius of the neighborhood.</summary>
	property itkSize^ Radius { virtual itkSize^ get()=0; virtual void set(itkSize^ value)=0; }

	///<summary>Returns the radius of the neighborhood along a specified dimension.</summary>
	virtual unsigned long GetRadius(const unsigned long n) = 0;
	
	///<summary>Returns the size (total length) of the neighborhood along a specified dimension.</summary>
	virtual unsigned long GetSize(const unsigned long n) = 0;

	///<summary>Returns the element at the center of the neighborhood.</summary>
	virtual itkPixel^ GetCenterValue() = 0;

	///<summary>Returns the array index of the element at the given offset.</summary>
	virtual unsigned int GetNeighborhoodIndex(itkOffset^ offset)  = 0;
	
	///<summary>Returns the array index of the center element.</summary>
	virtual unsigned int GetCenterNeighborhoodIndex() = 0;

	///<summary>Returns pixel value in the buffer at the given index.</summary>
	virtual itkPixel^ GetElement(unsigned int i) = 0;

	///<summary>Allow index access to the buffer.</summary>
	virtual itkPixel^ operator[] (unsigned int i) = 0;

	///<summary>Implement the IEnumerable interface.</summary>
	virtual System::Collections::IEnumerator^ GetEnumerator() = 0;

}; // end ref class

} // end namespace itk

#endif