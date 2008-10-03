/*=============================================================================

  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedCell.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date$
  Revision:  $Revision$

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

#ifndef __itkManagedCell_cxx
#define __itkManagedCell_cxx

// Include some managed files
#include "itkManagedPoint.cxx"

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

///<summary>This enumeration lists all the possible cell types (see itkCellInterface.h).</summary>
public enum class itkCellTypeEnum
{
    VertexCellType = 0,
    LineCellType,
    TriangleCellType,
    QuadrilateralCellType,
    PolygonCellType,
    TetrahedronCellType,
    HexahedronCellType,
    QuadraticEdgeCellType,
    QuadraticTriangleCellType,
    LastItkCellType,
    MaxItkCellsType = 255
};

///<summary>
///This class is a managed replacement for itk::CellInterface.
///</summary>
///<remarks>
///Define an abstract interface for cells. Actual cell types derive from this class.
///</remarks>
public ref class itkCell
{

private:
    itkCellTypeEnum m_Type;
    unsigned int m_Dimension;
    array<unsigned long>^ m_PointIds;

public:
    ///<summary>Default constructor.</summary>
    itkCell (  ) { }

    ///<summary>Constructor taking a pixel value and index.</summary>
    ///<param name="type">The type of the cell.</param>
    ///<param name="dim">The dimension of the cell.</param>
    ///<param name="pointids">The list of point identifiers (indices) defining the cell.</param>
    itkCell ( itkCellTypeEnum type, unsigned int dim, array< unsigned long >^ pointids )
    {
        this->m_Type = type;
        this->m_Dimension = dim;
        this->m_PointIds = pointids;
    }

    ///<summary>Constructor copying member data from an existing cell.</summary>
    ///<param name="cell">The existing cell to copy the data from.</param>
    itkCell ( itkCell^ cell )
    {
        this->m_Type = cell->Type;
        this->m_Dimension = cell->Dimension;
        this->m_PointIds = (array<unsigned long>^)cell->PointIds->Clone();
    }

    ///<summary>Get the cell type.</summary>
    property virtual itkCellTypeEnum Type
    {
        itkCellTypeEnum get() { return this->m_Type; }
    }

    ///<summary>Get the dimension of the cell.</summary>
    property virtual unsigned int Dimension
    {
        unsigned int get() { return this->m_Dimension; }
    }

    ///<summary>Get the number of points in the cell.</summary>
    property virtual unsigned int NumberOfPoints
    {
        unsigned int get() { return static_cast<unsigned int>( this->m_PointIds->Length ); }
    }

    ///<summary>Get the point identifiers (indices) defining the cell.</summary>
    property virtual array<unsigned long>^ PointIds
    {
        array<unsigned long>^ get() { return this->m_PointIds; }
    }

}; // end ref class

} // end namespace itk

#endif