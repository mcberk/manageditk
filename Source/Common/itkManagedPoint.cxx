/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedPoint.cxx
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

#ifndef __itkManagedPoint_cxx
#define __itkManagedPoint_cxx

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::ComponentModel;
using namespace System::Diagnostics;

// Some Managed ITK inludes
#include "itkManagedArray.cxx"
#include "itkManagedVector.cxx"

namespace itk
{

#define itkPointValueType System::Double

///<summary>
///This class is a managed replacement for itk::Point.
///</summary>
///<remarks>
///An Point represents an n-Dimensional geometric point in physical space.
///</remarks>
public ref class itkPoint : itkArray<itkPointValueType>
{

public:
	///<summary>Constructor taking the data values as a params array.</summary>
	///<param name="data">The variable length data array. The dimension will be initialised as data.Length.</param>
	itkPoint ( ... array<itkPointValueType>^ data ) : itkArray( data )
	{ }

	///<summary>Constructor taking the number of dimensions for the array.</summary>
	///<remarks>The data values are initialised as zero.</remarks>
	///<param name="dimension">The dimensionality of the array to initialise.</param>
	itkPoint( unsigned int dimension ) : itkArray( dimension )
	{ }

	///<summary>Constructor taking another array.</summary>
	///<param name="other">Another array to clone the data from.</param>
	itkPoint ( itkPoint^ other) : itkArray( other->Data )
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
        itkPoint^ right = safe_cast< itkPoint^ >(obj);

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
	///Compares two itkPoint objects.
	///They are equal if they have the same dimensionality AND data.
	///</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>true AND the objects are equal OR false AND the objects are not equal.</returns>
    static bool operator ==(itkPoint^ lhs, itkPoint^ rhs)
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
	///Compares two itkPoint objects.
	///They are not equal if they do not have the same dimensionality OR 
	///do not have the same data.
	///</summary>
    ///<param name="rhs"></param>
    ///<returns>true AND the objects are not equal OR false AND the objects are equal.</returns>
    virtual bool operator !=(itkPoint^ rhs)
    {
        return !(this == rhs);
    }

    ///<summary>Performs an element-wise addition.</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>A new itkVector instance with data as the element-wise addition.</returns>
    static itkVector^ operator+(itkPoint^ lhs, itkPoint^ rhs)
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
    static itkVector^ operator-(itkPoint^ lhs, itkPoint^ rhs)
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

    ///<summary>Move the point in the direction of the given vector.</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>A new itkPoint instance with each data element offset by the vector element.</returns>
    static itkPoint^ operator+(itkPoint^ lhs, itkVector^ rhs)
    {
		if ( lhs == nullptr || rhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkPoint^ result = gcnew itkPoint( lhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = lhs[i] + rhs[i];
            return result;
		}
    }

    ///<summary>Move the point in the opposite direction of the given vector.</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>A new itkPoint instance with each data element offset by the vector element.</returns>
    static itkPoint^ operator-(itkPoint^ lhs, itkVector^ rhs)
    {
		if ( lhs == nullptr || rhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else
		{
            itkPoint^ result = gcnew itkPoint( lhs->Dimension );
            for (unsigned int i = 0; i < result->Dimension; i++)
                result[i] = lhs[i] - rhs[i];
            return result;
		}
    }

    ///<summary>Computes the squared Euclidean distance from this to the given point.</summary>
    ///<param name="point">The other point used in the calculation.</param>
    ///<returns>The squared Euclidean distance from this to the given point.</returns>
	virtual double SquaredEuclideanDistanceTo(itkPoint^ point)
	{
		double sum = 0.0;
		for (unsigned int i=0; i<point->Length; i++ )
		{
			double difference = this[i] - point[i];
			sum += (difference * difference);
		}
		return sum;
	}

    ///<summary>Computes the distance from this to the given point.</summary>
    ///<param name="point">The other point used in the calculation.</param>
    ///<returns>The Euclidean distance from this to the given point.</returns>
	virtual double EuclideanDistanceTo(itkPoint^ point)
	{
		return System::Math::Sqrt(this->SquaredEuclideanDistanceTo(point) );
	}

}; // end ref class

} // end namespace itk

#endif