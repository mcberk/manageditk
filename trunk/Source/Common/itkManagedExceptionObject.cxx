/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedExceptionObject.cxx
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

#ifndef __itkManagedExceptionObject_cxx
#define __itkManagedExceptionObject_cxx

// Include some ITK files
#pragma unmanaged
#include "itkExceptionObject.h"

// Use some managed namespaces
#pragma managed
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::ComponentModel;
using namespace System::Diagnostics;

namespace itk
{

///<summary>
///A managed wrapper for itk::ExceptionObjects.
///</summary>
public ref class itkExceptionObject : System::ApplicationException
{
    
private:
    System::String^ m_Description;
    System::String^ m_Location;
    System::String^ m_File;
    unsigned int m_Line;

public:
	///<summary>Constructor taking a native itk::ExceptionObject.</summary>
	///<param name="ex">The native itk::ExceptionObject.</param>
	itkExceptionObject ( itk::ExceptionObject& ex )
		: System::ApplicationException( gcnew System::String( ex.GetDescription() ) )
	{
        this->m_Description = gcnew System::String( ex.GetDescription() );
		this->m_Location = gcnew System::String( ex.GetLocation() );
		this->m_File = gcnew System::String( ex.GetFile() );
		this->m_Line = ex.GetLine();
	}
	
	///<summary>Constructor taking managed components.</summary>
	///<param name="desc">The native exception description.</param>
	///<param name="loc">The native exception location.</param>
	///<param name="file">The file the naive exception was raised from.</param>
	///<param name="line">The line the naive exception was raised from.</param>
	itkExceptionObject ( System::String^ desc, System::String^ loc, System::String^ file, unsigned int line )
		: System::ApplicationException( desc )
	{
        this->m_Description = desc;
		this->m_Location = loc;
		this->m_File = file;
		this->m_Line = line;
	}
	
	///<summary>Constructor taking std::string components.</summary>
	///<param name="desc">The native exception description.</param>
	///<param name="loc">The native exception location.</param>
	///<param name="file">The file the naive exception was raised from.</param>
	///<param name="line">The line the naive exception was raised from.</param>
	itkExceptionObject ( const char* desc, const char* loc, const char* file, unsigned int line )
		: System::ApplicationException( gcnew System::String( desc ) )
	{
        this->m_Description = gcnew System::String( desc );
		this->m_Location = gcnew System::String( loc );
		this->m_File = gcnew System::String( file );
		this->m_Line = line;
	}

	///<summary>Gets the description. This is the same as the Message.</summary>
	property System::String^ Description
	{
		virtual System::String^ get() { return this->m_Description; }
	}
	
	///<summary>Gets the method location where the exception was thrown.</summary>
	property System::String^ Location
	{
		virtual System::String^ get() { return this->m_Location; }
	}
	
	///<summary>Gets the name of the source ode file from which the exception was thrown.</summary>
	property System::String^ File
	{
		virtual System::String^ get() { return this->m_File; }
	}
	
	///<summary>Gets the name of the source ode file from which the exception was thrown.</summary>
	property unsigned int Line
	{
		virtual unsigned int get() { return this->m_Line; }
	}
	
    ///<summary>Returns a string representation of the itkExceptionObject.</summary>
	///<returns>A string representation similar the native itk::ExceptionObject::Print() method.</returns>
	virtual String^ ToString() override
    {
        System::String^ result = String::Empty;
        result += this->Message;
        
        if (this->m_Location->Length > 0)
            result += Environment::NewLine + "Location: " + this->m_Location;

        if (this->m_File->Length > 0)
        {
            result += Environment::NewLine + "File: " + this->m_File;
            result += Environment::NewLine + "Line: " + this->m_Line;
        }
        
        if (this->StackTrace != nullptr && this->StackTrace->Length > 0)
            result += Environment::NewLine + this->StackTrace;

		return result;
    }

}; // end ref class

} // end namespace itk

#endif