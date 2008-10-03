/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedFlatStructuringElement.cxx
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

#ifndef __itkManagedFlatStructuringElement_cxx
#define __itkManagedFlatStructuringElement_cxx

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

// Include some useful ManagedITK files
#include "itkManagedInvalidWrappedTypeException.cxx"
#include "itkManagedINativePointer.cxx"
#include "itkManagedSize.cxx"

namespace itk
{

///<summary>
///This class is a managed wrapper around itk::FlatStructuringElement.
///</summary>
public ref class itkFlatStructuringElement abstract: INativePointer
{

protected:
    bool m_IsDisposed;
    String^ m_Type;
    itkSize^ m_Radius;
    itkFlatStructuringElement^ m_Instance;

public:
    ///<summary>Dispose of the managed object.</summary>
	~itkFlatStructuringElement ( )
    {
		if (!this->m_IsDisposed)
		{
            this->m_IsDisposed = true;
            delete m_Instance;
        }
    }

    ///<summary>Finalize the managed object.</summary>
    !itkFlatStructuringElement ( )
    {
        if (!this->m_IsDisposed)
            delete this;
    }

	///<summary>Create a box shaped structuring element of the given radius.</summary>
    static itkFlatStructuringElement^ Box( itkSize^ radius )
    {
        itkFlatStructuringElement^ result = CreateInstance( "Box", gcnew array<System::Object^>{radius} );
        result->m_IsDisposed = false;
        return result;
    }

	///<summary>Create a ball shaped structuring element of the given radius.</summary>
    static itkFlatStructuringElement^ Ball( itkSize^ radius )
    {
        itkFlatStructuringElement^ result = CreateInstance( "Ball", gcnew array<System::Object^>{radius} );
        result->m_IsDisposed = false;
        return result;
    }

	///<summary>
    ///Create an annulus (ring) structuring element of the given outer radius.
    ///The thickness defaults to 1, and the center pixel is excluded.
    ///</summary>
    static itkFlatStructuringElement^ Annulus( itkSize^ radius )
    {
        itkFlatStructuringElement^ result = CreateInstance( "Annulus", gcnew array<System::Object^>{radius} );
        result->m_IsDisposed = false;
        return result;
    }
    
	///<summary>
    ///Create an annulus (ring) structuring element of the given outer radius.
    ///The thickness is as specified, and the center pixel is excluded.
    ///</summary>
    static itkFlatStructuringElement^ Annulus( itkSize^ radius, unsigned int thickness )
    {
        itkFlatStructuringElement^ result = CreateInstance( "Annulus", gcnew array<System::Object^>{radius, thickness} );
        result->m_IsDisposed = false;
        return result;
    }

	///<summary>
    ///Create an annulus (ring) structuring element of the given outer radius.
    ///The thickness is as specified, and the center pixel is included or excluded as specified.
    ///</summary>
    static itkFlatStructuringElement^ Annulus( itkSize^ radius, unsigned int thickness, bool includeCenter )
    {
        itkFlatStructuringElement^ result = CreateInstance( "Annulus", gcnew array<System::Object^>{radius, thickness, includeCenter} );
        result->m_IsDisposed = false;
        return result;
    }

	///<summary>Get a string representing the type instance of the structuring element.</summary>
	///<example>"FSE2", "FSE3".</example>
	///<remarks>
	///This object can be passed to the New() methods to specify the type of
	///native itk object to create.
	///</remarks>
	property String^ MangledTypeString
	{ 
		virtual String^ get() { return "FSE" + this->m_Radius->Dimension.ToString(); }
	}

	///<summary>
	///Get/set the pointer to the native ITK object associated with
	///this type instance.
	///</summary>
	///<returns>The pointer to the native ITK object.</returns>
	property virtual IntPtr NativePointer
	{ 
		virtual IntPtr get(){ return m_Instance->NativePointer; }
		virtual void set ( IntPtr value){ m_Instance->NativePointer = value; }
    }
    
    ///<summary>
	///Converts the structuring to a string representation in the following format:
	///   Type[radius]
	///Example: Ball[2,2,2]
	///</summary>
    ///<returns>A string representation of the structuring element.</returns>
	virtual String^ ToString() override
    {
        return m_Type + m_Radius->ToString();
    }
	
private:
	///<summary>Creates the correct type instance of the underlying native itk::FlatStructuringElement.</summary>
	static itkFlatStructuringElement^ CreateInstance( String^ type, array<System::Object^>^ args)
    {
		itkSize^ radius = safe_cast<itkSize^>(args[0]);
		String^ nameInstanceType = "itk.itkFlatStructuringElement_" + radius->Dimension.ToString();

		try
		{
			System::Type^ typeInstance = System::Reflection::Assembly::GetExecutingAssembly()->GetType(nameInstanceType);
			if (typeInstance == nullptr)
			    throw gcnew NullReferenceException("The type '" + nameInstanceType + "' could not be found in " + System::Reflection::Assembly::GetExecutingAssembly()->GetName() );
			System::Object^ objInstance = typeInstance->InvokeMember(type, System::Reflection::BindingFlags::InvokeMethod, System::Type::DefaultBinder, nullptr, args);
			if (objInstance == nullptr)
			    throw gcnew NullReferenceException("Could not invoke the " + type + "() method for '" + nameInstanceType + "'.");
            return safe_cast<itkFlatStructuringElement^>(objInstance);
		}
		catch (Exception^ ex)
		{
			throw gcnew itkInvalidWrappedTypeException("Could not create an instance of '" + nameInstanceType + "'. The given type may not be supported or may be invalid.", ex);
		}
    }
}; // end ref class

} // end namespace itk

#endif