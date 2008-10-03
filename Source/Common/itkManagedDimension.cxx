/*=============================================================================

  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedDimension.cxx
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

#ifndef __itkManagedDimension_cxx
#define __itkManagedDimension_cxx

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
///This class is used to specify an instance type using the number of dimensions.
///</summary>
///<remarks>
///It can be used to specify the instance type of itkTransform to create.
///</remarks>
public ref class itkDimension : INativePointer
{

private:
    unsigned int m_Dimension;

public:
    ///<summary>Default constructor.</summary>
    itkDimension( unsigned int dimension )
    {
        this->m_Dimension = dimension;
    }

    ///<summary>Get the number of dimensions.</summary>
    property unsigned int Dimension
    {
        unsigned int get() { return this->m_Dimension; }
    }


    ///<summary>Get a string representing the type instance of this INativePointer.</summary>
    ///<example>"2", "3".</example>
    ///<remarks>
    ///This object can be passed to the New() methods to specify the type of
    ///native itk object to create.
    ///</remarks>
    property String^ MangledTypeString
    {
        virtual String^ get() { return this->m_Dimension.ToString(); }
    }

    ///<summary>
    ///Get/set the pointer to the native ITK object associated with
    ///this wrapper instance.
    ///</summary>
    ///<returns>The pointer to the native ITK object.</returns>
    ///<remarks>
    ///This property is not applicable for itkDimension and will always get/set 0.
    ///</remarks>
    property IntPtr NativePointer
    {
        virtual IntPtr get( ) { return IntPtr::Zero; };
        virtual void set ( IntPtr ptr ) { /*Do nothing*/ };
    }

}; // end ref class

} // end namespace itk

#endif