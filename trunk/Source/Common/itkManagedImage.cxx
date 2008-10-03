/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImage.cxx
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
#pragma warning( disable : 4996 ) // Disable warnings about deprecated methods

#ifndef __itkManagedImage_cxx
#define __itkManagedImage_cxx

// Include some useful ManagedITK files
#include "itkManagedImageBase.cxx"
#include "itkManagedInvalidWrappedTypeException.cxx"

// Use some managed namespaces
#using <mscorlib.dll>
#using <System.dll>
using namespace System;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Diagnostics;

namespace itk
{

///<summary>
///This class is a managed wrapper for itk::Image. A specific image type
///(eg. unsigned char, float, etc.) can be instantiated using the 
///New(pixeltype, dim) method.
///</summary>
///<remarks>
///Images are defined by a pixel type (modeling the dependent variables), 
///and a dimension (number of independent variables). 
///An image is modeled as an array, defined by a start index and a size.
///The underlying array can be accessed via the Buffer property.
///
///There are three sets of meta-data describing an image. These are "Region"
///objects that define a portion of an image via a starting index for the image
///array and a size. The ivar LargestPossibleRegion defines the size and
///starting index of the image dataset. The entire image dataset, however,
///need not be resident in memory. The region of the image that is resident in
///memory is defined by the "BufferedRegion". The Buffer is a contiguous block
///of memory.  The third set of meta-data defines a region of interest, called
///the "RequestedRegion". The RequestedRegion is used by the pipeline
///execution model to define what a filter is requested to produce.
///</remarks>
public ref class itkImage : itkImageBase
{

private:
	itkImageBase^ m_Instance;

protected:
	///<summary>Protected constructor.</summary>
	itkImage ( ) : itkImageBase( )
    { }

public:
    ///<summary>Dispose of the managed object.</summary>
	~itkImage ( )
    {
		if (!this->IsDisposed)
		{
            this->m_IsDisposed = true;
            delete m_Instance;
        }
    }

    ///<summary>Finalize the managed object.</summary>
    !itkImage ( )
    {
        if (!this->IsDisposed && this->DisposeNativeObjectOnFinalize)
            delete this;
    }

    ///<summary>Get/set a string describing the data object (typically an abosolute file name).</summary>
	property String^ Name
    {
        virtual String^ get() override { return this->m_Instance->Name; }
		virtual void set( String^ name ) override { this->m_Instance->Name = name; }
    }

	///<summary>Get the size of the image (from the LargestPossibleRegion).</summary>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	property itkSize^ Size 
	{ 
		virtual itkSize^ get() override { return this->m_Instance->Size; }
	}

	///<summary>Get/set the spacing between pixels of the image.</summary>
	property itkSpacing^ Spacing 
	{ 
		virtual itkSpacing^ get() override { return this->m_Instance->Spacing; }
		virtual void set( itkSpacing^ spacing ) override { this->m_Instance->Spacing = spacing; }
	}

	///<summary>Get/set the origin of the image in physical space.</summary>
	property itkPoint^ Origin 
	{ 
		virtual itkPoint^ get() override { return this->m_Instance->Origin; } 
		virtual void set( itkPoint^ origin ) override { this->m_Instance->Origin = origin; }
	}

	///<summary>
	///Get/set the region object that defines the size and starting index
    ///for the largest possible region this image could represent.
	///</summary>
	property itkImageRegion^ LargestPossibleRegion 
	{ 
		virtual itkImageRegion^ get() override { return this->m_Instance->LargestPossibleRegion; }
		virtual void set ( itkImageRegion^ region ) override { this->m_Instance->LargestPossibleRegion = region; }
	}

	///<summary>
	///Get/set the region object that defines the size and starting index
    ///for the region of the image requested (i.e., the region of the
    ///image to be operated on by a filter). Setting the RequestedRegion
    ///does not cause the object to be modified.
	///</summary>
	property itkImageRegion^ RequestedRegion 
	{ 
		virtual itkImageRegion^ get() override { return this->m_Instance->RequestedRegion; } 
		virtual void set ( itkImageRegion^ region ) override { this->m_Instance->RequestedRegion = region; }
	}

	///<summary>
	///Get/set the region object that defines the size and starting index
    ///of the region of the image currently loaded in memory.
	///</summary>
	property itkImageRegion^ BufferedRegion 
	{ 
		virtual itkImageRegion^ get() override { return this->m_Instance->BufferedRegion; } 
		virtual void set ( itkImageRegion^ region ) override { this->m_Instance->BufferedRegion = region; }
	}

	///<summary>Get the pointer to the underlying image data array.</summary>
	property IntPtr Buffer 
	{
		virtual IntPtr get() override { return this->m_Instance->Buffer; } 
	}
	
	///<summary>Get the direction cosines of the image. The direction cosines are vectors that point from one pixel to the next.</summary>
	property itkMatrix^ Direction 
    { 
        virtual itkMatrix^ get() override { return this->m_Instance->Direction; }
        virtual void set ( itkMatrix^ direction ) override { this->m_Instance->Direction = direction; }
    }

	///<summary>
	///Gets/sets if the underlying native object should be disposed when the managed object is finalized.
	///The default is true.
	///</summary>
	property bool DisposeNativeObjectOnFinalize
	{
        virtual bool get() override
        {
            if ( this->m_Instance == nullptr ) return true;
            else return this->m_Instance->DisposeNativeObjectOnFinalize;
        }
        virtual void set( bool value ) override
        { 
            if ( this->m_Instance != nullptr )
                this->m_Instance->DisposeNativeObjectOnFinalize = value;			
        }
	}

	///<summary>Get the last modified time.</summary>
	property unsigned long MTime 
	{ 
		virtual unsigned long get() override { return this->m_Instance->MTime; } 
	}
    
	///<summary>Get a string representing the type instance of this INativePointer.</summary>
	///<example>"IUC2", "IF3", "IVF22".</example>
	property String^ MangledTypeString 
	{ 
		virtual String^ get() override
        {
			INativePointer^ instanceSmartPtr = safe_cast<INativePointer^>(m_Instance);
			return instanceSmartPtr->MangledTypeString;
        }
	}
	
	///<summary>
	///Get/set the pointer to the native ITK object associated with
	///this wrapper instance.
	///</summary>
	///<returns>The pointer to the native ITK object.</returns>
	property virtual IntPtr NativePointer 
	{ 
		virtual IntPtr get() override
        {
			INativePointer^ instanceSmartPtr = safe_cast<INativePointer^>(m_Instance);
			return instanceSmartPtr->NativePointer;
        }        
        virtual void set ( IntPtr value) override
        {
			INativePointer^ instanceSmartPtr = safe_cast<INativePointer^>(m_Instance);
			instanceSmartPtr->NativePointer = value;
        }
	}

	///<summary>Create an instance of an underlying native itk::Image.</summary>
	///<param name="pixelType">The pixel type the underlying native itk::Image is templated over.</param>
    ///<param name="dim">The number of dimensions the underlying native itk::Image is templated over.</param>
	static itkImage^ New ( itkPixelType^ pixelType, unsigned int dim )
	{
		if (pixelType == nullptr)
			throw gcnew itkInvalidWrappedTypeException("The given pixel type is null. A valid pixel type must be specified to create an instance of a wrapped itk::Image.");
		
		itkImage^ newImage = gcnew itkImage();
		newImage->m_PixelType = pixelType;
		newImage->m_Dimension = dim;
		newImage->CreateInstance();
		return newImage;
	}

	///<summary>Create an instance of the same underlying native itk::Image type as the given image.</summary>
	///<param name="image">The type of the underlying native itk::Image to create.</param>
	static itkImage^ New ( itkImageBase^ image )
	{
		if (image == nullptr)
			throw gcnew itkInvalidWrappedTypeException("The given image is null. A valid image must be specified to create an instance of a wrapped itk::Image.");
		
		itkImage^ newImage = gcnew itkImage();
        newImage->m_PixelType = image->PixelType;
        newImage->m_Dimension = image->Dimension;
		newImage->CreateInstance();
		return newImage;
	}

	///<summary>Create an instance of an underlying native itk::Image.</summary>
	///<param name="mangledPixelType">A string representing the pixel type the underlying native itk::Image is templated over.</param>
    ///<param name="dim">The number of dimensions the underlying native itk::Image is templated over.</param>
	static itkImage^ New ( String^ mangledPixelType, unsigned int dim )
	{
		if (mangledPixelType == nullptr || mangledPixelType->Length == 0)
			throw gcnew itkInvalidWrappedTypeException("The given pixel type string is empty. A non-empty, valid pixel type string must be specified to create an instance of a wrapped itk::Image.");
		
		itkImage^ newImage = gcnew itkImage();
		newImage->m_PixelType = itkPixelType::CreateFromMangledType(mangledPixelType);
        newImage->m_Dimension = dim;
		newImage->CreateInstance();
		return newImage;
	}

	///<summary>Create an instance of an underlying native itk::Image.</summary>
	///<param name="mangledType">A string representing the pixel type and dimension the underlying native itk::Image is templated over. Eg. "UC2", "F3", etc.</param>
	static itkImage^ New ( String^ mangledType )
	{
		if (mangledType == nullptr || mangledType->Length == 0)
			throw gcnew itkInvalidWrappedTypeException("The given image type string is empty. A non-empty, valid image type string must be specified to create an instance of a wrapped itk::Image.");

		itkImage^ newImage = gcnew itkImage();
		newImage->m_PixelType = itkPixelType::CreateFromMangledType(mangledType);
		newImage->m_Dimension = UInt32::Parse(mangledType->Substring(mangledType->Length-1, 1));
		newImage->CreateInstance();
		return newImage;
	}
	
    ///<summary>Return itk::LightObject::Print( ostream ) as a string.</summary>
	virtual String^ ToString ( ) override
	{
        return m_Instance->ToString( );
	}

    ///<summary>
    ///Remove all observers watching this object.
    ///</summary>
    ///<remarks>
	///By default, observers are created for all events. Calling this
	///method removes all native observers, and therefore prevents
	///the firing of managed events. Call AddAnyEventObserver() to
	///reset the default observers which enable the managed events.
	///</remarks>
	virtual void RemoveAllObservers ( ) override
	{
		this->m_Instance->RemoveAllObservers();
	}

    ///<summary>
    ///Adds a native observer watching for any event.
    ///</summary>
    ///<remarks>
	///By default, observers are created for all events. Calling this
	///method adds a single native observer for any event. This
	///observer invokes the managed events. Therefore, calling this
	///method more than once, or calling it without first calling
	///RemoveAllObservers(), may cause the managed events to be
	///invoked more than once.
	///</remarks>
	virtual void AddAnyEventObserver ( ) override
	{
        this->m_Instance->AddAnyEventObserver( );
        this->PassEventsFromTypeToWrapper( );
	}

    ///<summary>Read the image from the given file.</summary>
    ///<param name="filename">The relative or absolute file path and name.</param>
	virtual void Read ( System::String^ filename ) override
	{
        this->m_Instance->Read(filename);
	}

    ///<summary>Read an image series from the given filenames.</summary>
    ///<param name="filenames">An array of absolute file paths.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadSeries ( array<System::String^>^ filenames ) override
	{
		this->m_Instance->ReadSeries(filenames);
	}

    ///<summary>Read an image series from the files matching the given pattern.</summary>
    ///<param name="path">An absolute path to search for the files comprising the series.</param>
    ///<param name="pattern">A pattern with wildcard character '*'.</param>
	///<example>path="C:/temp/", pattern="test_*.png".</example>
	///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadSeries ( System::String^ path, System::String^ pattern ) override
	{
		this->m_Instance->ReadSeries(path, pattern);
	}

    ///<summary>
    ///Read an image from the given DICOM directory using GDCM.
    ///This method uses the first found series identifier.
    ///</summary>
    ///<param name="directory">The directory containing the DICOM series.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadDicomDirectory( System::String^ directory ) override
	{
		this->m_Instance->ReadDicomDirectory(directory);
	}

    ///<summary>Read an image from the given DICOM directory using GDCM.</summary>
    ///<param name="directory">The directory containing the DICOM series.</param>
    ///<param name="seriesid">The identifier of the series to read.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadDicomDirectory( System::String^ directory, System::String^ seriesid ) override
	{
		this->m_Instance->ReadDicomDirectory(directory, seriesid);
	}

    ///<summary>Read an image from the given DICOM directory using GDCM.</summary>
    ///<param name="directory">The directory containing the DICOM series.</param>
    ///<param name="seriesid">The identifier of the series to read.</param>
    ///<param name="restrictions">Specifies additional DICOM information to distinguish unique volumes within the directory. Eg. "0008|0021" distinguishes series based on date.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadDicomDirectory( System::String^ directory, 
								     System::String^ seriesid,
									 ... array<System::String^>^ restrictions) override
	{
		this->m_Instance->ReadDicomDirectory(directory, seriesid, restrictions);
	}

    ///<summary>Write the image to the given file.</summary>
    ///<param name="filename">The relative or absolute file path and name.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void Write ( System::String^ filename ) override
	{
        this->m_Instance->Write(filename);
	}
	
    ///<summary>Write an image series to the files matching the given format.</summary>
    ///<param name="filenameFormat">The absolute path and filename format for the images. Eg. C:/temp/test_{0}.png.</param>
    ///<param name="seriesFormat">A format string for the series numbers. Eg. "000".</param>
	///<example>filenameFormat="C:/temp/test_{0}.png" and seriesFormat="000".</example>
	///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void WriteSeries ( System::String^ filenameFormat, System::String^ seriesFormat ) override
	{
        this->m_Instance->WriteSeries(filenameFormat, seriesFormat);
    }

    ///<summary>
    ///Allocates the memory for an empty image.
    ///This is the method to use to create an image from scratch (ie. not from IO).
	///The regions MUST have been set: call SetRegions() before calling this method.
	///The buffer is NOT initialised: call FillBuffer() after calling this method.
    ///</summary>
    ///<remarks>This method finalises the creation of the underlying native itk::Image.</remarks>
	virtual void Allocate (  ) override
	{
		this->m_Instance->Allocate();
	}

	///<summary>
	///Convenience method to set the LargestPossibleRegion, BufferedRegion and RequestedRegion.
    ///</summary>
    ///<param name="regions">The image region specifying the largest, requested, and buffered size.</param>
    ///<remarks>
	///This method does not allocate the image, use Allocate for that purpose.
	///</remarks>
	virtual void SetRegions ( itkImageRegion^ regions ) override
	{
		this->m_Instance->SetRegions(regions);
	}

    ///<summary>
    ///Fills the image data with the given value.
	///The image regions must be set before calling this method and
    ///the image must have been allocated.
    ///</summary>
    ///<param name="value">The pixel value to fill the image.</param>
	virtual void FillBuffer ( itkPixel^ value ) override
	{
        this->m_Instance->FillBuffer(value);
	}
    
    ///<summary>Returns the pixel value at the given discrete location.</summary>
    ///<param name="index">The discrete location in image space.</param>
    ///<returns>The pixel value at the given discrete location.</returns>
	virtual itkPixel^ GetPixel ( itkIndex^ index ) override
	{
        return m_Instance->GetPixel(index);
	}

    ///<summary>Set the pixel value at the given discrete location.</summary>
    ///<param name="index">The discrete location in image space.</param>
    ///<param name="value">The new value to set.</param>
	virtual void SetPixel ( itkIndex^ index, itkPixel^ value ) override
	{
        this->m_Instance->SetPixel(index, value);
	}
    
    ///<summary>Separate this image from the pipeline.</summary>
    ///<remarks>
	///This method disconnects the image from the upstream pipeline.
	///Hence an Update() from downstream will not propagate back past this image.
	///To completely isolate this image from the pipeline, the application must
	///remove this image from any filters which it is connected as the input.
	///</remarks>
    virtual void DisconnectPipeline ( ) override
	{
        this->m_Instance->DisconnectPipeline();
	}

    ///<summary>Convert a physical point to a continuous index.</summary>
    ///<param name="point">The geometric location in physical space.</param>
    ///<param name="cindex">The resultant continuous location in image space.</param>
    ///<returns>true if the resulting index is within the image, false otherwise.</returns>
	virtual bool TransformPhysicalPointToContinuousIndex( itkPoint^ point, [System::Runtime::InteropServices::Out] itkContinuousIndex^% cindex ) override
	{
        return this->m_Instance->TransformPhysicalPointToContinuousIndex(point, cindex);
	}
    
    ///<summary>Convert a physical point to a discrete index.</summary>
    ///<param name="point">The geometric location in physical space.</param>
    ///<param name="index">The resultant discrete location in image space.</param>
    ///<returns>true if the resulting index is within the image, false otherwise.</returns>
	virtual bool TransformPhysicalPointToIndex( itkPoint^ point, [System::Runtime::InteropServices::Out] itkIndex^% index ) override
	{
        return this->m_Instance->TransformPhysicalPointToIndex(point, index);
	}

	///<summary>Convert a continuous index to a physical point.</summary>
    ///<param name="cindex">The continuous location in image space.</param>
	///<param name="point">The resultant geometric location in physical space.</param>
	virtual void TransformContinuousIndexToPhysicalPoint( itkContinuousIndex^ cindex, [System::Runtime::InteropServices::Out] itkPoint^% point ) override
	{
        this->m_Instance->TransformContinuousIndexToPhysicalPoint(cindex, point);
	}

	///<summary>Convert a discrete index to a physical point.</summary>
    ///<param name="index">The discrete location in image space.</param>
	///<param name="point">The resultant geometric location in physical space.</param>
	virtual void TransformIndexToPhysicalPoint( itkIndex^ index, [System::Runtime::InteropServices::Out] itkPoint^% point ) override
	{
        this->m_Instance->TransformIndexToPhysicalPoint(index, point);
	}

private:	
	///<summary>Creates the correct type instance of the underlying native itk::Image.</summary>
	void CreateInstance ( )
    {
		this->m_IsDisposed = false;
        String^ nameInstanceType = "itk.itkImage_" + this->PixelType->MangledTypeString + this->Dimension;
		
		try
		{
			System::Type^ typeInstance = System::Reflection::Assembly::GetExecutingAssembly()->GetType(nameInstanceType);
			if (typeInstance == nullptr)
			    throw gcnew NullReferenceException("The type '" + nameInstanceType + "' could not be found in " + System::Reflection::Assembly::GetExecutingAssembly()->GetName() );
			System::Object^ objInstance = typeInstance->InvokeMember("New", System::Reflection::BindingFlags::InvokeMethod, System::Type::DefaultBinder, nullptr, nullptr);
			if (objInstance == nullptr)
			    throw gcnew NullReferenceException("Could not invoke the New() method for '" + nameInstanceType + "'.");
            this->m_Instance = safe_cast<itkImageBase^>(objInstance);
			this->PassEventsFromTypeToWrapper( );
		}
		catch (Exception^ ex)
		{
			throw gcnew itkInvalidWrappedTypeException("Could not create an instance of '" + nameInstanceType + "'. The given type may not be supported or may be invalid.", ex);
		}
    }
    
    ///<summary>Pass managed events from the type instance to this wrapper instance.</summary>
	void PassEventsFromTypeToWrapper()
	{
        this->m_Instance->Started += gcnew itkEventHandler(this, &itkImage::Instance_StartedHandler);
		this->m_Instance->Ended += gcnew itkEventHandler(this, &itkImage::Instance_EndedHandler);
		this->m_Instance->Aborted += gcnew itkEventHandler(this, &itkImage::Instance_AbortedHandler);
		this->m_Instance->Iteration += gcnew itkEventHandler(this, &itkImage::Instance_IterationHandler);
		this->m_Instance->Modified += gcnew itkEventHandler(this, &itkImage::Instance_ModifiedHandler);
	}

	///<summary>Handle the Started event.</summary>
	void Instance_StartedHandler(itkObject^ sender, itkEventArgs^ e)
	{
		this->InvokeStartedEvent(e);
	}

    ///<summary>Handle the Ended event.</summary>
	void Instance_EndedHandler(itkObject^ sender, itkEventArgs^ e)
	{
		this->InvokeEndedEvent(e);
	}
	
    ///<summary>Handle the Aborted event.</summary>
	void Instance_AbortedHandler(itkObject^ sender, itkEventArgs^ e)
	{
		this->InvokeAbortedEvent(e);
	}

    ///<summary>Handle the Iteration event.</summary>
	void Instance_IterationHandler(itkObject^ sender, itkEventArgs^ e)
	{
		this->InvokeIterationEvent(e);
	}

    ///<summary>Handle the Modified event.</summary>
	void Instance_ModifiedHandler(itkObject^ sender, itkEventArgs^ e)
	{
		this->InvokeModifiedEvent(e);
	}

}; // end ref class

} // end namespace itk

#endif