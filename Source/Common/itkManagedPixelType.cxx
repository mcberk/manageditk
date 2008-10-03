/*=============================================================================

  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedPixelType.cxx
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

#ifndef __itkManagedPixelType_cxx
#define __itkManagedPixelType_cxx

// Include some useful ManagedITK headers
#include "itkManagedINativePointer.cxx"

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

///<summary>This enumeration lists all the possible pixel types.</summary>
public enum class itkPixelTypeEnum
{
    UnsignedChar,
    SignedChar,
    UnsignedShort,
    SignedShort,
    UnsignedLong,
    SignedLong,
    Float,
    Double,
    Boolean
};

///<summary>This enumeration lists all the possible array types.</summary>
public enum class itkPixelArrayEnum
{
    Scalar,
    ArrayVector,
    ArrayCovariantVector,
    ArrayVariableLengthVector,
    ArrayVectorImage,
    ArrayRGB,
    ArrayRGBA
};

///<summary>
///This class is a managed replacement for the Image template variable TPixel.
///This class also acts in the role of itk::NumericTraits.
///</summary>
///<remarks>
///In native itk, images are templated over the pixel type: TPixel (eg. unsigned
///char, float, etc). In ManagedITK, to allow for the specification of image types
///at runtime, the itkPixelType and itkPixel classes were introduced.
///</remarks>
public ref class itkPixelType : INativePointer
{

private:
    itkPixelTypeEnum m_TypeAsEnum;
    itkPixelArrayEnum m_ArrayAsEnum;
    unsigned int m_NumberOfComponentsPerPixel;

public:
    ///<summary>Default constructor taking the pixel type. The type defaults to a single value (not an array).</summary>
    ///<param name="typeAsEnum">The enumerated type of the pixel.</param>
    itkPixelType ( itkPixelTypeEnum typeAsEnum )
    {
        this->m_TypeAsEnum = typeAsEnum;
        this->m_ArrayAsEnum = itkPixelArrayEnum::Scalar; // Default to not an array
        this->m_NumberOfComponentsPerPixel = 1; // Default to 1 component per pixel
    }

    ///<summary>Constructor taking the pixel type and number of components in array types.</summary>
    ///<param name="typeAsEnum">The enumerated type of the pixel.</param>
    ///<param name="arrayAsEnum">The enumerated type of array.</param>
    ///<param name="numberOfComponentsPerPixel">The number of components in the pixel array.</param>
    itkPixelType ( itkPixelTypeEnum typeAsEnum, itkPixelArrayEnum arrayAsEnum, unsigned int numberOfComponentsPerPixel )
    {
        // Set the member varuabkes
        this->m_TypeAsEnum = typeAsEnum;
        this->m_ArrayAsEnum = arrayAsEnum;
        this->m_NumberOfComponentsPerPixel = numberOfComponentsPerPixel;
    }

    ///<summary>Get the type of the pixel as an enumeration.</summary>
    property itkPixelTypeEnum TypeAsEnum
    {
        itkPixelTypeEnum get() { return this->m_TypeAsEnum; }
    }

    ///<summary>Get the type of the pixel element as an enumeration.</summary>
    property itkPixelArrayEnum ArrayAsEnum
    {
        itkPixelArrayEnum get() { return this->m_ArrayAsEnum; }
    }

    ///<summary>Get the number of components in array pixel types.</summary>
    ///<remarks>
    ///This property will be one for itkPixelArrayEnum::Scalar or zero if
    ///unknown at compile time (eg. itkPixelArrayEnum::VariableLengthVector).
    ///</remarks>
    property unsigned int NumberOfComponentsPerPixel
    {
        unsigned int get() { return this->m_NumberOfComponentsPerPixel; }
    }

    ///<summary>Get the number of bits the pixel type occupies.</summary>
    ///<remarks>
    ///Array element types (eg. Vector, CovariantVector) are adjusted for the
    ///size of the array by multiplying by the number of components in the array.
    ///</remarks>
    property unsigned int PixelSize
    {
        unsigned int get()
        {
            switch (this->m_TypeAsEnum)
            {
            case itkPixelTypeEnum::UnsignedChar:
                return 8*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::SignedChar:
                return 8*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::UnsignedShort:
                return 16*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::SignedShort:
                return 16*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::UnsignedLong:
                return 32*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::SignedLong:
                return 32*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::Float:
                return 16*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::Double:
                return 32*m_NumberOfComponentsPerPixel;
            case itkPixelTypeEnum::Boolean:
                return 1*m_NumberOfComponentsPerPixel;
            default:
                return 0;
            }
        }
    }

    ///<summary>Get the minimum value of the single element pixel type.</summary>
    property Object^ MinValue
    {
        Object^ get()
        {
            switch (this->m_TypeAsEnum)
            {
            case itkPixelTypeEnum::UnsignedChar:
                return (Object^)Byte::MinValue;
            case itkPixelTypeEnum::SignedChar:
                return (Object^)SByte::MinValue;
            case itkPixelTypeEnum::UnsignedShort:
                return (Object^)UInt16::MinValue;
            case itkPixelTypeEnum::SignedShort:
                return (Object^)Int16::MinValue;
            case itkPixelTypeEnum::UnsignedLong:
                return (Object^)UInt32::MinValue;
            case itkPixelTypeEnum::SignedLong:
                return (Object^)Int32::MinValue;
            case itkPixelTypeEnum::Float:
                return (Object^)Single::MinValue;
            case itkPixelTypeEnum::Double:
                return (Object^)Double::MinValue;
            case itkPixelTypeEnum::Boolean:
                return (Object^)false;
            default:
                return (Object^)0;
            }
        }
    }

    ///<summary>Get the maximum value of the single element pixel type.</summary>
    property Object^ MaxValue
    {
        Object^ get()
        {
            switch (this->m_TypeAsEnum)
            {
                case itkPixelTypeEnum::UnsignedChar:
                    return (Object^)Byte::MaxValue;
                case itkPixelTypeEnum::SignedChar:
                    return (Object^)SByte::MaxValue;
                case itkPixelTypeEnum::UnsignedShort:
                    return (Object^)UInt16::MaxValue;
                case itkPixelTypeEnum::SignedShort:
                    return (Object^)Int16::MaxValue;
                case itkPixelTypeEnum::UnsignedLong:
                    return (Object^)UInt32::MaxValue;
                case itkPixelTypeEnum::SignedLong:
                    return (Object^)Int32::MaxValue;
                case itkPixelTypeEnum::Float:
                    return (Object^)Single::MaxValue;
                case itkPixelTypeEnum::Double:
                    return (Object^)Double::MaxValue;
                case itkPixelTypeEnum::Boolean:
                    return (Object^)true;
                default:
                    return (Object^)0;
            }
        }
    }

    ///<summary>Get the zero value of the single element pixel type.</summary>
    property Object^ Zero
    {
        Object^ get()
        {
            switch (this->m_TypeAsEnum)
            {
            case itkPixelTypeEnum::UnsignedChar:
                // Fall through
            case itkPixelTypeEnum::SignedChar:
                // Fall through
            case itkPixelTypeEnum::UnsignedShort:
                // Fall through
            case itkPixelTypeEnum::SignedShort:
                // Fall through
            case itkPixelTypeEnum::UnsignedLong:
                // Fall through
            case itkPixelTypeEnum::SignedLong:
                return (Object^)0;
            case itkPixelTypeEnum::Float:
                // Fall through
            case itkPixelTypeEnum::Double:
                return (Object^)0.0;
            case itkPixelTypeEnum::Boolean:
                return (Object^)false;
            default:
                return (Object^)0;
            }
        }
    }

    ///<summary>
    ///Get if the pixel is a scalar value (one value per pixel)
    ///or a vector/array value (mor than one value per pixel).
    ///</summary>
    ///<returns>True if the type is a scalar, false otherwise.</returns>
    property bool IsScalar
    {
        bool get() { return (this->m_ArrayAsEnum == itkPixelArrayEnum::Scalar); }
    }

    ///<summary>
    ///Get if the pixel is a scalar value (one value per pixel)
    ///or a vector/array value (mor than one value per pixel).
    ///</summary>
    ///<returns>True if the type is an array or vector, false otherwise.</returns>
    property bool IsArray
    {
        bool get() { return (this->m_ArrayAsEnum != itkPixelArrayEnum::Scalar); }
    }

    ///<summary>
    ///Get if the pixel is a color value (ie. RGB or RGBA) value.
    ///</summary>
    ///<returns>True if the type is a color type (ie. RGB or RGBA), false otherwise.</returns>
    property bool IsColor
    {
        bool get()
        {
            return (this->m_ArrayAsEnum == itkPixelArrayEnum::ArrayRGB ||
                    this->m_ArrayAsEnum == itkPixelArrayEnum::ArrayRGBA);
        }
    }

    ///<summary>
    ///Get if the pixel value type is a char value (ie. unsigned char or signed char).
    ///</summary>
    ///<returns>True if the pixel type is a char value (ie. unsigned char or signed char), false otherwise.</returns>
    property bool IsChar
    {
        bool get()
        {
            return (this->m_TypeAsEnum == itkPixelTypeEnum::UnsignedChar ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::SignedChar);
        }
    }

    ///<summary>
    ///Get if the pixel value type is a short value (ie. unsigned short or signed short).
    ///</summary>
    ///<returns>True if the pixel type is a short value (ie. unsigned short or signed short), false otherwise.</returns>
    property bool IsShort
    {
        bool get()
        {
            return (this->m_TypeAsEnum == itkPixelTypeEnum::UnsignedShort ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::SignedShort);
        }
    }

    ///<summary>
    ///Get if the pixel value type is a long value (ie. unsigned long or signed long).
    ///</summary>
    ///<returns>True if the pixel type is a long value (ie. unsigned long or signed long), false otherwise.</returns>
    property bool IsLong
    {
        bool get()
        {
            return (this->m_TypeAsEnum == itkPixelTypeEnum::UnsignedLong ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::SignedLong);
        }
    }

    ///<summary>
    ///Get if the pixel value type is a real value (ie. float or double),
    ///as opposed to an integer value.
    ///</summary>
    ///<returns>True if the pixel type is float or double, false otherwise.</returns>
    property bool IsReal
    {
        bool get()
        {
            return (this->m_TypeAsEnum == itkPixelTypeEnum::Float ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::Double);
        }
    }

    ///<summary>
    ///Get if the pixel value type is a single bit value (ie. boolean).
    ///</summary>
    ///<returns>True if the pixel type is boolean, false otherwise.</returns>
    property bool IsSingleBit
    {
        bool get()
        {
            return (this->m_TypeAsEnum == itkPixelTypeEnum::Boolean);
        }
    }

    ///<summary>
    ///Get if the pixel value type is an integer value (ie. unsigned char, signed long, etc),
    ///as opposed to a real value.
    ///</summary>
    ///<returns>True if the pixel type is integer (ie. unsigned char, signed long, etc), false otherwise.</returns>
    property bool IsInteger
    {
        bool get() { return !this->IsReal; }
    }

    ///<summary>
    ///Get if the pixel value type is an signed value (ie. signed char, signed long, float, etc).
    ///</summary>
    ///<returns>True if the pixel type is signed (ie. signed char, signed long, float, etc), false otherwise.</returns>
    property bool IsSigned
    {
        bool get()
        {
            return (this->m_TypeAsEnum == itkPixelTypeEnum::SignedChar ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::SignedShort ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::SignedLong ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::Float ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::Double);
        }
    }

    ///<summary>
    ///Get if the pixel value type is an unsigned value (ie. unsigned char, unsigned long, etc).
    ///Boolean pixel values are considered unsigned.
    ///</summary>
    ///<returns>True if the pixel type is unsigned (ie. unsigned char, unsigned long, etc), false otherwise.</returns>
    property bool IsUnsigned
    {
        bool get()
        {
            return (this->m_TypeAsEnum == itkPixelTypeEnum::UnsignedChar ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::UnsignedShort ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::UnsignedLong ||
                    this->m_TypeAsEnum == itkPixelTypeEnum::Boolean);
        }
    }

    ///<summary>Get a string representing the type instance of this INativePointer.</summary>
    ///<example>"UC" = UnsignedChar, "SS" = Signed Short, "F" = float.</example>
    virtual property String^ MangledTypeString
    {
        String^ get()
        {
            String^ format = String::Empty;

            switch (this->m_ArrayAsEnum)
            {
            case itkPixelArrayEnum::Scalar:
                format = "{0}";
                break;
            case itkPixelArrayEnum::ArrayVector:
                format = "V{0}" + this->m_NumberOfComponentsPerPixel.ToString();
                break;
            case itkPixelArrayEnum::ArrayCovariantVector:
                format = "CV{0}" + this->m_NumberOfComponentsPerPixel.ToString();
                break;
            case itkPixelArrayEnum::ArrayVariableLengthVector:
                format = "VLV{0}";
                break;
            case itkPixelArrayEnum::ArrayVectorImage:
                format = "VI{0}";
                break;
            case itkPixelArrayEnum::ArrayRGB:
                format = "RGB{0}";
                break;
            case itkPixelArrayEnum::ArrayRGBA:
                format = "RGBA{0}";
                break;
            default:
                format = "Unknown{0}";
            }

            switch (this->m_TypeAsEnum)
            {
            case itkPixelTypeEnum::UnsignedChar:
                return String::Format(format, "UC");
            case itkPixelTypeEnum::SignedChar:
                return String::Format(format, "SC");
            case itkPixelTypeEnum::UnsignedShort:
                return String::Format(format, "US");
            case itkPixelTypeEnum::SignedShort:
                return String::Format(format, "SS");
            case itkPixelTypeEnum::UnsignedLong:
                return String::Format(format, "UL");
            case itkPixelTypeEnum::SignedLong:
                return String::Format(format, "SL");
            case itkPixelTypeEnum::Float:
                return String::Format(format, "F");
            case itkPixelTypeEnum::Double:
                return String::Format(format, "D");
            case itkPixelTypeEnum::Boolean:
                return String::Format(format, "B");
            default:
                return String::Empty;
            }
        }
    }

    ///<summary>The NativePointer property is not applicable for itkPixelType.</summary>
    ///<returns>Always returns zero for itkPixelType.</returns>
    virtual property IntPtr NativePointer
    {
        // INativePointer.NativePointer is not applicable for itkPixelType.
        IntPtr get() { return IntPtr::Zero; }
        void set(IntPtr ptr) { /*Do nothing*/ }
    }

    ///<summary>Get a 'long' string representing the pixel type.</summary>
    ///<example>"Unsigned Char", "Float"</example>
    property String^ LongTypeString
    {
        String^ get()
        {
            String^ format = String::Empty;

            switch (this->m_ArrayAsEnum)
            {
            case itkPixelArrayEnum::Scalar:
                format = "{0}";
                break;
            case itkPixelArrayEnum::ArrayVector:
                format = "Vector {0}";
                break;
            case itkPixelArrayEnum::ArrayCovariantVector:
                format = "Covariant Vector {0}";
                break;
            case itkPixelArrayEnum::ArrayVariableLengthVector:
                format = "Variable Length Vector {0}";
                break;
            case itkPixelArrayEnum::ArrayVectorImage:
                format = "Vector Image {0}";
                break;
            case itkPixelArrayEnum::ArrayRGB:
                format = "RGB {0}";
                break;
            case itkPixelArrayEnum::ArrayRGBA:
                format = "RGBA {0}";
                break;
            default:
                format = "Unknown {0}";
            }

            switch (this->m_TypeAsEnum)
            {
            case itkPixelTypeEnum::UnsignedChar:
                return String::Format(format, "Unsigned Char");
            case itkPixelTypeEnum::SignedChar:
                return String::Format(format, "Signed Char");
            case itkPixelTypeEnum::UnsignedShort:
                return String::Format(format, "Unsigned Short");
            case itkPixelTypeEnum::SignedShort:
                return String::Format(format, "Signed Short");
            case itkPixelTypeEnum::UnsignedLong:
                return String::Format(format, "Unsigned Long");
            case itkPixelTypeEnum::SignedLong:
                return String::Format(format, "Signed Long");
            case itkPixelTypeEnum::Float:
                return String::Format(format, "Float");
            case itkPixelTypeEnum::Double:
                return String::Format(format, "Double");
            case itkPixelTypeEnum::Boolean:
                return String::Format(format, "Boolean");
            default:
                return String::Empty;
            }
        }
    }

    ///<summary>Get a 'long' string representing the pixel type.</summary>
    ///<example>"Unsigned Char", "Float"</example>
    virtual String^ ToString() override
    {
        return this->LongTypeString;
    }

    ///<summary>Create a pixel type from a given string.</summary>
    ///<param name="mangledType">The type of the pixel as a string. Eg. "UC" = UnsignedChar.</param>
    ///<returns>A new pixel type instance of the type specified by the mangled string.</returns>
    ///<remarks>This method also works with a mangledType string from an image. Eg. "ISS3" = SignedShort.</remarks>
    static itkPixelType^ CreateFromMangledType(String^ mangledType)
    {
        const bool IGNORE_CASE = true;
        System::Globalization::CultureInfo^ currentCulture = System::Globalization::CultureInfo::CurrentCulture;

        // Trim any 'I's from the start
        String^ sType = mangledType->TrimStart('I', 'i');

        // Setup default member information
        bool foundPixelType = false;
        itkPixelTypeEnum enumType = itkPixelTypeEnum::UnsignedChar;
        itkPixelArrayEnum enumArray = itkPixelArrayEnum::Scalar;
        System::Int32 iNumberOfComponentsPerPixel = 1;

        // Detect the element type
        // NOTE: The order of the below if statements are important!
        if (sType->StartsWith("VI", IGNORE_CASE, currentCulture))
        {
            sType = sType->Replace("VI", "");
            enumArray = itkPixelArrayEnum::ArrayVectorImage;
            iNumberOfComponentsPerPixel = 0; //TODO: The number of components is unknown
        }
        else if (sType->StartsWith("VLV", IGNORE_CASE, currentCulture))
        {
            sType = sType->Replace("VLV", "");
            enumArray = itkPixelArrayEnum::ArrayVariableLengthVector;
            iNumberOfComponentsPerPixel = 0; //TODO: The number of components is unknown
        }
        else if (sType->StartsWith("V", IGNORE_CASE, currentCulture))
        {
            sType = sType->Replace("V", "");
            enumArray = itkPixelArrayEnum::ArrayVector;
        }
        else if (sType->StartsWith("CV", IGNORE_CASE, currentCulture))
        {
            sType = sType->Replace("CV", "");
            enumArray = itkPixelArrayEnum::ArrayCovariantVector;
        }
        else if (sType->StartsWith("RGBA", IGNORE_CASE, currentCulture))
        {
            sType = sType->Replace("RGBA", "");
            enumArray = itkPixelArrayEnum::ArrayRGBA;
            iNumberOfComponentsPerPixel = 4;
        }
        else if (sType->StartsWith("RGB", IGNORE_CASE, currentCulture))
        {
            sType = sType->Replace("RGB", "");
            enumArray = itkPixelArrayEnum::ArrayRGB;
            iNumberOfComponentsPerPixel = 3;
        }

        // Detect the pixel type and get the number of elements
        String^ sNumberOfComponentsPerPixel = String::Empty;
        if (sType->StartsWith("UC", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::UnsignedChar;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(2, 1);
        }
        else if (sType->StartsWith("SC", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::SignedChar;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(2, 1);
        }
        else if (sType->StartsWith("US", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::UnsignedShort;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(2, 1);
        }
        else if (sType->StartsWith("SS", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::SignedShort;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(2, 1);
        }
        else if (sType->StartsWith("UL", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::UnsignedLong;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(2, 1);
        }
        else if (sType->StartsWith("SL", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::SignedLong;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(2, 1);
        }
        else if (sType->StartsWith("F", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::Float;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(1, 1);
        }
        else if (sType->StartsWith("D", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::Double;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(1, 1);
        }
        else if (sType->StartsWith("B", IGNORE_CASE, currentCulture))
        {
            enumType = itkPixelTypeEnum::Boolean;
            foundPixelType = true;
            if (enumArray == itkPixelArrayEnum::ArrayVector ||
                enumArray == itkPixelArrayEnum::ArrayCovariantVector)
                sNumberOfComponentsPerPixel = sType->Substring(1, 1);
        }

        // Try to parse the number of elements
        if (enumArray == itkPixelArrayEnum::ArrayVector ||
            enumArray == itkPixelArrayEnum::ArrayCovariantVector)
        {
          if ( !Int32::TryParse(sNumberOfComponentsPerPixel, iNumberOfComponentsPerPixel) )
              throw gcnew NotSupportedException("The pixel type '" + mangledType + "' is not supported. The number of components per pixel could not be determined.");
        }

        // Check that we got everything
        if ( foundPixelType )
            return gcnew itkPixelType(enumType, enumArray, iNumberOfComponentsPerPixel);
        else
            throw gcnew NotSupportedException("The pixel type '" + mangledType + "' is not supported. The pixel type could not be determined.");
    }

    // Scalar Pixel Types
    static itkPixelType^ UC =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar );
    static itkPixelType^ SC =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedChar );
    static itkPixelType^ US =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort );
    static itkPixelType^ SS =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedShort );
    static itkPixelType^ UL =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedLong );
    static itkPixelType^ SL =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedLong );
    static itkPixelType^ F =
        gcnew itkPixelType ( itkPixelTypeEnum::Float );
    static itkPixelType^ D =
        gcnew itkPixelType ( itkPixelTypeEnum::Double );
    static itkPixelType^ B =
        gcnew itkPixelType ( itkPixelTypeEnum::Boolean );

    // Vector Pixel Types
    static itkPixelType^ VUC2 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VUC3 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayVector, 3 );
    static itkPixelType^ VSC2 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VSC3 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayVector, 3 );
    static itkPixelType^ VUS2 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VUS3 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayVector, 3 );
    static itkPixelType^ VSS2 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VSS3 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayVector, 3 );
    static itkPixelType^ VUL2 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VUL3 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayVector, 3 );
    static itkPixelType^ VSL2 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VSL3 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayVector, 3 );
    static itkPixelType^ VF2 =
        gcnew itkPixelType ( itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VF3 =
        gcnew itkPixelType ( itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayVector, 3 );
    static itkPixelType^ VD2 =
        gcnew itkPixelType ( itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayVector, 2 );
    static itkPixelType^ VD3 =
        gcnew itkPixelType ( itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayVector, 3 );

    // CovariantVector Pixel Types
    static itkPixelType^ CVUC2 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVUC3 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayCovariantVector, 3 );
    static itkPixelType^ CVSC2 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVSC3 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayCovariantVector, 3 );
    static itkPixelType^ CVUS2 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVUS3 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayCovariantVector, 3 );
    static itkPixelType^ CVSS2 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVSS3 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayCovariantVector, 3 );
    static itkPixelType^ CVUL2 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVUL3 =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayCovariantVector, 3 );
    static itkPixelType^ CVSL2 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVSL3 =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayCovariantVector, 3 );
    static itkPixelType^ CVF2 =
        gcnew itkPixelType ( itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVF3 =
        gcnew itkPixelType ( itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayCovariantVector, 3 );
    static itkPixelType^ CVD2 =
        gcnew itkPixelType ( itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayCovariantVector, 2 );
    static itkPixelType^ CVD3 =
        gcnew itkPixelType ( itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayCovariantVector, 3 );

    // VectorImage Pixel Types
    static itkPixelType^ VIUC =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayVectorImage, 0 );
    static itkPixelType^ VISC =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayVectorImage, 0 );
    static itkPixelType^ VIUS =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayVectorImage, 0 );
    static itkPixelType^ VISS =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayVectorImage, 0 );
    static itkPixelType^ VIUL =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayVectorImage, 0 );
    static itkPixelType^ VISL =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayVectorImage, 0 );
    static itkPixelType^ VIF =
        gcnew itkPixelType ( itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayVectorImage, 0 );
    static itkPixelType^ VID =
        gcnew itkPixelType ( itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayVectorImage, 0 );

    // VariableLengthVector Pixel Types
    static itkPixelType^ VLVUC =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );
    static itkPixelType^ VLVSC =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );
    static itkPixelType^ VLVUS =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );
    static itkPixelType^ VLVSS =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );
    static itkPixelType^ VLVUL =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );
    static itkPixelType^ VLVSL =
        gcnew itkPixelType ( itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );
    static itkPixelType^ VLVF =
        gcnew itkPixelType ( itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );
    static itkPixelType^ VLVD =
        gcnew itkPixelType ( itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayVariableLengthVector, 0 );

    // RGB and RGBA Pixel Types
    static itkPixelType^ RGBUC =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayRGB, 3 );
    static itkPixelType^ RGBAUC =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayRGBA, 4 );
    static itkPixelType^ RGBUS =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayRGB, 3 );
    static itkPixelType^ RGBAUS =
        gcnew itkPixelType ( itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayRGBA, 4 );

};

} // end namespace itk

#endif
