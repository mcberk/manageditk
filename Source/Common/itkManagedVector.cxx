/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedVector.cxx
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

#ifndef __itkManagedVector_cxx
#define __itkManagedVector_cxx

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::ComponentModel;
using namespace System::Diagnostics;

// Include Array
#include "itkManagedArray.cxx"

namespace itk
{

#define itkVectorValueType System::Double

///<summary>
///This class is a managed replacement for itk::Vector.
///</summary>
///<remarks>
///Vector is a class that holds an n-Dimensional vector of values. It
///can be used as the data type held at each pixel in an Image or as 
///a data type for the mathematical 'vector'.                                           
///</remarks>
public ref class itkVector : itkArray<itkVectorValueType>
{

public:
	///<summary>Constructor taking the data values as a params array.</summary>
	///<param name="data">The variable length data array. The dimension will be initialised as data.Length.</param>
	itkVector ( ... array<itkVectorValueType>^ data ) : itkArray( data )
	{ }

	///<summary>Constructor taking the number of dimensions for the array.</summary>
	///<remarks>The data values are initialised as zero.</remarks>
	///<param name="dimension">The dimensionality of the array to initialise.</param>
	itkVector( unsigned int dimension ) : itkArray( dimension )
	{ }

	///<summary>Constructor taking another array.</summary>
	///<param name="other">Another array to clone the data from.</param>
	itkVector ( itkVector^ other) : itkArray( other->Data )
	{ }

    ///<summary>
	///Compares the given Object to this.
	///They are equal if they have the same dimensionality AND data.
	///</summary>
    ///<param name="obj">The object to test.</param>
    ///<returns>true AND the objects are equal OR false AND the objects are not equal.</returns>
	virtual bool Equals(Object^ obj) override
    {
		// Check if input object is null
        if ( obj == nullptr )
            return false;

        // Cast
        itkVector^ right = safe_cast< itkVector^ >(obj);

        if ( right != nullptr )
        {
            // Check number of dimensions are the same
            if (this->Dimension != right->Dimension) return false;

            // Check data at each location is the the same
            bool result = true;
            for (unsigned int i = 0; i < this->Dimension; i++)
                result &= (this[i] == right[i]);
            return result;
        }

        return false;	
	}

    ///<summary>
	///Compares two itkVector objects.
	///They are equal if they have the same dimensionality AND data.
	///</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>true AND the objects are equal OR false AND the objects are not equal.</returns>
    static bool operator ==(itkVector^ lhs, itkVector^ rhs)
    {
		if ( Object::ReferenceEquals(lhs, rhs) )
            return true;
		else if ( Object::ReferenceEquals(lhs, nullptr) )
			return false;
		else if ( Object::ReferenceEquals(rhs, nullptr) )
            return false;
        else
            return lhs->Equals(rhs);
    }

    ///<summary>
	///Compares two itkVector objects.
	///They are not equal if they do not have the same dimensionality OR 
	///do not have the same data.
	///</summary>
    ///<param name="rhs"></param>
    ///<returns>true AND the objects are not equal OR false AND the objects are equal.</returns>
    virtual bool operator !=(itkVector^ rhs)
    {
        return !(this == rhs);
    }

    ///<summary>Performs an element-wise addition.</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>A new itkVector instance with data as the element-wise addition.</returns>
    static itkVector^ operator+(itkVector^ lhs, itkVector^ rhs)
    {
		if ( lhs == nullptr || rhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkVector^ result = gcnew itkVector( lhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = lhs[i] + rhs[i];
            return result;
		}
    }

    ///<summary>Performs an element-wise subtraction.</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>A new itkVector instance with data as the element-wise subtraction.</returns>
    static itkVector^ operator-(itkVector^ lhs, itkVector^ rhs)
    {
		if ( lhs == nullptr || rhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkVector^ result = gcnew itkVector( lhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = lhs[i] - rhs[i];
            return result;
		}
    }

    ///<summary>Multiply by a scalar value.</summary>
    ///<param name="lhs"></param>
    ///<param name="scalar"></param>
    ///<returns>A new itkVector instance with each data element multiplied by the scalar.</returns>
    static itkVector^ operator*(itkVector^ lhs, double scalar)
    {
		if ( lhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkVector^ result = gcnew itkVector( lhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = lhs[i] * scalar;
            return result;
		}
    }

    ///<summary>Multiply by a scalar value.</summary>
    ///<param name="scalar"></param>
    ///<param name="rhs"></param>
    ///<returns>A new itkVector instance with each data element multiplied by the scalar.</returns>
    static itkVector^ operator*(double scalar, itkVector^ rhs)
    {
		if ( rhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkVector^ result = gcnew itkVector( rhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = rhs[i] * scalar;
            return result;
		}
    }

    ///<summary>Divide by a scalar value.</summary>
    ///<param name="lhs"></param>
    ///<param name="scalar"></param>
    ///<returns>A new itkVector instance with each data element divided by the scalar.</returns>
    static itkVector^ operator/(itkVector^ lhs, double scalar)
    {
		if ( lhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkVector^ result = gcnew itkVector( lhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = lhs[i] / scalar;
            return result;
		}
    }

    ///<summary>Divide by a scalar value.</summary>
    ///<param name="scalar"></param>
    ///<param name="rhs"></param>
    ///<returns>A new itkVector instance with each data element divided by the scalar.</returns>
    static itkVector^ operator/(double scalar, itkVector^ rhs)
    {
		if ( rhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkVector^ result = gcnew itkVector( rhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = rhs[i] / scalar;
            return result;
		}
    }

	///<summary>Computes the Euclidean norm (magnitude) of the vector.</summary>
    ///<returns>The Euclidean norm (magnitude) of the vector.</returns>
    double GetNorm()
    {
		return Math::Sqrt(this->GetSquaredNorm());
    }

	///<summary>Computes the squared Euclidean (magnitude) of the vector.</summary>
	///<returns>The squared Euclidean norm (magnitude) of the vector.</returns>
    double GetSquaredNorm()
    {
        double result = 0.0;
 
        for (unsigned int i = 0; i < this->Dimension; i++)
            result += this[i] * this[i];

        return result;
    }

	///<summary>Normalizes this instance of the vector. ie. Divides each comonent by GetNorm().</summary>
    void Normalize()
    {
		double norm = this->GetNorm();
        for (unsigned int i = 0; i < this->Dimension; i++)
            this[i] /= norm;
    }

	///<summary>Computes and returns the dot product of two vectors.</summary>
	static itkVectorValueType Dot( itkVector^ a, itkVector^ b )
	{
		if ( a == nullptr || b == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		if ( a->Length != b->Length )
			throw gcnew ArgumentException("Vector lengths do not match.");

		itkVectorValueType result = 0.0;
		for( unsigned int i=0; i < a->Length; i++ ) 
        {
			result += a[i] * b[i];
		}
		return result;
	}

	///<summary>Computes and returns the cross product of two vectors.</summary>
	///<remarks>This operation is only defined for vectors of length 3.</remarks>
	static itkVector^ Cross( itkVector^ a, itkVector^ b )
	{
		if ( a == nullptr || b == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		if ( a->Length != 3 && b->Length != 3 )
			throw gcnew ArgumentException("Cross product is only defined for vectors of length 3.");

		itkVector^ c = gcnew itkVector( a->Length );
		c[0] = a[1] * b[2] - a[2] * b[1];
	    c[1] = a[2] * b[0] - a[0] * b[2];
		c[2] = a[0] * b[1] - a[1] * b[0];
		return c;
	}

}; // end ref class

} // end namespace itk

#endif