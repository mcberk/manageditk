/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedNoSmartPointerObject.cxx
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

#ifndef __itkManagedNoSmartPointerObject_cxx
#define __itkManagedNoSmartPointerObject_cxx

// Include some headers for string ops
#include <iostream>  
#include <map>
#include <string>
using std::string;

// Include some useful ManagedITK files
#include "itkManagedINativePointer.cxx"

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
///This class is a managed replacement for ITK objects which are not SmartPointers.
///</summary>
public ref class itkNoSmartPointerObject abstract : INativePointer
{
protected:
	bool m_IsDisposed;
	bool m_DisposeNativeObjectOnFinalize;
	String^ m_MangledTypeString;

    ///<summary>Protected constructor.</summary>
	itkNoSmartPointerObject( )
	{
        this->m_IsDisposed = false;
        this->m_DisposeNativeObjectOnFinalize = true;
		this->m_MangledTypeString = String::Empty;
	}

public:
	///<summary>Gets if the object has been disposed.</summary>
	property bool IsDisposed
	{
		virtual bool get() { return this->m_IsDisposed; }
	}
	
	///<summary>
	///Gets/sets if the underlying native object should be disposed when the managed object is finalized.
	///The default is true.
	///</summary>
	property bool DisposeNativeObjectOnFinalize
	{
		virtual bool get() { return this->m_DisposeNativeObjectOnFinalize; }
		virtual void set( bool value ) { this->m_DisposeNativeObjectOnFinalize = value; }
	}

	///<summary>Get a string representing the type instance of this INativePointer.</summary>
	///<example>"2", "3", "UC".</example>
	property String^ MangledTypeString
	{ 
		virtual String^ get() { return this->m_MangledTypeString; }
	}

	///<summary>
	///Get/set the pointer to the native ITK object associated with this wrapper instance.
	///</summary>
	///<returns>The pointer to the native ITK object.</returns>
	property IntPtr NativePointer{ virtual IntPtr get()=0; virtual void set ( IntPtr value )=0; }

}; // end ref class

} // end namespace itk

#endif