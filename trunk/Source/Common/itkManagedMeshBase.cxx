/*=============================================================================

  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedMeshBase.cxx
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

#ifndef __itkManagedMeshBase_cxx
#define __itkManagedMeshBase_cxx

// Include some useful ManagedITK files
#include "itkManagedPointSetBase.cxx"
#include "itkManagedCell.cxx"

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
///This abstract class is a managed replacement for itk::Mesh.
///</summary>
///<remarks>
///An N-dimensional mesh structure.
///</remarks>
public ref class itkMeshBase abstract : itkPointSetBase
{

public:
    ///<summary>Get the number of cells comprising this mesh.</summary>
    property unsigned long NumberOfCells { virtual unsigned long get( ) = 0; }

    ///<summary>Return the pointer to the native CellsContainerPointer.</summary>
    virtual IntPtr GetCells( ) = 0;

    ///<summary>Return a managed array of cells.</summary>
    ///<remarks>This method steps through the cell array and duplicates each index in to managed memory. It operates irrespective of the mesh traits.</remarks>
    virtual array<itkCell^>^ GetCellsAsArray( ) = 0;

    ///<summary>Copy the array of cell indicies to the given memory location. For this method to be useful, all cells must have the same number of points (ie. all LINE_CELL, all TRIANGLE_CELL, etc).</summary>
    ///<param name="arrayptr">The memory location to write the cell indices. It is the caller's responsiblity to ensure enough memory has been allocated.</param>
    virtual void GetCellIndicesAsArray( IntPtr arrayptr ) = 0;

    ///<summary>Set the cells from the given memory location. This method only creates meshes with homogenuous cells (ie. all cells are the same).</summary>
    ///<param name="numberOfCells">The number of cells in the array. The array will have (numberOfCells * NumberOfPoints in cell) values.</param>
    ///<param name="arrayptr">The memory location to read the cells. It is the caller's responsiblity to ensure the array has the correct number of values.</param>
    virtual void SetCellIndicesAsArray( unsigned int numberOfCells, itkCellTypeEnum cellType, IntPtr arrayptr ) = 0;

}; // end ref class

} // end namespace itk

#endif