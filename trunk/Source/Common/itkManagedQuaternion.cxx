/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedQuaternion.cxx
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

#ifndef __itkManagedQuaternion_cxx
#define __itkManagedQuaternion_cxx

// Include some useful ManagedITK files
#include "itkManagedObject.cxx"
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

#define itkQuaternionValueType System::Double

///<summary>
///This class is a managed replacement for itk::Quaternion.
///</summary>
///<remarks>
///The class does not provide many quaternion operations, it is
///only a basic wrapper for the actual XYZW data.
///</remarks>
public ref class itkQuaternion
{
protected:
	itkQuaternionValueType m_X;
	itkQuaternionValueType m_Y;
	itkQuaternionValueType m_Z;
	itkQuaternionValueType m_W;

public:
	///<summary>
	///Default constructor. The Quaternion is initialised to the identity.
	///</summary>
	itkQuaternion ( )
	{
		this->SetIdentity();
	}

	///<summary>
	///Component constructor. The Quaternion is initialised to the given XYZW components.
	///</summary>
	itkQuaternion ( itkQuaternionValueType x, itkQuaternionValueType y, itkQuaternionValueType z, itkQuaternionValueType w  )
	{
		this->Set( x, y, z, w );
	}

	///<summary>Get the X component.</summary>
	property itkQuaternionValueType X
	{
		virtual itkQuaternionValueType get() { return m_X; }
	}

	///<summary>Get the Y component.</summary>
	property itkQuaternionValueType Y
	{
		virtual itkQuaternionValueType get() { return m_Y; }
	}

	///<summary>Get the Z component.</summary>
	property itkQuaternionValueType Z
	{
		virtual itkQuaternionValueType get() { return m_Z; }
	}

	///<summary>Get the W component.</summary>
	property itkQuaternionValueType W
	{
		virtual itkQuaternionValueType get() { return m_W; }
	}

	///<summary>
	///Gets the scalar (W) part.
	///</summary>
	property itkQuaternionValueType Scalar
	{
		virtual itkQuaternionValueType get() { return m_W; }
	}

	///<summary>Compute the tensor.</summary>
	property itkQuaternionValueType Tensor
	{
		virtual itkQuaternionValueType get() 
		{
			return Math::Sqrt( m_X*m_X + m_Y*m_Y + m_Z*m_Z + m_W*m_W ); 
		}
	}

	///<summary>Compute the axis of rotation.</summary>
	property itkVector^ Axis
	{
		virtual itkVector^ get() 
		{
			itkVector^ axis = gcnew itkVector(3U);
			itkQuaternionValueType vectorNorm = Math::Sqrt( m_X*m_X + m_Y*m_Y + m_Z*m_Z );

			if (Math::Abs(vectorNorm) < Double::Epsilon)
			{
				axis[0] = 0.0;
				axis[1] = 0.0;
				axis[2] = 0.0;
			}
			else
			{
				axis[0] = m_X / vectorNorm;
				axis[1] = m_Y / vectorNorm;
				axis[2] = m_Z / vectorNorm;
			}

			return axis;
		}
	}

	///<summary>
	///Gets the right (vector) part of the Quaternion.
	///It is called Right because it is equivalent to a right angle rotation.
	///</summary>
	property itkVector^ Right
	{
		virtual itkVector^ get() 
		{
			itkVector^ right = gcnew itkVector(3U);
			right[0] = m_X;
			right[1] = m_Y;
			right[2] = m_Z;
			return right;
		}
	}

	///<summary>
	///Returns the rotation angle in radians.
	///</summary>
	property itkQuaternionValueType Angle
	{
		virtual itkQuaternionValueType get() 
		{
			itkQuaternionValueType vectorNorm = Math::Sqrt( m_X*m_X + m_Y*m_Y + m_Z*m_Z );
			itkQuaternionValueType angle = 2.0 * Math::Atan2( vectorNorm, m_W );  
			return angle;
		}
	}

	///<summary>
	///Normalize the Quaternion.
	///</summary>
    virtual void Normalize( )
	{
		itkQuaternionValueType tensor = this->Tensor;

		if (Math::Abs(tensor) < Double::Epsilon)
			throw gcnew ApplicationException( "Attempted to normalize an itkQuaternion with zero tensor." );
		
		m_X /= tensor;
		m_Y /= tensor;  
		m_Z /= tensor;
		m_W /= tensor;
	}

	///<summary>Set the Quaternion using the given XYZW components.</summary>
    virtual void Set( itkQuaternionValueType x, itkQuaternionValueType y, itkQuaternionValueType z, itkQuaternionValueType w )
	{
		m_X = x;
		m_Y = y;  
		m_Z = z;
		m_W = w;
	}

	///<summary>
	///Set the Quaternion  using a vector and angle.
    ///The unit vector parallel to the given vector will be used.
	///The angle is expected in radians.
	///</summary>
    virtual void Set( itkVector^ axis, itkQuaternionValueType angle )
	{
		itkQuaternionValueType vectorNorm = axis->GetNorm();
		itkQuaternionValueType cosangle2 = Math::Cos( angle/2.0 );
		itkQuaternionValueType sinangle2 = Math::Sin( angle/2.0 );
		itkQuaternionValueType factor =  sinangle2 / vectorNorm;
  
		m_X = axis[0] * factor;
		m_Y = axis[1] * factor;
		m_Z = axis[2] * factor;  
		m_W = cosangle2;
	}

	///<summary>Set the Quaternion as a rotation around the X-axis.</summary>
    virtual void SetRotationAroundX( itkQuaternionValueType angle )
	{
		itkQuaternionValueType sinangle2 = Math::Sin( angle/2.0 );
		itkQuaternionValueType cosangle2 = Math::Cos( angle/2.0 );

		m_X = sinangle2;
		m_Y = 0.0;
		m_Z = 0.0;  
		m_W = cosangle2;
	}

	///<summary>Set the Quaternion as a rotation around the Y-axis.</summary>
    virtual void SetRotationAroundY( itkQuaternionValueType angle )
	{
		itkQuaternionValueType sinangle2 = Math::Sin( angle/2.0 );
		itkQuaternionValueType cosangle2 = Math::Cos( angle/2.0 );

		m_X = 0.0;
		m_Y = sinangle2;
		m_Z = 0.0;  
		m_W = cosangle2;
	}

	///<summary>Set the Quaternion as a rotation around the Z-axis.</summary>
    virtual void SetRotationAroundZ( itkQuaternionValueType angle )
	{
		itkQuaternionValueType sinangle2 = Math::Sin( angle/2.0 );
		itkQuaternionValueType cosangle2 = Math::Cos( angle/2.0 );

		m_X = 0.0;
		m_Y = 0.0;
		m_Z = sinangle2;  
		m_W = cosangle2;
	}

	///<summary>Set the Quaternion as identity ie. [0,0,0,1].</summary>
    virtual void SetIdentity( )
	{
		m_X = 0.0;
		m_Y = 0.0;
		m_Z = 0.0;  
		m_W = 1.0;
	}

}; // end ref class

} // end namespace itk

#endif