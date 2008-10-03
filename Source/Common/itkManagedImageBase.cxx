/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedImageBase.cxx
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

#ifndef __itkManagedImageBase_cxx
#define __itkManagedImageBase_cxx

// Include some useful ITK headers
#pragma unmanaged
#include "itkImageIOFactory.h"

// Include some useful ManagedITK files
#pragma managed
#include "itkManagedDataObject.cxx"
#include "itkManagedDataObjectWithReadWrite.cxx"
#include "itkManagedIndex.cxx"
#include "itkManagedContinuousIndex.cxx"
#include "itkManagedPoint.cxx"
#include "itkManagedOffset.cxx"
#include "itkManagedPixelType.cxx"
#include "itkManagedPixel.cxx"
#include "itkManagedSize.cxx"
#include "itkManagedSpacing.cxx"
#include "itkManagedMatrix.cxx"
#include "itkManagedImageRegion.cxx"
#include "itkManagedExceptionObject.cxx"
#include "itkManagedImageInformation.cxx"

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
///This class is a managed wrapper for itk::ImageBase.
///</summary>
public ref class itkImageBase abstract : itkDataObjectWithReadWrite
{

protected:
	itkPixelType^ m_PixelType;
	unsigned int m_Dimension;

    ///<summary>Protected constructor.</summary>
	itkImageBase ( ) : itkDataObjectWithReadWrite( )
    { }

public:
    ///<summary>Dispose of the managed object.</summary>
	~itkImageBase ( )
    { }

    ///<summary>Get the type of pixel this image contains.</summary>
    ///<remarks>
	///In native itk, images are templated over the pixel type: TPixel (eg. unsigned
	///char, float, etc). In ManagedITK, to allow for the specification of image types
	///at runtime, the itkPixelType and itkPixel classes were introduced.
	///</remarks>
	property itkPixelType^ PixelType 
	{ 
		itkPixelType^ get( ) { return this->m_PixelType; } 
	}

	///<summary>Get the number of dimensions this image contains.</summary>
    ///<remarks>
	///In native itk, images are templated over the number of dimensions: VDimension.
	///In ManagedITK, to allow for the specification of image types at runtime,
	///this property was introduced.
	///</remarks>
	property unsigned int Dimension
	{ 
		unsigned int get( ) { return this->m_Dimension; } 
	}

	///<summary>Get the size of the image (from the LargestPossibleRegion).</summary>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	property itkSize^ Size { virtual itkSize^ get()=0; }
	
	///<summary>
	///Get the physical size of the image of the image (element-wise multiplication
	///of Size and Spacing).
	///</summary>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	property itkArray<double>^ PhysicalSize 
	{ 
		virtual itkArray<double>^ get()
		{
			itkArray<double>^ result = gcnew itkArray<double>(this->Dimension);
			for (unsigned int i=0; i<this->Dimension; i++)
				result[i] = this->Size[i] * this->Spacing[i];
			return result;
		}
	}

	///<summary>Get/set the spacing between pixels of the image.</summary>
	property itkSpacing^ Spacing { virtual itkSpacing^ get()=0; virtual void set( itkSpacing^ spacing )=0; }

	///<summary>Get/set the origin of the image in physical space.</summary>
	property itkPoint^ Origin { virtual itkPoint^ get()=0; virtual void set( itkPoint^ origin )=0; }

	///<summary>
	///Get the region object that defines the size and starting index
    ///for the largest possible region this image could represent.
	///</summary>
	property itkImageRegion^ LargestPossibleRegion { virtual itkImageRegion^ get()=0; virtual void set ( itkImageRegion^ region )=0; }

	///<summary>
	///Get/set the region object that defines the size and starting index
    ///for the region of the image requested (i.e., the region of the
    ///image to be operated on by a filter). Setting the RequestedRegion
    ///does not cause the object to be modified.
	///</summary>
	property itkImageRegion^ RequestedRegion { virtual itkImageRegion^ get()=0; virtual void set ( itkImageRegion^ region )=0; }

	///<summary>
	///Get/set the region object that defines the size and starting index
    ///of the region of the image currently loaded in memory.
	///</summary>
	property itkImageRegion^ BufferedRegion { virtual itkImageRegion^ get()=0; virtual void set ( itkImageRegion^ region )=0; }

	///<summary>Get the pointer to the underlying image data array.</summary>
	property IntPtr Buffer { virtual IntPtr get()=0; }
	
	///<summary>Get the direction cosines of the image. The direction cosines are vectors that point from one pixel to the next.</summary>
	property itkMatrix^ Direction { virtual itkMatrix^ get()=0; virtual void set ( itkMatrix^ direction )=0; }

    ///<summary>
    ///Allocates the memory for an empty image.
    ///This is the method to use to create an image from scratch (ie. not from IO).
	///The regions MUST have been set: call SetRegions() before calling this method.
	///The buffer is NOT initialised: call FillBuffer() after calling this method.
    ///</summary>
    ///<remarks>This method finalises the creation of the underlying native itk::Image.</remarks>
	virtual void Allocate ( )=0;

	///<summary>
	///Convenience method to set the LargestPossibleRegion, BufferedRegion and RequestedRegion.
    ///</summary>
    ///<param name="regions">The image region specifying the largest, requested, and buffered size.</param>
    ///<remarks>
	///This method does not allocate the image, use Allocate for that purpose.
	///</remarks>
	virtual void SetRegions ( itkImageRegion^ regions )=0;

    ///<summary>
    ///Fills the image data with the given value.
	///The image regions must be set before calling this method and
    ///the image must have been allocated.
    ///</summary>
    ///<param name="value">The pixel value to fill the image.</param>
	virtual void FillBuffer ( itkPixel^ value )=0;

    ///<summary>Read and return the image information.</summary>
    ///<param name="filename">The relative or absolute file path and name.</param>
    ///<returns>An itkImageInformation structure containing the dimensions, pixeltype,
    ///size, spacing, etc. of the given image.</returns>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	static itkImageInformation^ ReadInformation ( System::String^ filename )
	{
        try
        {
            // Marshal string to std::string
            std::string stdFilename;
    		itkObject::MarshalString( filename, stdFilename );
    
            // Read the image information
            itk::ImageIOBase::Pointer imageIO = itk::ImageIOFactory::CreateImageIO( stdFilename.c_str(), itk::ImageIOFactory::ReadMode );
			if ( imageIO.IsNull() )
			{
				throw gcnew NotSupportedException( "The given file type is not supported." );
				return nullptr;
			}
			imageIO->SetFileName( stdFilename.c_str() );
            imageIO->ReadImageInformation();

            // Get the dim, size, spacing and origin
            unsigned int dim = imageIO->GetNumberOfDimensions();
            itkSize^ size = gcnew itkSize( dim );
            itkSpacing^ spacing = gcnew itkSpacing( dim );
            itkPoint^ origin = gcnew itkPoint( dim );
            for (unsigned int i=0; i<dim; i++)
            {
				spacing[i] = imageIO->GetSpacing( i );
                origin[i] = imageIO->GetOrigin( i );
                size[i] = imageIO->GetDimensions( i );
            }

			// Get the pixel type
			itkPixelTypeEnum componentType = itkPixelTypeEnum::UnsignedChar;
			itkPixelArrayEnum arrayType = itkPixelArrayEnum::Scalar;
			switch (imageIO->GetComponentType())
			{
			case itk::ImageIOBase::UCHAR:
				componentType = itkPixelTypeEnum::UnsignedChar;
				break;
			case itk::ImageIOBase::CHAR:
				componentType = itkPixelTypeEnum::SignedChar;
				break;
			case itk::ImageIOBase::USHORT:
				componentType = itkPixelTypeEnum::UnsignedShort;
				break;
			case itk::ImageIOBase::SHORT:
				componentType = itkPixelTypeEnum::SignedShort;
				break;
			case itk::ImageIOBase::ULONG:
				componentType = itkPixelTypeEnum::UnsignedLong;
				break;
			case itk::ImageIOBase::LONG:
				componentType = itkPixelTypeEnum::SignedLong;
				break;
			case itk::ImageIOBase::FLOAT:
				componentType = itkPixelTypeEnum::Float;
				break;
			case itk::ImageIOBase::DOUBLE:
				componentType = itkPixelTypeEnum::Double;
				break;
			default:
				throw gcnew NotSupportedException( "Unsupported pixel component type: " +  ((int)imageIO->GetComponentType()).ToString() );
				return nullptr;
			}

			switch (imageIO->GetPixelType())
			{
			case itk::ImageIOBase::SCALAR:
				arrayType = itkPixelArrayEnum::Scalar;
				break;
			case itk::ImageIOBase::RGB:
				arrayType = itkPixelArrayEnum::ArrayRGB;
				break;
			case itk::ImageIOBase::RGBA:
				arrayType = itkPixelArrayEnum::ArrayRGBA;
				break;
			case itk::ImageIOBase::VECTOR:
				arrayType = itkPixelArrayEnum::ArrayVector;
				break;
			case itk::ImageIOBase::COVARIANTVECTOR:
				arrayType = itkPixelArrayEnum::ArrayCovariantVector;
				break;
			default:
				throw gcnew ApplicationException( "Unsupported pixel array type: " +  ((int)imageIO->GetPixelType()).ToString() );
				return nullptr;
			}

			itkPixelType^ pixeltype = gcnew itkPixelType( componentType, arrayType, imageIO->GetNumberOfComponents() );
            
            // Return the information structure
            return gcnew itkImageInformation( pixeltype, dim, size, spacing, origin );
        }
    	catch ( itk::ExceptionObject& ex )
    	{
            throw gcnew itkExceptionObject( ex );
        }
        catch ( Exception^ ex )
        {
            System::String^ message = "Unable to read '" + System::IO::Path::GetFileName(filename) + "'.";
            throw gcnew ApplicationException(message, ex);
        }
    }

    ///<summary>Read an image series from the given filenames.</summary>
    ///<param name="filenames">An array of absolute file paths.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadSeries ( array<System::String^>^ filenames )=0;

    ///<summary>Read an image series from the files matching the given pattern.</summary>
    ///<param name="path">An absolute path to search for the files comprising the series.</param>
    ///<param name="pattern">A pattern with wildcard character '*'.</param>
	///<example>path="C:/temp/", pattern="test_*.png".</example>
	///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadSeries ( System::String^ path, System::String^ pattern )
	{
		this->ReadSeries( System::IO::Directory::GetFiles(path, pattern) );
	}

    ///<summary>
    ///Read an image from the given DICOM directory using GDCM.
    ///This method uses the first found series identifier.
    ///</summary>
    ///<param name="directory">The directory containing the DICOM series.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadDicomDirectory( System::String^ directory ) = 0;

    ///<summary>Read an image from the given DICOM directory using GDCM.</summary>
    ///<param name="directory">The directory containing the DICOM series.</param>
    ///<param name="seriesid">The identifier of the series to read.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadDicomDirectory( System::String^ directory, System::String^ seriesid ) = 0;
    
    ///<summary>Read an image from the given DICOM directory using GDCM.</summary>
    ///<param name="directory">The directory containing the DICOM series.</param>
    ///<param name="seriesid">The identifier of the series to read.</param>
    ///<param name="restrictions">Specifies additional DICOM information to distinguish unique volumes within the directory. Eg. "0008|0021" distinguishes series based on date.</param>
    ///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void ReadDicomDirectory( System::String^ directory,
								     System::String^ seriesid,
									 ... array<System::String^>^ restrictions) = 0;

    ///<summary>Write an image series to the files matching the given format. The seriesFormat is "000".</summary>
    ///<param name="filenameFormat">The absolute path and filename format for the images. Eg. C:/temp/test_{0}.png.</param>
	///<example>filenameFormat="C:/temp/test_{0}.png".</example>
	///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void WriteSeries ( System::String^ filenameFormat )
	{
        this->WriteSeries( filenameFormat, "000" );
    }

    ///<summary>Write an image series to the files matching the given format.</summary>
    ///<param name="filenameFormat">The absolute path and filename format for the images. Eg. C:/temp/test_{0}.png.</param>
    ///<param name="seriesFormat">A format string for the series numbers. Eg. "000".</param>
	///<example>filenameFormat="C:/temp/test_{0}.png" and seriesFormat="000".</example>
	///<remarks>This method was added in ManagedITK for simplicity.</remarks>
	virtual void WriteSeries ( System::String^ filenameFormat, System::String^ seriesFormat )=0;

    ///<summary>Returns the pixel value at the given discrete location.</summary>
    ///<param name="index">The discrete location in image space.</param>
    ///<returns>The pixel value at the given discrete location.</returns>
	virtual itkPixel^ GetPixel ( itkIndex^ index )=0;

    ///<summary>Set the pixel value at the given discrete location.</summary>
    ///<param name="index">The discrete location in image space.</param>
    ///<param name="value">The new value to set.</param>
	virtual void SetPixel ( itkIndex^ index, itkPixel^ value )=0;
    
    ///<summary>Convert a physical point to a continuous index.</summary>
    ///<param name="point">The geometric location in physical space.</param>
    ///<param name="cindex">The resultant continuous location in image space.</param>
    ///<returns>true if the resulting index is within the image, false otherwise.</returns>
	virtual bool TransformPhysicalPointToContinuousIndex( itkPoint^ point, [System::Runtime::InteropServices::Out] itkContinuousIndex^% cindex )=0;
    
    ///<summary>Convert a physical point to a discrete index.</summary>
    ///<param name="point">The geometric location in physical space.</param>
    ///<param name="index">The resultant discrete location in image space.</param>
    ///<returns>true if the resulting index is within the image, false otherwise.</returns>
	virtual bool TransformPhysicalPointToIndex( itkPoint^ point, [System::Runtime::InteropServices::Out] itkIndex^% index )=0;

	///<summary>Convert a continuous index to a physical point.</summary>
    ///<param name="cindex">The continuous location in image space.</param>
	///<param name="point">The resultant geometric location in physical space.</param>
	virtual void TransformContinuousIndexToPhysicalPoint( itkContinuousIndex^ cindex, [System::Runtime::InteropServices::Out] itkPoint^% point )=0;

	///<summary>Convert a discrete index to a physical point.</summary>
    ///<param name="index">The discrete location in image space.</param>
	///<param name="point">The resultant geometric location in physical space.</param>
	virtual void TransformIndexToPhysicalPoint( itkIndex^ index, [System::Runtime::InteropServices::Out] itkPoint^% point )=0;

	///<summary>
	///Create a string representation of the image in the following format:
	///   "Size=[XX, XX, ..] Spacing=[XX, XX, ..] PixelType=ThePixelType"
	///</summary>
    ///<returns>A string representation of the image including Size, Spacing, and PixelType.</returns>
	virtual String^ ToString() override
	{
        // Construct string
		String^ result = String::Empty;
		if (this->Size != nullptr)
            result += "Size=" + this->Size->ToString() + " ";
		if (this->Spacing != nullptr)
            result += "Spacing=" + this->Spacing->ToString() + " ";
        result += "PixelType=" + this->PixelType->LongTypeString;

        // Return
        return result;
	}

}; // end ref class

} // end namespace itk

#endif