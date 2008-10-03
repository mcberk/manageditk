/*=============================================================================

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedMultiThreader.cxx
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

#ifndef __itkManagedMultiThreader_cxx
#define __itkManagedMultiThreader_cxx

// Include some useful ITK headers
#pragma unmanaged
#include "itkMultiThreader.h"

// Use some managed namespaces
#pragma managed
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::ComponentModel;
using namespace System::Diagnostics;

// Some other necessary includes
namespace itk
{

///<summary>
///This class is a managed type instance for itk::MultiThreader.
///</summary>
public ref class itkMultiThreader
{

public:
    static property int GlobalMaximumNumberOfThreads
    {
        int get( )
        { return itk::MultiThreader::GetGlobalMaximumNumberOfThreads( ); }
        void set( int value )
        { itk::MultiThreader::SetGlobalMaximumNumberOfThreads( value ); }
    }
    
    static property int GlobalDefaultNumberOfThreads
    {
        int get( )
        { return itk::MultiThreader::GetGlobalDefaultNumberOfThreads( ); }
        void set( int value )
        { itk::MultiThreader::SetGlobalDefaultNumberOfThreads( value ); }
    }

}; // end ref class

} // end namespace itk

#endif
