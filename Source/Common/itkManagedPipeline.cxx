/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedPipeline.cxx
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

#ifndef __itkManagedPipeline_cxx
#define __itkManagedPipeline_cxx

// Include some useful ManagedITK files
#include "itkManagedDataObject.cxx"
#include "itkManagedProcessObject.cxx"
#include "itkManagedImageSource.cxx"
#include "itkManagedImageToImageFilter.cxx"

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::ComponentModel;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

namespace itk
{

///<summary>
///A class for grouping filters into a simple itkPipeline object.
///Add filters using the AddFilter() or SetFilter() methods, add inputs using
///the SetInput() method, get outputs using the GetOutput() method, 
///and update the Pipeline using the Update() method. Filters must be added BEFORE
///the Input/Output/Update methods can be called.
///</summary>
///<remarks>
///The pipeline can work for internal filters which expect multiple inputs by
///explicitly setting the inputs instead of or after calling 
///ConnectInternalFiltersInputsAndOutputs().
///</remarks>
public ref class itkPipeline
{

private:
	bool m_IsDisposed;
	List<itkImageToImageFilter^>^ m_Filters;

	///<summary>Initialise the pipeline.</summary>
	void Initialise ( )
	{
		this->m_IsDisposed = false;
		this->m_Filters = gcnew List<itkImageToImageFilter^>();
	}

public:
	///<summary>Default constructor which creates an empty list of filters.</summary>
	itkPipeline ( )
	{
		this->Initialise();
	}
	
	///<summary>Constructor taking the list of filters.</summary>
	///<param name="filters">The list of filter instance objects in this pipline.</param>
	itkPipeline ( ... array<itkImageToImageFilter^>^ filters )
	{
		this->Initialise();

		for each ( itkImageToImageFilter^ filter in filters)
			this->m_Filters->Add( filter );
	}

    ///<summary>Dispose of the managed object.</summary>
	~itkPipeline ( )
    {
		if (!this->m_IsDisposed)
		{
			// Mark as disposed
			this->m_IsDisposed = true;
			
			// Dispose of each filter
			for each ( itkImageToImageFilter^ filter in this->m_Filters )
			{
				if (filter != nullptr && !filter->IsDisposed) delete filter;
			}

			// Clean up the list of filters
			this->m_Filters->Clear();
			this->m_Filters = nullptr;
        }
    }
	
	///<summary>Get the list of filters comprising this pipeline.</summary>
	///<remarks>Filters can be added to this pipeline using Filters.Add() or AddFilters().</remarks>
	property List<itkImageToImageFilter^>^ Filters
	{
		virtual List<itkImageToImageFilter^>^ get() { return this->m_Filters; }
	}

	///<summary>Add a filter to the end of the pipeline.</summary>
	///<param name="filter">The filter to add to the end of the pipeline.</param>
	///<remarks>Filters can be added to this pipeline using Filters.Add() or AddFilters().</remarks>
	virtual void AddFilter( itkImageToImageFilter^ filter )
	{
		this->m_Filters->Add( filter );
	}

	///<summary>
	///Set the filter at the specified position in the pipeline.
	///The index must be less than Filters.Length, otherwise an IndexOutOfRangeException
	///will be thrown.
	///</summary>
	///<param name="index">The index of the filter to set.</param>
	///<param name="filter">The filter object to set.</param>
	virtual void SetFilter( unsigned int index, itkImageToImageFilter^ filter )
	{
		this->m_Filters[index] = filter;
	}

    ///<summary>Set the first input of the pipeline object.</summary>
    ///<param name="input">The input as an itkDataObject.</param>
	///<remarks>The first filter must be added to the pipeline before calling this method.</remarks>
	virtual void SetInput( itkDataObject^ input )
	{
		this->m_Filters[0]->SetInput( input );
	}

    ///<summary>Set the specified input of the pipeline object.</summary>
    ///<param name="input">The input as an itkDataObject.</param>
	///<remarks>The first filter must be added to the pipeline before calling this method.</remarks>
	virtual void SetInput(unsigned int index, itkDataObject^ input)
	{
		this->m_Filters[0]->SetInput( index, input );
	}

	///<summary>
	///Connects the output of each internal filter to the input of the next filter.
	///</summary>
	///<remarks>
	///This method has no effect if the number of internal filters is one.
	///</remarks>
	virtual void ConnectInternalFiltersInputsAndOutputs( )
	{
		// Connect the output to the input of the next filter
		for (int i=1; i < this->m_Filters->Count; i++)
			this->m_Filters[i]->SetInput( this->m_Filters[i-1]->GetOutput() );
	}

	///<summary>
	///Call Update() on the last filter in the pipeline.
	///</summary>
	///<remarks>
	///The user must have already connected the internal filter inputs and outputs by
	///calling or ConnectInternalFiltersInputsAndOutputs or by explicitly setting them.
	///</remarks>
	virtual void Update ( )
	{		
		// Update the last filter
		this->m_Filters[this->m_Filters->Count - 1]->Update();
	}

    ///<summary>Get the first output of the pipeline object.</summary>
    ///<param name="output">The itkDataObject to make as the output.</param>
	///<remarks>All filters must be added to the pipeline before calling this method.</remarks>
	virtual void GetOutput( itkDataObject^ output )
	{
		this->m_Filters[this->m_Filters->Count - 1]->GetOutput( output );
	}

    ///<summary>Get the specified output of the pipeline object.</summary>
    ///<param name="output">The itkDataObject to make as the output.</param>
	///<remarks>All filters must be added to the pipeline before calling this method.</remarks>
	virtual void GetOutput(unsigned int index, itkDataObject^ output)
	{
		this->m_Filters[this->m_Filters->Count - 1]->GetOutput( index, output );
	}

    ///<summary>
	///Converts the itkPipeline to a string representation.
	///Eg. "itkTest1ImageFilter -> itkTest2ImageFilter".
	///</summary>
    ///<returns>A string represetnation of the itkPipeline.</returns>
	virtual String^ ToString() override
    {
		String^ result = String::Empty;		
		for each (itkProcessObject^% filter in this->m_Filters)
			result += filter->Name + " -> ";	
		result->TrimEnd( ' ', '-', '>' );
		return result;
    }

}; // end ref class

} // end namespace itk

#endif