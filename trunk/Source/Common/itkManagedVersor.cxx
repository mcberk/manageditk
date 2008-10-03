/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedVersor.cxx
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

#ifndef __itkManagedVersor_cxx
#define __itkManagedVersor_cxx

// Include some useful ManagedITK files
#include "itkManagedQuaternion.cxx"
#include "itkManagedPoint.cxx"
#include "itkManagedVector.cxx"

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
///This class is a managed replacement for itk::Versor.
///</summary>
///<remarks>
///The difference between versors and quaternions is that quaternions
///can represent rotations and scale changes while versors are limited
///to rotations. ie. versors are unit or normalized quaternions, the 
///tensor is always 1.0. The class does not provide many operations,
///it is only a basic wrapper for the actual XYZW data.
///</remarks>
public ref class itkVersor : itkQuaternion
{
public:
	///<summary>
	///Default constructor. The Versor is initialised to the identity.
	///</summary>
	itkVersor ( ) : itkQuaternion( )
	{ }

	///<summary>
	///Component constructor. The Versor is initialised to the given XYZW components.
	///</summary>
	itkVersor ( itkQuaternionValueType x, itkQuaternionValueType y, itkQuaternionValueType z, itkQuaternionValueType w  ) : itkQuaternion( x, y, z, w )
	{
		this->Normalize( );
	}

	///<summary>Set the Versor using the given ZYZW components.</summary>
    virtual void Set( itkQuaternionValueType x, itkQuaternionValueType y, itkQuaternionValueType z, itkQuaternionValueType w ) override
	{
		itkQuaternion::Set( x, y, z, w );
		this->Normalize( );
	}

	///<summary>
	///Set the Versor  using a vector and angle.
    ///The unit vector parallel to the given vector will be used.
	///The angle is expected in radians.
	///</summary>
    virtual void Set( itkVector^ axis, itkQuaternionValueType angle ) override
	{
		itkQuaternion::Set( axis, angle );
		this->Normalize( );
	}

	///<summary>Set the Versor as a rotation around the X-axis.</summary>
    virtual void SetRotationAroundX( itkQuaternionValueType angle ) override
	{
		itkQuaternion::SetRotationAroundX( angle );
		this->Normalize( );
	}

	///<summary>Set the Quaternion as a rotation around the Y-axis.</summary>
    virtual void SetRotationAroundY( itkQuaternionValueType angle ) override
	{
		itkQuaternion::SetRotationAroundY( angle );
		this->Normalize( );
	}

	///<summary>Set the Quaternion as a rotation around the Z-axis.</summary>
    virtual void SetRotationAroundZ( itkQuaternionValueType angle ) override
	{
		itkQuaternion::SetRotationAroundZ( angle );
		this->Normalize( );
	}

}; // end ref class

} // end namespace itk

#endif