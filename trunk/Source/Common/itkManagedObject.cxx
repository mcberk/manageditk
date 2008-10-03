/*=============================================================================

NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

Project:   ManagedITK
Program:   Insight Segmentation & Registration Toolkit
Module:    itkManagedObject.cxx
Language:  C++/CLI
Author:    Dan Mueller
Date:      $Date: 2008-06-21 09:20:09 +0200 (Sat, 21 Jun 2008) $
Revision:  $Revision: 18 $

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

#ifndef __itkManagedObject_cxx
#define __itkManagedObject_cxx

// Include some headers for string ops
#include <iostream>  
#include <map>
#include <string>
using std::string;

// Include some useful ManagedITK files
#include "itkManagedINativePointer.cxx"

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

  /** Forward reference to itkObject */
  ref class itkObject;

  ///<summary>
  ///EventArgs subclass for managed ITK objects.
  ///</summary>
  public ref class itkEventArgs : System::EventArgs
  {
  public:
    ///<summary>Default constructor.</summary>
    itkEventArgs( ) : System::EventArgs( )
    { 

    }
  };

  ///<summary>A delegate for events sent from an itkObject.</summary>
  public delegate void itkEventHandler(itkObject^ sender, itkEventArgs^ e);

  ///<summary>
  ///This class is a managed replacement for itk::Object.
  ///</summary>
  ///<remarks>
  ///Object is the second-highest level base class for most itk objects. 
  ///It extends the base object functionality of LightObject by          
  ///implementing callbacks (via object/observer), debug flags/methods,  
  ///and modification time tracking. Most ITK classes should be a subclass
  ///of Object due to the need to keep track of modified time.
  ///</remarks>
  public ref class itkObject abstract : INativePointer
  {

  private:	
    String^ m_Name;
    Dictionary<String^, Object^>^ m_Metadata;
    itkEventHandler^	m_EventStorage_Started;
    itkEventHandler^	m_EventStorage_Ended;
    itkEventHandler^	m_EventStorage_Aborted;
    itkEventHandler^	m_EventStorage_Iteration;
    itkEventHandler^	m_EventStorage_Modified;

  protected:
    bool m_IsDisposed;
    bool m_DisposeNativeObjectOnFinalize;
    String^ m_MangledTypeString;

    ///<summary>Protected constructor.</summary>
    itkObject( )
    {
      this->m_IsDisposed = false;
      this->m_DisposeNativeObjectOnFinalize = true;
      this->m_MangledTypeString = String::Empty;
    }

  public:
    ///<summary>Gets if the object has been disposed.</summary>
    property bool IsDisposed
    {
      virtual bool get() { return this->m_IsDisposed; }
    }

    ///<summary>
    ///Gets/sets if the underlying native object should be disposed when the managed object is finalized.
    ///The default is true.
    ///</summary>
    property bool DisposeNativeObjectOnFinalize
    {
      virtual bool get() { return this->m_DisposeNativeObjectOnFinalize; }
      virtual void set( bool value ) { this->m_DisposeNativeObjectOnFinalize = value; }
    }

    ///<summary>Get a [name, value] list of 'metadata'.</summary>
    ///<remarks>
    ///This property was added to ManagedITK to easily create temporary
    ///(ie. non-persisent, not save to file) 'metadata'.
    ///</remarks>
    property Dictionary<String^, Object^>^ Metadata
    {
      virtual Dictionary<String^, Object^>^ get() 
      { 
        // Create for first access
        if (this->m_Metadata == nullptr)
          this->m_Metadata = gcnew Dictionary<String^, Object^>();

        // Return
        return this->m_Metadata;	 
      }
    }

    ///<summary>Get the last modified time.</summary>
    property unsigned long MTime { virtual unsigned long get()=0; }

    ///<summary>Get a string representing the type instance of this INativePointer.</summary>
    ///<example>"IUC2", "IF3", "IUC2IUC2".</example>
    property String^ MangledTypeString
    { 
      virtual String^ get() { return this->m_MangledTypeString; }
    }

    ///<summary>
    ///Get/set the pointer to the native ITK object associated with
    ///this wrapper instance.
    ///</summary>
    ///<returns>The pointer to the native ITK object.</returns>
    property IntPtr NativePointer{ virtual IntPtr get()=0; virtual void set ( IntPtr value )=0; }

    ///<summary>
    ///Remove all observers watching this object.
    ///</summary>
    ///<remarks>
    ///By default, observers are created for all events. Calling this
    ///method removes all native observers, and therefore prevents
    ///the firing of managed events. Call AddAnyEventObserver() to
    ///reset the default observers which enable the managed events.
    ///</remarks>
    virtual void RemoveAllObservers ( ) = 0;

    ///<summary>
    ///Adds a native observer watching for any event.
    ///</summary>
    ///<remarks>
    ///By default, observers are created for all events. Calling this
    ///method adds a single native observer for any event. This
    ///observer invokes the managed events. Therefore, calling this
    ///method more than once, or calling it without first calling
    ///RemoveAllObservers() may cause the managed events to be
    ///invoked more than once.
    ///</remarks>
    virtual void AddAnyEventObserver ( ) = 0;

    ///<summary>An event which is raised when the object is modified.</summary>
    event itkEventHandler^ Modified
    {
    public:
      void add (itkEventHandler^ handler) { m_EventStorage_Modified += handler; }
      void remove (itkEventHandler^ handler) { m_EventStorage_Modified -= handler; }
    internal:
      void raise( itkObject^ obj, itkEventArgs^ e ) 
      { 
        if (this->m_EventStorage_Modified != nullptr)
          this->m_EventStorage_Modified(obj, e);
      }
    }

    ///<summary>An event which is raised when the process is started.</summary>
    event itkEventHandler^ Started
    {
    public:
      void add (itkEventHandler^ handler) { m_EventStorage_Started += handler; }
      void remove (itkEventHandler^ handler) { m_EventStorage_Started -= handler; }
    internal:
      void raise( itkObject^ obj, itkEventArgs^ e ) 
      { 
        if (this->m_EventStorage_Started != nullptr)
          this->m_EventStorage_Started(obj, e);
      }
    }

    ///<summary>An event which is raised when the process has finished.</summary>
    event itkEventHandler^ Ended
    {
    public:
      void add (itkEventHandler^ handler) { m_EventStorage_Ended += handler; }
      void remove (itkEventHandler^ handler) { m_EventStorage_Ended -= handler; }
    internal:
      void raise( itkObject^ obj, itkEventArgs^ e ) 
      { 
        if (this->m_EventStorage_Ended != nullptr)
          this->m_EventStorage_Ended(obj, e);
      }
    }

    ///<summary>An event which is raised if the process is aborted.</summary>
    event itkEventHandler^ Aborted
    {
    public:
      void add (itkEventHandler^ handler) { m_EventStorage_Aborted += handler; }
      void remove (itkEventHandler^ handler) { m_EventStorage_Aborted -= handler; }
    internal:
      void raise( itkObject^ obj, itkEventArgs^ e ) 
      { 
        if (this->m_EventStorage_Aborted != nullptr)
          this->m_EventStorage_Aborted(obj, e);
      }
    }    

    ///<summary>An event which is raised when the process iteration is updated.</summary>
    event itkEventHandler^ Iteration
    {
    public:
      void add (itkEventHandler^ handler) { m_EventStorage_Iteration += handler; }
      void remove (itkEventHandler^ handler) { m_EventStorage_Iteration -= handler; }
    internal:
      void raise( itkObject^ obj, itkEventArgs^ e ) 
      { 
        if (this->m_EventStorage_Iteration != nullptr)
          this->m_EventStorage_Iteration(obj, e);
      }
    }

    ///<summary>Invoke the Started event.</summary>
    virtual void InvokeStartedEvent ( itkEventArgs^ e )
    { this->Started(this, e); }

    ///<summary>Invoke the Ended event.</summary>
    virtual void InvokeEndedEvent ( itkEventArgs^ e )
    { this->Ended(this, e); }

    ///<summary>Invoke the Aborted event.</summary>
    virtual void InvokeAbortedEvent ( itkEventArgs^ e )
    { this->Aborted(this, e); }

    ///<summary>Invoke the Iteration event.</summary>
    virtual void InvokeIterationEvent (  itkEventArgs^ e )
    { this->Iteration(this, e); }

    ///<summary>Invoke the Modified event.</summary>
    virtual void InvokeModifiedEvent ( itkEventArgs^ e )
    { this->Modified(this, e); }

  internal:
    ///<summary>Marshal a managed string to the unmanaged heap.</summary>
    static void MarshalString ( System::String^ s, std::string& os )
    {
      const char* chars = 
        (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(s)).ToPointer();
      os = chars;
      System::Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr((void*)chars));
    }

  }; // end ref class

} // end namespace itk

#endif