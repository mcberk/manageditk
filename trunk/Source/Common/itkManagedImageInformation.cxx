/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImageInformation.cxx
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

#ifndef __itkManagedImageInformation_cxx
#define __itkManagedImageInformation_cxx

// Include some managed files
#include "itkManagedSize.cxx"
#include "itkManagedSpacing.cxx"
#include "itkManagedPoint.cxx"
#include "itkManagedPixelType.cxx"

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
///This structures holds information regarding the image dimension, pixeltype,
///size, spacing, etc.
///</summary>
///<remarks>This class was added to ManagedITK for simplicity.</remarks>
public ref struct itkImageInformation
{

private:
	itkPixelType^ m_PixelType;
	unsigned int m_Dimension;
	itkSize^ m_Size;
	itkSpacing^ m_Spacing;
	itkPoint^ m_Origin;

public:
    ///<summary>Default constructor.</summary>
	itkImageInformation ( itkPixelType^ pixeltype, unsigned int dimension, itkSize^ size, itkSpacing^ spacing, itkPoint^ origin )
	{
		this->m_PixelType = pixeltype;
		this->m_Dimension = dimension;
		this->m_Size = size;
		this->m_Spacing = spacing;
		this->m_Origin = origin;
	}

	///<summary>Get the pixel type of the image.</summary>
	property virtual itkPixelType^ PixelType 
	{ 
		itkPixelType^ get() { return this->m_PixelType; }
	}

	///<summary>Get the dimensionality of the image.</summary>
	property virtual unsigned int Dimension 
	{ 
		unsigned int get() { return this->m_Dimension; }
	}
	
	///<summary>Get the size of the image.</summary>
	property virtual itkSize^ Size 
	{ 
		itkSize^ get() { return this->m_Size; }
	}

	///<summary>Get the spacing of the image.</summary>
	property virtual itkSpacing^ Spacing 
	{ 
		itkSpacing^ get() { return this->m_Spacing; }
	}
	
	///<summary>Get the origin of the image.</summary>
	property virtual itkPoint^ Origin
	{ 
		itkPoint^ get() { return this->m_Origin; }
	}

}; // end ref struct

} // end namespace itk

#endif