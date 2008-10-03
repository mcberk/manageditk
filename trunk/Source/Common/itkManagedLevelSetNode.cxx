/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedLevelSetNode.cxx
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

#ifndef __itkManagedLevelSetNode_cxx
#define __itkManagedLevelSetNode_cxx

// Include some managed files
#include "itkManagedIndex.cxx"

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
///This class is a managed replacement for itk::LevelSetNode.
///</summary>
///<remarks>
///LevelSetNode is a simple class that represents a node
///or grid position of a level set. A group or collection of      
///LevelSetNode can then be used to represents a narrowband or    
///region of interest.                                            
///</remarks>
public ref class itkLevelSetNode
{

private:
	double m_Value;
	itkIndex^ m_Index;

public:
    ///<summary>Default constructor.</summary>
	itkLevelSetNode (  ) { }

    ///<summary>Constructor taking a pixel value and index.</summary>
    ///<param name="value">The value of the level set node.</param>
    ///<param name="index">The discrete location in image space of the level set node.</param>
	itkLevelSetNode ( double value, itkIndex^ index ) 
	{
		this->m_Value = value;
		this->m_Index = index;
	}

    ///<summary>Constructor copying member data from an existing node.</summary>
    ///<param name="node">The existing node to copy the data from.</param>
	itkLevelSetNode ( itkLevelSetNode^ node ) 
	{
		this->m_Value = node->Value;
		this->m_Index = node->Index;
	}

    ///<summary>Get/set the value of the node.</summary>
	property virtual double Value 
	{
		double get() { return this->m_Value; }
		void set( double value ) { this->m_Value = value; } 
	}

    ///<summary>Get/set the discrete location of the node.</summary>
	property virtual itkIndex^ Index 
	{ 
		itkIndex^ get() { return this->m_Index; }
		void set( itkIndex^ index ) { this->m_Index = index; } 
	}

}; // end ref class

} // end namespace itk

#endif