/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedMatrix.cxx
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

#ifndef __itkManagedMatrix_cxx
#define __itkManagedMatrix_cxx

// Include some useful ManagedITK files
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

#define itkMatrixValueType System::Double

///<summary>
///This class is a managed replacement for itk::Matrix.
///</summary>
public ref class itkMatrix
{
private:
	unsigned int m_NumberOfRows;
	unsigned int m_NumberOfCols;
	array<itkMatrixValueType>^ m_Data;

public:
	///<summary>
	///Constructor taking the number of rows and columns.
	///The matrix is initialised to all zeros.
	///</summary>
	///<param name="numrows">The number of rows in the matrix.</param>
	///<param name="numcols">The number of columns in the matrix.</param>
	itkMatrix ( unsigned int numrows, unsigned int numcols )
	{
		this->m_NumberOfRows = numrows;
		this->m_NumberOfCols = numcols;
		this->m_Data = gcnew array<itkMatrixValueType>( numrows*numcols );
		this->Fill( 0.0 );
	}

	///<summary>
	///Static constructor creating a new matrix set to the identity.
	///</summary>
	///<param name="numrows">The number of rows in the matrix.</param>
	///<param name="numcols">The number of columns in the matrix.</param>
	static itkMatrix^ NewIdentity ( unsigned int numrows, unsigned int numcols )
	{
		itkMatrix^ result = gcnew itkMatrix( numrows, numcols );
		result->SetIdentity( );
		return result;
	}

	///<summary>
	///Static constructor creating a new matrix set to all zeros.
	///</summary>
	///<param name="numrows">The number of rows in the matrix.</param>
	///<param name="numcols">The number of columns in the matrix.</param>
	static itkMatrix^ NewZeros ( unsigned int numrows, unsigned int numcols )
	{
		itkMatrix^ result = gcnew itkMatrix( numrows, numcols );
		return result;
	}

	///<summary>Get the number of rows in the Matrix.</summary>
	property unsigned int NumberOfRows
	{
		unsigned int get() { return this->m_NumberOfRows; }
	}

	///<summary>Get the number of columns in the Matrix.</summary>
	property unsigned int NumberOfCols
	{
		unsigned int get() { return this->m_NumberOfCols; }
	}

	///<summary>Get the underlying data array.</summary>
	property array<itkMatrixValueType>^ Data
	{
		array<itkMatrixValueType>^ get() { return this->m_Data; }
	}

	///<summary>Get/set the value at the given [row, col].</summary>
	property itkMatrixValueType default[unsigned int, unsigned int]
	{
		itkMatrixValueType get(unsigned int row, unsigned int col) 
		{ return this->m_Data[row*m_NumberOfRows + col]; }
		void set(unsigned int row, unsigned int col, itkMatrixValueType value) 
		{ this->m_Data[row*m_NumberOfRows + col] = value; }
	}

    ///<summary>Get the specified matrix component.</summary>
    ///<param name="row">The matrix row.</param>
    ///<param name="col">The matrix column.</param>
	///<returns>A reference to the matrix component at [row, col].</returns>
    virtual itkMatrixValueType Get( unsigned int row, unsigned int col )
	{
		return this[row, col];
	}

    ///<summary>Set the specified matrix component.</summary>
    ///<param name="row">The matrix row.</param>
    ///<param name="col">The matrix column.</param>
	///<param name="value">The value for [row, col].</param>
    virtual void Set( unsigned int row, unsigned int col, itkMatrixValueType value )
	{
		this[row, col] = value;
	}

    ///<summary>Set the matrix to identity.</summary>
    virtual void SetIdentity( )
	{
		this->Fill(0.0);
		for (unsigned int i = 0; i<System::Math::Min(m_NumberOfRows, m_NumberOfCols); i++)
			this[i,i] = 1.0;
	}

    ///<summary>Fill the matrix with a value.</summary>
    virtual void Fill( itkMatrixValueType value )
	{
		for (unsigned int i = 0; i<m_NumberOfRows*m_NumberOfCols; i++)
			this->m_Data[i] = value;
	}

    ///<summary>Performs matrix multiplication.</summary>
    ///<param name="lhs"></param>
    ///<param name="rhs"></param>
    ///<returns>The resultant itkMatrix from multiplying lhs with rhs.</returns>
    static itkMatrix^ operator*(itkMatrix^ lhs, itkMatrix^ rhs)
    {
		if ( lhs == nullptr || rhs == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else if ( lhs->NumberOfRows != rhs->NumberOfRows )
			throw gcnew ArgumentException("Number of rows for left and right hand sides do not match.");
		else if ( lhs->NumberOfCols != rhs->NumberOfCols )
			throw gcnew ArgumentException("Number of columns for left and right hand sides do not match.");
		else
		{
			itkMatrix^ result = gcnew itkMatrix( lhs->NumberOfRows, lhs->NumberOfCols );
			for (unsigned i = 0; i < lhs->NumberOfRows; i++) {		 // For each row
				for (unsigned j = 0; j < rhs->NumberOfCols; j++) {	 // For each column
					itkMatrixValueType sum = 0;
					for (unsigned k = 0; k < lhs->NumberOfCols; k++) // For each column
						sum += (lhs[i,k] * rhs[k,j]);
					result[i,j] = sum;
				}
			}
            return result;
		}
    }

	///<summary>Product by a vector.</summary>
    ///<param name="vector"></param>
    ///<param name="matrix"></param>
    ///<returns>The itkVector after multiplying vector by matrix.</returns>
    static itkVector^ operator*(itkVector^ vector, itkMatrix^ matrix)
    {
		if ( vector == nullptr || matrix == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else if ( vector->Dimension != matrix->NumberOfRows )
			throw gcnew ArgumentException("Incompatiable lengths.");
		else
		{
			itkVector^ result = gcnew itkVector( vector->Dimension );			
			for( unsigned int r=0; r<matrix->NumberOfRows; r++)
			{
				itkMatrixValueType sum = 0.0;   
				for( unsigned int c=0; c<matrix->NumberOfCols; c++ ) 
				{
					sum += matrix[r,c] * vector[c];
				}
				result[r] = sum;
			}
            return result;
		}
    }

	///<summary>Product by a point.</summary>
    ///<param name="point"></param>
    ///<param name="matrix"></param>
    ///<returns>The itkPoint after multiplying point by matrix.</returns>
    static itkPoint^ operator*(itkPoint^ point, itkMatrix^ matrix)
    {
		if ( point == nullptr || matrix == nullptr )
			throw gcnew ArgumentNullException("Can not operate on nullptr objects.");
		else if ( point->Dimension != matrix->NumberOfRows )
			throw gcnew ArgumentException("Incompatiable lengths.");
		else
		{
			itkPoint^ result = gcnew itkPoint( point->Dimension );			
			for( unsigned int r=0; r<matrix->NumberOfRows; r++)
			{
				itkMatrixValueType sum = 0.0;   
				for( unsigned int c=0; c<matrix->NumberOfCols; c++ ) 
				{
					sum += matrix[r,c] * point[c];
				}
				result[r] = sum;
			}
            return result;
		}
    }

	///<summary>
	///Converts the Matrix to a string representation.
	///</summary>
    ///<returns>A string representation of the matrix.</returns>
	virtual String^ ToString() override
    {
		String^ result = String::Empty;
		for (unsigned int i = 0; i<m_NumberOfRows*m_NumberOfCols; i++)
			result += this->m_Data[i].ToString() + " ";
		return result->Trim(' ');
	}

}; // end ref class

} // end namespace itk

#endif