/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImageRegion.cxx
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

#ifndef __itkManagedImageRegion_cxx
#define __itkManagedImageRegion_cxx

// Include some managed files
#include "itkManagedSize.cxx"
#include "itkManagedIndex.cxx"
#include "itkManagedContinuousIndex.cxx"

// Use some managed namespaces
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
///This class is a managed replacement for itk::ImageRegion.
///</summary>
///<remarks>
///ImageRegion is an class that represents some structured portion or
///piece of an Image. The ImageRegion is represented with an index and
///a size in each of the n-dimensions of the image. (The index is the
///corner of the image, the size is the lengths of the image in each of
///the topological directions.)
///</remarks>
public ref class itkImageRegion
{

private:
	itkSize^ m_Size;
	itkIndex^ m_Index;

public:
    ///<summary>Default constructor.</summary>
	itkImageRegion (  ) { }

    ///<summary>Constructor taking an existing size and index.</summary>
    ///<param name="size">The size to set within the new image region.</param>
    ///<param name="index">The index to set within the new image region.</param>
	itkImageRegion ( itkSize^ size, itkIndex^ index ) 
	{
		if (size->Dimension != index->Dimension)
			throw gcnew ArgumentException( "The size and index of the image region must have the same dimensionality." );
		
		this->m_Size = size;
		this->m_Index = index;
	}

	///<summary>Get the dimensionality of the region.</summary>
	property virtual unsigned int Dimension 
	{ 
		unsigned int get() { return this->m_Size->Dimension; }
	}

	///<summary>Get/set the size of the image region.</summary>
	property virtual itkSize^ Size 
	{ 
		itkSize^ get() { return this->m_Size; }
		void set( itkSize^ size ) { this->m_Size = size; } 
	}

	///<summary>Get/set the index of the image region.</summary>
	property virtual itkIndex^ Index 
	{ 
		itkIndex^ get() { return this->m_Index; }
		void set( itkIndex^ index ) { this->m_Index = index; } 
	}

	///<summary>Test if an index is inside the image region.</summary>
    ///<returns>True if inside, false otherwise.</returns>
	bool IsInside ( itkIndex^ index )
	{
		for(unsigned int i=0; i<index->Length; i++)
        {
			if ( index[i] < this->Index[i] ) 
			  return false;
			if ( index[i] >= this->Index[i] + this->Size[i] ) 
			  return false;
        }
		return true;
	}

	///<summary>Test if a continuous index is inside the image region.</summary>
    ///<returns>True if inside, false otherwise.</returns>
	bool IsInside ( itkContinuousIndex^ cindex )
	{
		for (unsigned int i=0; i<cindex->Length; i++)
        {
			if ( cindex[i] < this->Index[i] ) 
				return false;
			if ( cindex[i] >= (this->Index[i] + this->Size[i]) )
				return false;
        }
		return true;
	}

	///<summary>
	///Pad an image region by the specified radius uniformly in all dimensions.
	///</summary>
	void PadByRadius( System::Int32 radius )
	{
		array<System::Int32>^ radiusArray = gcnew array<System::Int32>( this->Dimension );
		for (unsigned int i=0; i < this->Dimension; ++i)
			radiusArray[i] = radius;
		this->PadByRadius( radiusArray );
	}

	///<summary>
	///Pad an image region by the specified radius.
	///</summary>
	void PadByRadius( itkSize^ radius )
	{
		this->PadByRadius( radius->Data );
	}

	///<summary>
	///Pad an image region by the specified radius.
	///</summary>
	void PadByRadius( array<System::Int32>^ radius )
	{
		for (unsigned int i = 0; i < this->Dimension; i++)
		{
			m_Size[i]  += 2 * radius[i];
			m_Index[i] -= radius[i];
		}  
	}

	///<summary>
	///Crop a region by another region. If this region is outside of the crop,
	///this method returns false and does not modify the region. Otherwise,
	///this method returns true and the region ismodified to reflect the crop.
    ///</summary>
	bool Crop ( itkImageRegion^ region )
	{
		System::Int32 crop;
		unsigned int i;
		bool cropPossible = (this->Dimension == region->Dimension);

		// Can we crop?
		for (i = 0; i < region->Dimension && cropPossible; i++)
		{
			// Is left edge of current region to the right of the right edge
			// of the region to crop with? (if so, we cannot crop)
			if ( m_Index[i] >= region->Index[i] + region->Size[i] )
				cropPossible = false;

			// If right edge of the current region to the left of the left
			// edge of the region to crop with? (if so, we cannot crop)
			if ( m_Index[i] + m_Size[i] <= region->Index[i] )
				cropPossible = false;
		}

		// If we cannot crop, return without changing anythin
		if (!cropPossible)
			return cropPossible;

		// We can crop, so crop
		for (i=0; i < region->Dimension; i++)
		{
			// First check the start index
			if (m_Index[i] < region->Index[i])
			{
				// How much do we need to adjust
				crop = region->Index[i] - m_Index[i];

				// Adjust the start index and the size of the current region
				m_Index[i] += crop;
				m_Size[i] -= crop;
			}

			// Now check the final size
			if ( m_Index[i] + m_Size[i] > region->Index[i] + region->Size[i] )
			{
				// How much do we need to adjust
				crop = m_Index[i] + m_Size[i] - region->Index[i] - region->Size[i];

				// Adjust the size
				m_Size[i] -= crop;
			}
		}

		return cropPossible;
	}

	///<summary>Returns a string representation of the itkImageRegion.</summary>
	///<returns>A string representation in the format "Index=[XXX,XXX,..] Size=[XXX,XXX,..]".</returns>
	virtual String^ ToString() override
    {
		return "Index=" + this->Index->ToString() + " Size=" + this->Size->ToString();
	}

}; // end ref class

} // end namespace itk

#endif