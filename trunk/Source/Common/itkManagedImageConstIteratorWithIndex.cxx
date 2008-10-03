/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImageConstIteratorWithIndex.cxx
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

#ifndef __itkManagedImageConstIteratorWithIndex_cxx
#define __itkManagedImageConstIteratorWithIndex_cxx

// Include some useful ManagedITK files
#include "itkManagedPixelType.cxx"
#include "itkManagedPixel.cxx"
#include "itkManagedIndex.cxx"
#include "itkManagedImageRegion.cxx"
#include "itkManagedImageBase.cxx"

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
///This class is a managed wrapper for itk::ImageIterator.
///</summary>
public ref class itkImageConstIteratorWithIndex abstract : System::Collections::IEnumerable, INativePointer
{
protected:
	bool m_IsDisposed;
	String^ m_MangledTypeString;

    ///<summary>Default constructor.</summary>
	itkImageConstIteratorWithIndex(){}

public:
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

	///<summary>
	///Get/set the index at the current iterator location.
	///Iterators NOT in the "WithIndex" family calculate the index on demand (expensive call).
	///Iterators in the "WithIndex" family maintain the index during operation (inexpensive call).
	///</summary>
	property itkIndex^ Index { virtual itkIndex^ get()=0; virtual void set(itkIndex^ value)=0; }

	///<summary>Get the image region this iterator walks.</summary>
	property itkImageRegion^ Region { virtual itkImageRegion^ get()=0; }

	///<summary>Get the image this iterator walks.</summary>
	property itkImageBase^ Image { virtual itkImageBase^ get()=0; }

	///<summary>Get the pixel value at the current iterator location.</summary>
	virtual itkPixel^ Get() = 0;

	///<summary>Gets if the iterator is at the beginning of the region to iterate.</summary>
	property bool IsAtReverseEnd { virtual bool get()=0; }

	///<summary>Gets if the iterator is at the end of the region to iterate.</summary>
	property bool IsAtEnd { virtual bool get()=0; }

	///<summary>Move the iterator to the beginning location.</summary>
	virtual void GoToBegin() = 0;

	///<summary>Move the iterator to the ending location.</summary>
	virtual void GoToReverseBegin() = 0;

	///<summary>Increment the iterator.</summary>
	virtual itkImageConstIteratorWithIndex^ operator++() = 0;

	///<summary>Decrement the iterator.</summary>
	virtual itkImageConstIteratorWithIndex^ operator--() = 0;

	///<summary>Implement the IEnumerable interface.</summary>
	virtual System::Collections::IEnumerator^ GetEnumerator() = 0;

}; // end ref class

} // end namespace itk

#endif