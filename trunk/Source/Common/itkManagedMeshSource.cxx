/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedMeshSource.cxx
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

#ifndef __itkManagedMeshSource_cxx
#define __itkManagedMeshSource_cxx

// Include some useful ManagedITK files
#include "itkManagedMeshBase.cxx"
#include "itkManagedProcessObject.cxx"

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
///This class is a managed replacement for itk::MeshSource.
///</summary>
///<remarks>
///MeshSource is the base class for all process objects that output
///mesh data. Specifically, this class defines the GetOutput() method
///that returns a pointer to the output mesh. The class also defines
///some internal private data members that are used to manage streaming
///of data.
///</remarks>
public ref class itkMeshSource abstract : itkProcessObject
{

protected:
    ///<summary>Protected constructor.</summary>
    ///<param name="name">A string representing the name of the ProcessObject.</param>
	itkMeshSource( String^ name ) : itkProcessObject( name )
	{ }

public:
    ///<summary>Get the first output.</summary>
    ///<param name="output">The itkMeshBase to make as the output.</param>
	virtual void GetOutput(itkMeshBase^ output) = 0;

    ///<summary>Get the specified output.</summary>
    ///<param name="output">The itkMeshBase to make as the output.</param>
    virtual void GetOutput(unsigned int index, itkMeshBase^ output) = 0;

    ///<summary>Get the specified output as an IntPtr.</summary>
    ///<returns>The output as an IntPtr.</param>
	virtual IntPtr GetOutput( unsigned int index ) = 0;

    ///<summary>Get the first output as an IntPtr.</summary>
    ///<returns>The output as an IntPtr.</param>
	virtual IntPtr GetOutput( ) = 0;

}; // end ref class

} // end namespace itk

#endif