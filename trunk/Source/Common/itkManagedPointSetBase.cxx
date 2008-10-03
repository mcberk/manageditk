/*=============================================================================

  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedPointSetBase.cxx
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

#ifndef __itkManagedPointSetBase_cxx
#define __itkManagedPointSetBase_cxx

// Include some useful ManagedITK files
#include "itkManagedDataObject.cxx"
#include "itkManagedPoint.cxx"

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
///This class is used to specify an instance type for MeshTraits.
///</summary>
///<remarks>
///It can be used to specify the instance type of itkPointSet and itkMesh to create.
///</remarks>
public ref class itkMeshTraits : INativePointer
{
public:
    ///<summary>A managed enumerated type for the mesh traits type.</summary>
    enum class MeshTraitsEnum
    {
        Static,
        Dynamic
    };

private:
    MeshTraitsEnum m_Type;

public:
    ///<summary>Create a static mesh traits object.</summary>
    static itkMeshTraits^ Static(  )
    {
        return gcnew itkMeshTraits( MeshTraitsEnum::Static );
    }

    ///<summary>Create a dynamic mesh traits object.</summary>
    static itkMeshTraits^ Dynamic( )
    {
        return gcnew itkMeshTraits( MeshTraitsEnum::Dynamic );
    }

    ///<summary>Default constructor accepting the mesh traits type.</summary>
    itkMeshTraits( MeshTraitsEnum type )
    {
        this->m_Type = type;
    }

    ///<summary>Get the mesh traits type, static or dynamic.</summary>
    property MeshTraitsEnum Type
    {
        MeshTraitsEnum get() { return this->m_Type; }
    }

    ///<summary>Get a string representing the type instance of this INativePointer.</summary>
    ///<example>"S", "D".</example>
    ///<remarks>
    ///This object can be passed to the New() methods to specify the type of
    ///native itk object to create.
    ///</remarks>
    property String^ MangledTypeString
    {
        virtual String^ get()
        {
            switch( m_Type )
            {
            case itkMeshTraits::MeshTraitsEnum::Static:
                return "S";
            case itkMeshTraits::MeshTraitsEnum::Dynamic:
                return "D";
            default:
                return "S";
            }
        }
    }

    ///<summary>
    ///Get/set the pointer to the native ITK object associated with
    ///this wrapper instance.
    ///</summary>
    ///<returns>The pointer to the native ITK object.</returns>
    ///<remarks>
    ///This property is not applicable for itkMeshTraits and will always get/set 0.
    ///</remarks>
    property IntPtr NativePointer
    {
        virtual IntPtr get( ) { return IntPtr::Zero; };
        virtual void set ( IntPtr ptr ) { /*Do nothing*/ };
    }

}; // end ref class


///<summary>
///This abstract class is a managed replacement for itk::PointSet.
///</summary>
///<remarks>
///A superclass of the N-dimensional mesh structure.
///</remarks>
public ref class itkPointSetBase abstract : itkDataObject
{

public:
    ///<summary>Get the number of points comprising this set.</summary>
    property unsigned long NumberOfPoints { virtual unsigned long get( ) = 0; }

    ///<summary>Return the pointer to the native PointsContainer.</summary>
    virtual IntPtr GetPoints( ) = 0;

    ///<summary>Return a managed array of points.</summary>
    ///<remarks>This method steps through the points array and duplicates each point in to managed memory. It operates irrespective of the mesh traits.</remarks>
    virtual array<itkPoint^>^ GetPointsAsArray( ) = 0;

    ///<summary>Copy the array of points from the mesh to the given memory location.</summary>
    ///<param name="arrayptr">The memory location to write the points. It is the caller's responsiblity to ensure enough memory has been allocated.</param>
    virtual void GetPointsAsArray( IntPtr arrayptr ) = 0;

    ///<summary>Set the array of points from the given managed array.</summary>
    ///<param name="array">The managed array of points to add to the point set.</param>
    virtual void SetPointsAsArray( array<itkPoint^>^ array ) = 0;

    ///<summary>Set the array of points from the given memory location.</summary>
    ///<param name="numberOfPoints">The number of points in the array. The array will have (numberOfPoints * PointDimension) values.</param>
    ///<param name="arrayptr">The memory location to read the points. It is the caller's responsiblity to ensure the array has the correct number of values.</param>
    virtual void SetPointsAsArray( unsigned int numberOfPoints, IntPtr arrayptr ) = 0;

}; // end ref class

} // end namespace itk

#endif