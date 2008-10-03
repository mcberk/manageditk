/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedFiniteDifferenceImageFilter.cxx
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

#ifndef __itkManagedFiniteDifferenceImageFilter_cxx
#define __itkManagedFiniteDifferenceImageFilter_cxx

// Include some ManagedITK files
#include "itkManagedImageToImageFilter.cxx"

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
///This class is a managed replacement for itk::FiniteDifferenceImageFilter.
///</summary>
///<remarks>
///This class defines the generic solver API at the top level of the Finite
///Difference Solver (FDS) framework. FiniteDifferenceImageFilter is an 
///abstract class that implements the generic, high-level algorithm.
///</remarks>
public ref class itkFiniteDifferenceImageFilter  abstract : itkImageToImageFilter
{

public:
    ///<summary>Default constructor.</summary>
    ///<param name="name">A string representing the name of the ProcessObject.</param>
	itkFiniteDifferenceImageFilter( String^ name ) : itkImageToImageFilter( name )
	{ }

    ///<summary>
    ///Get the number of elapsed iterations of the filter.
    ///</summary>
    virtual property unsigned int ElapsedIterations { unsigned int get()=0; }
    
    ///<summary>
    ///Get/set the maximum number of iterations that the filter will run.
    ///</summary>
    virtual property unsigned int NumberOfIterations { unsigned int get()=0; void set( unsigned int value )=0; }
    
    ///<summary>
    ///Get/set if the image spacing information is used in calculations. 
    ///Use this option if you want derivatives in physical space.
    ///</summary>
    ///<remarks>Default is UseImageSpacingOff (ie. UseImageSpacing=False).</remarks>
    virtual property bool UseImageSpacing { bool get()=0; void set( bool value )=0; }

    ///<summary>
    ///Get/set the maximum error allowed in the solution. 
    ///This may not be defined for all solvers and its meaning may change with the application.
    ///</summary>
    virtual property double MaximumRMSError { double get()=0; void set( double value )=0; }
    
    ///<summary>
    ///Get/set the root mean squared change of the previous iteration.
    ///May not be used by all solvers.
    ///</summary>
    virtual property double RMSChange { double get()=0; void set( double value )=0; }

}; // end ref class

} // end namespace itk

#endif