/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedSpatialObjectBase.cxx
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

#ifndef __itkManagedSpatialObject_cxx
#define __itkManagedSpatialObject_cxx

// Include some useful ManagedITK files
#include "itkManagedObject.cxx"
#include "itkManagedDataObject.cxx"
#include "itkManagedArray.cxx"
#include "itkManagedPoint.cxx"
#include "itkManagedVector.cxx"
#include "itkManagedSpacing.cxx"
#include "itkManagedTransform.cxx"
#include "itkManagedImageRegion.cxx"

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
///This abstract class is a managed replacement for itk::SpatialObject.
///</summary>
public ref class itkSpatialObjectBase abstract : itkDataObject
{

public:
	///<summary>Get the object dimensions.</summary>
	property unsigned int ObjectDimension
	{
		virtual unsigned int get() = 0;
	}
	
	///<summary>Get the SpatialObject type string.</summary>
	property String^ TypeName
	{
		virtual String^ get() = 0;
	}
	
	///<summary>Get the SpatialObject type string.</summary>
	property String^ SpatialObjectTypeAsString
	{
		virtual String^ get() = 0;
	}

    ///<summary>Get/set the ObjectToWorldTransform (a ScalableAffineTransform).</summary>
	property itkTransform^ ObjectToWorldTransform
	{
		virtual itkTransform^ get() = 0;
		virtual void set(itkTransform^ transform) = 0;
	}

    ///<summary>Get/set the ObjectToParentTransform (a ScalableAffineTransform).</summary>
	property itkTransform^ ObjectToParentTransform
	{
		virtual itkTransform^ get() = 0;
		virtual void set(itkTransform^ transform) = 0;
	}
	
	///<summary>
	///Get/set the region object that defines the size and starting index
    ///for the largest possible region this SpatialObject could represent.
	///</summary>
	property itkImageRegion^ LargestPossibleRegion
	{ 
		virtual itkImageRegion^ get() = 0;
		virtual void set ( itkImageRegion^ region ) = 0;
	}

	///<summary>
	///Get/set the region object that defines the size and starting index
    ///for the region of the SpatialObject requested (i.e., the region of the
    ///image to be operated on by a filter). Setting the RequestedRegion
    ///does not cause the object to be modified.
	///</summary>
	property itkImageRegion^ RequestedRegion 
	{ 
		virtual itkImageRegion^ get() = 0;
		virtual void set ( itkImageRegion^ region ) = 0;
	}

	///<summary>
	///Get/set the region object that defines the size and starting index
    ///of the region of the SpatialObject currently loaded in memory.
	///</summary>
	property itkImageRegion^ BufferedRegion 
	{ 
		virtual itkImageRegion^ get() = 0;
		virtual void set ( itkImageRegion^ region ) = 0;
	}

	///<summary>Get/set the spacing.</summary>
	property itkSpacing^ Spacing
	{
		virtual itkSpacing^ get() = 0;
		virtual void set( itkSpacing^ spacing ) = 0;
	}

	///<summary>
    ///Compute the World transform when the local transform is set
    ///This function should be called each time the local transform
    ///has been modified.
    ///</summary>
	virtual void ComputeObjectToWorldTransform ( ) = 0;

    ///<summary>
    ///Compute the Local transform when the global transform is set.
    ///</summary>
	virtual void ComputeObjectToParentTransform ( ) = 0;
	
    ///<summary>
    ///Returns the value at a point.
    ///</summary>
	virtual bool ValueAt ( itkPoint^ point, double & value ) = 0;

    ///<summary>
    ///Returns true if the object can provide a "meaningful" value at
    ///a point. Often defaults to returning same answer as IsInside, but
    ///certain objects influence space beyond their spatial extent.
    ///</summary>
	virtual bool IsEvaluableAt ( itkPoint^ point ) = 0;
	
    ///<summary>
    ///Returns true if a point is inside the object.
    ///</summary>
	virtual bool IsInside ( itkPoint^ point ) = 0;
	
    ///<summary>
    ///Add an object to the list of children.
    ///</summary>
	virtual void AddSpatialObject ( itkSpatialObjectBase^ object ) = 0;

    ///<summary>
    ///Remove the object passed as arguments from the list of children.
    ///</summary>
	virtual void RemoveSpatialObject ( itkSpatialObjectBase^ object ) = 0;
	
    ///<summary>
    ///Set the native pointer of the given object to the parent object in the hierarchy tree.
    ///</summary>
	virtual void GetParent ( itkSpatialObjectBase^ parent ) = 0;
	
	///<summary>
    ///Clear the spatial object by deleting all lists of children and subchildren.
    ///</summary>
	virtual void Clear ( ) = 0;
	
	///<summary>
    ///Return the number of children directly under this SpatialObject.
    ///</summary>
	virtual unsigned int GetNumberOfChildren ( ) = 0;
	
	///<summary>
    ///Return the number of children under this SpatialObject to the given depth.
    ///</summary>
	virtual unsigned int GetNumberOfChildren ( unsigned int depth ) = 0;
	
	///<summary>
    ///Returns a list of pointer to the children affiliated to this object.
    ///A depth of 0 returns the immediate childred. A depth of 1 returns the
    ///children and those children's children.
    ///</summary>
	virtual array<itkSpatialObjectBase^>^ GetChildren ( unsigned int depth ) = 0;


}; // end ref class

} // end namespace itk

#endif