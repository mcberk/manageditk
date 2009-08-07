/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedContinuousIndex.cxx
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

#ifndef __itkManagedContinuousIndex_cxx
#define __itkManagedContinuousIndex_cxx

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
#include "itkManagedIndex.cxx"

namespace itk
{

#define itkContinuousIndexValueType System::Double

///<summary>
///This class is a managed replacement for itk::ContinuousIndex.
///</summary>
///<remarks>
///A ContinuousIndex represents an n-Dimensional real-valued point in pixel space.
///</remarks>
public ref class itkContinuousIndex : itkArray<itkContinuousIndexValueType>
{

public:
	///<summary>Constructor taking the data values as a params array.</summary>
	///<param name="data">The variable length data array. The dimension will be initialised as data.Length.</param>
	itkContinuousIndex ( ... array<itkContinuousIndexValueType>^ data ) : itkArray( data )
	{ }

	///<summary>Constructor taking the number of dimensions for the array.</summary>
	///<remarks>The data values are initialised as zero.</remarks>
	///<param name="dimension">The dimensionality of the array to initialise.</param>
	itkContinuousIndex( unsigned int dimension ) : itkArray( dimension )
	{ }

	///<summary>Constructor taking another array.</summary>
	///<param name="other">Another array to clone the data from.</param>
	itkContinuousIndex ( itkContinuousIndex^ other) : itkArray( other->Data )
	{ }

	///<summary>Constructor which copies member data from an existing itkIndex object.</summary>
	///<param name="index">The existing itkIndex object to copy from.</param>
	itkContinuousIndex( itkIndex^ index ) : itkArray( index->Dimension )
	{
		for (unsigned int i=0; i<this->Dimension; i++)
			this->Data[i] = (itkContinuousIndexValueType)index[i];
	}

    ///<summary>Converts this to a discrete itkIndex by rounding 'away from zero'.</summary>
    ///<remarks>Uses MidpointRounding::AwayFromZero to perform rounding.</remarks>
	virtual itkIndex^ ToIndex()
    {
        itkIndex^ index = gcnew itkIndex(this->Dimension);
        for (unsigned int i=0; i<this->Dimension; i++)
            index[i] += (int)System::Math::Round(this[i], MidpointRounding::AwayFromZero);
        return index;
    }

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
        itkContinuousIndex^ right = safe_cast< itkContinuousIndex^ >(obj);

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
	///Compares two itkContinuousIndex objects.
	///They are equal if they have the same dimensionality AND data.
	///</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>true AND the objects are equal OR false AND the objects are not equal.</returns>
	static bool operator ==(itkContinuousIndex^ lhs, itkContinuousIndex^ rhs)
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
	///Compares two itkContinuousIndex objects.
	///They are not equal if they do not have the same dimensionality OR 
	///do not have the same data.
	///</summary>
    ///<param name="rhs"></param>
    ///<returns>true AND the objects are not equal OR false AND the objects are equal.</returns>
    virtual bool operator !=(itkContinuousIndex^ rhs)
    {
        return !(this == rhs);
    }

}; // end ref class

} // end namespace itk

#endif