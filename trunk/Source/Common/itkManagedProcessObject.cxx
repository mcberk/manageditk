/*=============================================================================

NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

Project:   ManagedITK
Program:   Insight Segmentation & Registration Toolkit
Module:    itkManagedProcessObject.cxx
Language:  C++/CLI
Author:    Dan Mueller
Date:      $Date: 2008-06-15 19:37:32 +0200 (Sun, 15 Jun 2008) $
Revision:  $Revision: 15 $

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

#ifndef __itkManagedProcessObject_cxx
#define __itkManagedProcessObject_cxx

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
  /** Forward reference to itkProcessObject */
  ref class itkProcessObject;

  ///<summary>
  ///EventArgs subclass holding the current progress of a process object.
  ///Provides a convient method which converts the fractional progress to an integer percentage.
  ///</summary>
  public ref class itkProgressEventArgs : itkEventArgs
  {
  private:
    float m_Progress;

  public:
    ///<summary>Default constructor.</summary>
    ///<param name="progress">The fractional progress of the process object (ie. 0.03 = 3%)</param>
    itkProgressEventArgs( float progress ) : itkEventArgs( )
    { 
      this->m_Progress = progress;
    }

    ///<summary>Get the current progress as a fraction (ie. 0.03 = 3 %).</summary>
    property float Progress 
    {
      virtual float get() { return this->m_Progress; }
    }

    ///<summary>Get the current progress as a percentage, rounded to the nearest integer value.</summary>
    property int ProgressAsPercentage
    {
      virtual int get() 
      { 
        return static_cast<int>( System::Math::Round(this->m_Progress*100.0) );
      }
    }
  };

  ///<summary>A delegate for events sent from an itkProcessObject, with a progress value between 0.0 and 1.0.</summary>
  public delegate void itkProgressHandler(itkProcessObject^ sender, itkProgressEventArgs^ e);

  ///<summary>
  ///This abstract class is a managed replacement for itk::ProcessObject.
  ///</summary>
  ///<remarks>
  ///ProcessObject is an abstract object that specifies behavior and
  ///interface of network process objects (sources, filters, mappers).
  ///Source objects are creators of visualization data; filters input,
  ///process, and output image data; and mappers transform data into
  ///another form (like transforming coordinates or writing data to a file).
  ///
  ///A major role of ProcessObject is to define the inputs and outputs of
  ///a filter. More than one input and/or output may exist for a given filter.
  ///Some classes (e.g., source objects or mapper objects) will not use inputs
  ///(the source) or outputs (mappers). In this case, the inputs or outputs is 
  ///just ignored.                                    
  ///</remarks>
  public ref class itkProcessObject abstract : itkObject
  {

  private:
    String^				m_Name;
    itkProgressHandler^	m_EventStorage_Progress;

  protected:
    ///<summary>Protected constructor.</summary>
    ///<param name="name">A string representing the name of the ProcessObject.</param>
    itkProcessObject( String^ name ) : itkObject( )
    { 
      this->m_Name = name;
    }

  public:
    ///<summary>Get/set a string describing the process object.</summary>
    property String^ Name 
    {
      virtual String^ get() { return this->m_Name; }
    }

    ///<summary>
    ///Get the size of the input array. This is merely the size of the input array,
    ///not the number of inputs that have valid DataObject's assigned.
    ///</summary>
    ///<remarks>Use NumberOfValidRequiredInputs to determine how many inputs are non-null.</remarks>
    property unsigned int NumberOfInputs 
    { 
      virtual unsigned int get()=0;
    }

    ///<summary>
    ///Get the number of valid inputs.  This is the number of non-null entries in the
    ///input array in the first NumberOfRequiredInputs slots. This method is used
    ///to determine whether the necessary required inputs have been set.
    ///</summary>
    property unsigned int NumberOfValidRequiredInputs 
    { 
      virtual unsigned int get()=0;
    }

    ///<summary>Return the length of the output array.</summary>
    property unsigned int NumberOfOutputs 
    { 
      virtual unsigned int get()=0;
    }

    ///<summary>Get/set the number of threads to create when executing.</summary>
    property unsigned int NumberOfThreads 
    { 
      virtual unsigned int get()=0;
      virtual void set(unsigned int threads)=0;
    }

    ///<summary>An event which is raised when the progress of the process is updated.</summary>
    event itkProgressHandler^ Progress
    {
    public:
      void add (itkProgressHandler^ handler) { m_EventStorage_Progress += handler; }
      void remove (itkProgressHandler^ handler) { m_EventStorage_Progress -= handler; }
    internal:
      void raise( itkProcessObject^ obj, itkProgressEventArgs^ e ) 
      { 
        if (this->m_EventStorage_Progress != nullptr)
          this->m_EventStorage_Progress(obj, e);
      }
    }    

    ///<summary>
    ///Bring this filter up-to-date.
    ///</summary>
    ///<remarks>
    ///Update() checks modified times against last execution times, and
    ///re-executes objects if necessary. A side effect of this method
    ///ss that the whole pipeline may execute in order to bring this filter
    ///up-to-date. This method updates the currently prescribed requested region.
    ///If no requested region has been set on the output, then the requested
    ///region will be set to the largest possible region. Once the requested
    ///region is set, Update() will make sure the specified requested region 
    ///is up-to-date. To have a filter always to produce its largest possible
    ///region, users should call UpdateLargestPossibleRegion() instead.
    ///</remarks>
    virtual void Update ( ) = 0;

    ///<summary>
    ///Bring the largest possible region of this filter up-to-date.
    ///</summary>
    ///<remarks>
    ///Like Update(), but sets the output requested region to the
    ///largest possible region for the output. This is the method users
    ///should call if they want the entire dataset to be processed. If
    ///a user wants to update the same output region as a previous call
    ///to Update() or a previous call to UpdateLargestPossibleRegion(), 
    ///then they should call the method Update().
    ///</remarks>
    virtual void UpdateLargestPossibleRegion ( ) = 0;

    ///<summary>
    ///Set the AbortGenerateData flag to true, and try to prematurely terminate the process. 
    ///</summary>
    ///<remarks>
    ///Process objects may handle premature termination of execution in different ways.
    ///Eg. many filters totally ignore this flag.
    ///</remarks>
    virtual void AbortGenerateData ( ) = 0;

    ///<summary>Invoke the Progress event.</summary>
    virtual void InvokeProgressEvent ( itkProgressEventArgs^ e )
    { this->Progress(this, e); }

  }; // end ref class

} // end namespace

#endif
