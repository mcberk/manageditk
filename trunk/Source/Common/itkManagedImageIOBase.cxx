/*=============================================================================

NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

Project:   ManagedITK
Program:   Insight Segmentation & Registration Toolkit
Module:    itkManagedImageIOBase.cxx
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

#ifndef __itkManagedImageIOBase_cxx
#define __itkManagedImageIOBase_cxx

// Include some useful ManagedITK files
#include "itkManagedObject.cxx"

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
  ///This abstract class is a managed replacement for itk::ImageIOBase.
  ///</summary>
  ///<remarks>
  ///ImageIOBase is a class that reads and/or writes image data
  ///of a particular format (such as PNG or raw binary). The
  ///ImageIOBase encapsulates both the reading and writing of data. The
  ///ImageIOBase is used by the ImageFileReader class (to read data)
  ///and the ImageFileWriter (to write data) into a single file. The
  ///ImageSeriesReader and ImageSeriesWriter classes are used to read
  ///and write data (in conjunction with ImageIOBase) when the data is
  ///represented by a series of files. Normally the user does not directly
  ///manipulate this class other than to instantiate it, set the FileName,
  ///and assign it to a ImageFileReader/ImageFileWriter or
  ///ImageSeriesReader/ImageSeriesWriter.
  ///</remarks>
  public ref class itkImageIOBase abstract : itkObject
  {

  private:


  protected:
    ///<summary>Protected constructor.</summary>
    itkImageIOBase( ) : itkObject( )
    { 

    }

  public:

    ///<summary>
    ///Get/set the number of independent variables (dimensions) in the image being read or written. Note this is not necessarily what is written, rather the IORegion controls that.
    ///</summary>
    property unsigned int NumberOfDimensions
    { 
      virtual unsigned int get()=0;
      virtual void set(unsigned int value)=0;
    }

    ///<summary>
    ///Get/set a boolean to use the compression or not.
    ///</summary>
    property bool UseCompression
    { 
      virtual bool get()=0;
      virtual void set(bool value)=0;
    }
    
    ///<summary>
    ///Get/set a boolean to use streaming while reading or not.
    ///</summary>
    property bool UseStreamedReading
    { 
      virtual bool get()=0;
      virtual void set(bool value)=0;
    }
    
    ///<summary>
    ///Get/set a boolean to use streaming while writing or not.
    ///</summary>
    property bool UseStreamedWriting
    { 
      virtual bool get()=0;
      virtual void set(bool value)=0;
    }

    ///<summary>
    ///Get the image dimensions in the x, y, z, etc. directions. GetDimensions() is typically used after reading the data.
    ///</summary>
    virtual unsigned int GetDimensions(unsigned int i) = 0;

    ///<summary>
    ///Set the image dimensions in the x, y, z, etc. directions. SetDimensions() is used prior to writing the data.
    ///</summary>
    virtual void SetDimensions(unsigned int i, unsigned int dim) = 0;

    ///<summary>
    ///Determine the file type. Returns true if this ImageIO can read the file specified.
    ///</summary>
    virtual bool CanReadFile ( String^ filename ) = 0;

    ///<summary>
    ///Determine if the ImageIO can stream reading from this file. Default is false.
    ///</summary>
    virtual bool CanStreamRead ( ) = 0;

    ///<summary>
    ///Determine the file type. Returns true if this ImageIO can write the file specified.
    ///</summary>
    virtual bool CanWriteFile ( String^ filename ) = 0;

    ///<summary>
    ///Determine if the ImageIO can stream writing to this file. Default is false.
    ///</summary>
    virtual bool CanStreamWrite ( ) = 0;

    ///<summary>
    ///The different types of ImageIO's can support data of varying dimensionality. For example, some file formats are strictly 2D while others can support 2D, 3D, or even n-D. This method returns true/false as to whether the ImageIO can support the dimension indicated.
    ///</summary>
    virtual bool SupportsDimension ( unsigned long dim ) = 0;

  }; // end ref class

} // end namespace

#endif
