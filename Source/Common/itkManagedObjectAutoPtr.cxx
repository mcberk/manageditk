/*=============================================================================
  
  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedObjectAutoPtr.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date: 2008-03-09 19:29:02 +0100 (Sun, 09 Mar 2008) $
  Revision:  $Revision: 8 $

  This file was based on the following article:
      "Best Practices for Writing Efficient and Reliable Code with C++/CLI"
         by Kenny Kerr (May 2006)
       http://msdn.microsoft.com/library/en-us/dnvs05/html/CplusCLIBP.asp

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

#ifndef __itkObjectAutoPtr_cxx
#define __itkObjectAutoPtr_cxx

using namespace System::Diagnostics;

namespace itk
{

template <typename T>
ref struct itkObjectAutoPtr
{
private:
    T* m_ptr;
    bool m_disposed;

public: 
    itkObjectAutoPtr( ) : m_ptr( NULL ), m_disposed( false ) { }
    itkObjectAutoPtr( T* ptr ) : m_ptr( ptr ), m_disposed( false )
    { 
        if ( ptr != NULL )
            ptr->Register( );
    }
    itkObjectAutoPtr( itkObjectAutoPtr<T>% right ) : m_ptr( right.Release() ), m_disposed( false ) { }

    //~itkObjectAutoPtr()
    //{
    //    if (!m_disposed) Reset();
    //    m_disposed = true;
    //}

    //!itkObjectAutoPtr()
    //{
    //  // Dispose of the managed pointer if the user forgot
    //  if ( !m_Disposed )
    //    delete this;
    //}

    T* operator->( )
    {
        return m_ptr;
    }

    T* Get( )
    {
        return m_ptr;
    }

    T* Release( )
    {
        T* released = m_ptr;
        m_ptr = NULL;
        return released;
    }

    void Reset( )
    {
        Reset( NULL );
    }

    void Reset(T* ptr)
    {
        try
        {
            if ( m_ptr != NULL && ptr != m_ptr )
            {
                // Free the existing native pointer
                m_ptr->RemoveAllObservers( );
                m_ptr->SetReferenceCount( 0 );
            }

            // Set the new native pointer (sets to NULL if ptr = NULL)
            m_ptr = ptr;

            // Register the new pointer to keep it alive
            if ( m_ptr != NULL )
            {
                m_ptr->Register( );
            }
        }
        catch (...)
        {
            // HACK: Consume the exception, even though it is bad practice.
            // NOTE: This method tends to throw System.AccessViolationExceptions,
            //       probably because the memory has been previously freed.
        }
    }
};

} // end namespace itk

#endif
