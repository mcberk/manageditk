/*=============================================================================

  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedPixel.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date: 2008-04-15 20:48:33 +0200 (Tue, 15 Apr 2008) $
  Revision:  $Revision: 10 $

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

#ifndef __itkManagedPixel_cxx
#define __itkManagedPixel_cxx

// Include some useful ManagedITK headers
#include "itkManagedPixelType.cxx"
#include "itkManagedVector.cxx"

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

///<summary>
///This class is a managed replacement for the Image template variable TPixel.
///</summary>
///<remarks>
///In native itk, images are templated over the pixel type: TPixel (eg. unsigned
///char, float, etc). In ManagedITK, to allow for the specification of image types
///at runtime, the itkPixelType and itkPixel classes were introduced.
///</remarks>
public ref class itkPixel
{

private:
    itkPixelType^ m_Type;
    Object^ m_Value;

public:
    ///<summary>Default constructor taking the pixel type and value.</summary>
    ///<param name="type">The type of the pixel to create.</param>
    ///<param name="value">The value of the pixel as a generic Object.</param>
    itkPixel ( itkPixelType^ type, Object^ value )
    {
        this->m_Type = type;
        this->m_Value = value;
    }

    ///<summary>Get the type of the pixel.</summary>
    property itkPixelType^ Type
    {
        itkPixelType^ get() { return this->m_Type; }
    }

    ///<summary>Get the generic Object value of the pixel.</summary>
    property Object^ Value
    {
        Object^ get() { return this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an unsigned char (ie. Byte).</summary>
    property Byte ValueAsUC
    {
        Byte get() { return Convert::ToByte(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as a signed char (ie. SByte).</summary>
    property SByte ValueAsSC
    {
        SByte get() { return Convert::ToSByte(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as an unsigned short (ie. UInt16).</summary>
    property UInt16 ValueAsUS
    {
        UInt16 get() { return Convert::ToUInt16(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as a signed short (ie. Int16).</summary>
    property Int16 ValueAsSS
    {
        Int16 get() { return Convert::ToInt16(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as an unsigned long (ie. UInt32).</summary>
    property UInt32 ValueAsUL
    {
        UInt32 get() { return Convert::ToUInt32(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as a signed long (ie. Int32).</summary>
    property Int32 ValueAsSL
    {
        Int32 get() { return Convert::ToInt32(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as a float (ie. Single).</summary>
    property Single ValueAsF
    {
        Single get() { return Convert::ToSingle(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as a double.</summary>
    property Double ValueAsD
    {
        Double get() { return Convert::ToDouble(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as a boolean.</summary>
    property Boolean ValueAsB
    {
        Boolean get() { return Convert::ToBoolean(this->m_Value); }
    }

    ///<summary>Get the value of the pixel as an array.</summary>
    generic<typename TValueType>
    where TValueType : System::IComparable<TValueType>, System::IConvertible
    virtual itkArray<TValueType>^ ValueAsArray()
    {
        return (itkArray<TValueType>^)this->m_Value;
    }

    ///<summary>Get the value of the pixel as an array of UC.</summary>
    property itkArray<System::Byte>^ ValueAsArrayOfUC
    {
        itkArray<System::Byte>^ get() { return (itkArray<System::Byte>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an array of SC.</summary>
    property itkArray<System::SByte>^ ValueAsArrayOfSC
    {
        itkArray<System::SByte>^ get() { return (itkArray<System::SByte>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an array of US.</summary>
    property itkArray<System::UInt16>^ ValueAsArrayOfUS
    {
        itkArray<System::UInt16>^ get() { return (itkArray<System::UInt16>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an array of SS.</summary>
    property itkArray<System::Int16>^ ValueAsArrayOfSS
    {
        itkArray<System::Int16>^ get() { return (itkArray<System::Int16>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an array of UL.</summary>
    property itkArray<System::UInt32>^ ValueAsArrayOfUL
    {
        itkArray<System::UInt32>^ get() { return (itkArray<System::UInt32>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an array of SL.</summary>
    property itkArray<System::Int32>^ ValueAsArrayOfSL
    {
        itkArray<System::Int32>^ get() { return (itkArray<System::Int32>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an array of F.</summary>
    property itkArray<System::Single>^ ValueAsArrayOfF
    {
        itkArray<System::Single>^ get() { return (itkArray<System::Single>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an array of D.</summary>
    property itkArray<System::Double>^ ValueAsArrayOfD
    {
        itkArray<System::Double>^ get() { return (itkArray<System::Double>^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as a itkVector.</summary>
    property itkVector^ ValueAsVector
    {
        itkVector^ get() { return (itkVector^)this->m_Value; }
    }

    ///<summary>Get the value of the pixel as an Int32.</summary>
    ///<remarks>This is the same as SignedLong.</remarks>
    property int ValueAsInt32
    {
        int get() { return Convert::ToInt32(this->m_Value); }
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( unsigned char value )
    {
        return gcnew itkPixel( itkPixelType::UC, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( signed char value )
    {
        return gcnew itkPixel( itkPixelType::SC, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( unsigned short value )
    {
        return gcnew itkPixel( itkPixelType::US, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( signed short value )
    {
        return gcnew itkPixel( itkPixelType::SS, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( unsigned long value )
    {
        return gcnew itkPixel( itkPixelType::UL, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( signed long value )
    {
        return gcnew itkPixel( itkPixelType::SL, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( float value )
    {
        return gcnew itkPixel( itkPixelType::F, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( double value )
    {
        return gcnew itkPixel( itkPixelType::D, value );
    }

    ///<summary>Implicit conversion operator to create scalar itkPixel from literal.</summary>
    static operator itkPixel^ ( bool value )
    {
        return gcnew itkPixel( itkPixelType::B, value );
    }

    ///<summary>Return a string representation of the pixel.</summary>
    ///<returns>A string representation of the pixel.</returns>
    virtual String^ ToString() override
    {
        return this->ToString(nullptr);
    }

    ///<summary>Return a string representation of the pixel.</summary>
    ///<param name="format">The format string for the conversion (eg. "000.00").</param>
    ///<returns>A string representation of the pixel.</returns>
    virtual String^ ToString(String^ format)
    {
        if (this->Type->ArrayAsEnum != itkPixelArrayEnum::Scalar)
        {
            switch (this->Type->TypeAsEnum)
            {
            case itkPixelTypeEnum::UnsignedChar:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsArrayOfUC->ToString("000");
                else
                    return this->ValueAsArrayOfUC->ToString(format);
            case itkPixelTypeEnum::SignedShort:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsArrayOfSS->ToString("000");
                else
                    return this->ValueAsArrayOfSS->ToString(format);
            case itkPixelTypeEnum::Float:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsArrayOfF->ToString("000.00");
                else
                    return this->ValueAsArrayOfF->ToString(format);
            case itkPixelTypeEnum::Double:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsArrayOfD->ToString("000.00");
                else
                    return this->ValueAsArrayOfD->ToString(format);
            }
        }
        else
        {
            switch (this->Type->TypeAsEnum)
            {
            case itkPixelTypeEnum::UnsignedChar:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsUC.ToString("000");
                else
                    return this->ValueAsUC.ToString(format);
            case itkPixelTypeEnum::SignedChar:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsSC.ToString("000");
                else
                    return this->ValueAsSC.ToString(format);
            case itkPixelTypeEnum::UnsignedShort:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsUS.ToString("00000");
                else
                    return this->ValueAsUS.ToString(format);
            case itkPixelTypeEnum::SignedShort:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsSS.ToString("00000");
                else
                    return this->ValueAsSS.ToString(format);
            case itkPixelTypeEnum::UnsignedLong:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsUL.ToString("000000000");
                else
                    return this->ValueAsUL.ToString(format);
            case itkPixelTypeEnum::SignedLong:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsSL.ToString("000000000");
                else
                    return this->ValueAsSL.ToString(format);
            case itkPixelTypeEnum::Float:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsF.ToString("000.000");
                else
                    return this->ValueAsF.ToString(format);
            case itkPixelTypeEnum::Double:
                if (format == nullptr || format->Length == 0)
                    return this->ValueAsD.ToString("000.000");
                else
                    return this->ValueAsD.ToString(format);
            case itkPixelTypeEnum::Boolean:
                return this->ValueAsB.ToString();
            }
        }

        return this->Value->ToString();
    }


    ///<summary>
    ///Parses a string and creates a Pixel of the given type.
    ///This method consumes any exceptions caused by parsing,
    ///returning true on success and false on failure.
    ///</summary>
    ///<param name="type">The type of pixel to parse.</param>
    ///<param name="value">The string representing the pixel. Eg. "100", "0.50", "-1234"</param>
    ///<param name="pixel">The resultant pixel parsed from the string, or null on failure.</param>
    ///<returns>True if the parse was successful, otherwise false.</returns>
    static bool TryParse(itkPixelType^ type, String^ value, [System::Runtime::InteropServices::Out] itkPixel^% pixel)
    {
        Byte resultUC;
        SByte resultSC;
        UInt16 resultUS;
        Int16 resultSS;
        UInt32 resultUL;
        Int32 resultSL;
        Single resultF;
        Double resultD;
        Boolean resultB;

        bool result = false;
        pixel = nullptr;

        if (type->ArrayAsEnum != itkPixelArrayEnum::Scalar)
            throw gcnew NotSupportedException("Can not parse pixel: the PixelType '" + type->ToString() + "' is not supported by this method.");

        switch (type->TypeAsEnum)
        {
            case itkPixelTypeEnum::UnsignedChar:
                if (Byte::TryParse(value, resultUC))
                {
                    pixel = gcnew itkPixel(itkPixelType::UC, resultUC);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::SignedChar:
                if (SByte::TryParse(value, resultSC))
                {
                    pixel = gcnew itkPixel(itkPixelType::SC, resultSC);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::UnsignedShort:
                if (UInt16::TryParse(value, resultUS))
                {
                    pixel = gcnew itkPixel(itkPixelType::US, resultUS);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::SignedShort:
                if (Int16::TryParse(value, resultSS))
                {
                    pixel = gcnew itkPixel(itkPixelType::SS, resultSS);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::UnsignedLong:
                if (UInt32::TryParse(value, resultUL))
                {
                    pixel = gcnew itkPixel(itkPixelType::UL, resultUL);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::SignedLong:
                if (Int32::TryParse(value, resultSL))
                {
                    pixel = gcnew itkPixel(itkPixelType::SL, resultSL);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::Float:
                if (Single::TryParse(value, resultF))
                {
                    pixel = gcnew itkPixel(itkPixelType::F, resultF);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::Double:
                if (Double::TryParse(value, resultD))
                {
                    pixel = gcnew itkPixel(itkPixelType::D, resultD);
                    result = true;
                }
                break;
            case itkPixelTypeEnum::Boolean:
                if (Boolean::TryParse(value, resultB))
                {
                    pixel = gcnew itkPixel(itkPixelType::B, resultB);
                    result = true;
                }
                break;
            default:
                throw gcnew NotSupportedException("Can not parse pixel: the PixelType '" + type->ToString() + "' is not supported by this method.");
        }// end switch

        return result;
    }

    ///<summary>Create a new pixel of the given type with zero value.</summary>
    ///<param name="type">The type of pixel to create.</param>
    ///<returns>A new pixel with the value equal to zero.</returns>
    static itkPixel^ NewZero(itkPixelType^ type)
    {
        if (type->IsArray)
          throw gcnew NotSupportedException("Could not make minimum: the PixelType '" + type->ToString() + "' is not supported by this method.");

        switch (type->TypeAsEnum)
        {
            case itkPixelTypeEnum::UnsignedChar:
                return gcnew itkPixel(itkPixelType::UC, (Object^)0);
            case itkPixelTypeEnum::SignedChar:
                return gcnew itkPixel(itkPixelType::SC, (Object^)0);
            case itkPixelTypeEnum::UnsignedShort:
                return gcnew itkPixel(itkPixelType::US, (Object^)0);
            case itkPixelTypeEnum::SignedShort:
                return gcnew itkPixel(itkPixelType::SS, (Object^)0);
            case itkPixelTypeEnum::UnsignedLong:
                return gcnew itkPixel(itkPixelType::UL, (Object^)0);
            case itkPixelTypeEnum::SignedLong:
                return gcnew itkPixel(itkPixelType::SL, (Object^)0);
            case itkPixelTypeEnum::Float:
                return gcnew itkPixel(itkPixelType::F, (Object^)0.0);
            case itkPixelTypeEnum::Double:
                return gcnew itkPixel(itkPixelType::D, (Object^)0.0);
            case itkPixelTypeEnum::Boolean:
                return gcnew itkPixel(itkPixelType::B, (Object^)false);
            default:
                throw gcnew NotSupportedException("Could not make zero: the PixelType '" + type->ToString() + "' is not supported by this method.");
        }// end switch
    }

    ///<summary>Create a new pixel of the given type with the minimum value.</summary>
    ///<param name="type">The type of pixel to create.</param>
    ///<returns>A new pixel with the value equal to the minimum value.</returns>
    static itkPixel^ NewMin(itkPixelType^ type)
    {
        if (type->IsArray)
          throw gcnew NotSupportedException("Could not make minimum: the PixelType '" + type->ToString() + "' is not supported by this method.");

        switch (type->TypeAsEnum)
        {
            case itkPixelTypeEnum::UnsignedChar:
                return gcnew itkPixel(itkPixelType::UC, type->MinValue);
            case itkPixelTypeEnum::SignedChar:
                return gcnew itkPixel(itkPixelType::SC, type->MinValue);
            case itkPixelTypeEnum::UnsignedShort:
                return gcnew itkPixel(itkPixelType::US, type->MinValue);
            case itkPixelTypeEnum::SignedShort:
                return gcnew itkPixel(itkPixelType::SS, type->MinValue);
            case itkPixelTypeEnum::UnsignedLong:
                return gcnew itkPixel(itkPixelType::UL, type->MinValue);
            case itkPixelTypeEnum::SignedLong:
                return gcnew itkPixel(itkPixelType::SL, type->MinValue);
            case itkPixelTypeEnum::Float:
                return gcnew itkPixel(itkPixelType::F, type->MinValue);
            case itkPixelTypeEnum::Double:
                return gcnew itkPixel(itkPixelType::D, type->MinValue);
            case itkPixelTypeEnum::Boolean:
                return gcnew itkPixel(itkPixelType::B, type->MinValue);
            default:
                throw gcnew NotSupportedException("Could not make minimum: the PixelType '" + type->ToString() + "' is not supported by this method.");
        }// end switch
    }

    ///<summary>Create a new pixel of the given type with the maximum value.</summary>
    ///<param name="type">The type of pixel to create.</param>
    ///<returns>A new pixel with the value equal to the maximum value.</returns>
    static itkPixel^ NewMax(itkPixelType^ type)
    {
        if (type->IsArray)
          throw gcnew NotSupportedException("Could not make maximum: the PixelType '" + type->ToString() + "' is not supported by this method.");

        switch (type->TypeAsEnum)
        {
            case itkPixelTypeEnum::UnsignedChar:
                return gcnew itkPixel(itkPixelType::UC, type->MaxValue);
            case itkPixelTypeEnum::SignedChar:
                return gcnew itkPixel(itkPixelType::SC, type->MaxValue);
            case itkPixelTypeEnum::UnsignedShort:
                return gcnew itkPixel(itkPixelType::US, type->MaxValue);
            case itkPixelTypeEnum::SignedShort:
                return gcnew itkPixel(itkPixelType::SS, type->MaxValue);
            case itkPixelTypeEnum::UnsignedLong:
                return gcnew itkPixel(itkPixelType::UL, type->MaxValue);
            case itkPixelTypeEnum::SignedLong:
                return gcnew itkPixel(itkPixelType::SL, type->MaxValue);
            case itkPixelTypeEnum::Float:
                return gcnew itkPixel(itkPixelType::F, type->MaxValue);
            case itkPixelTypeEnum::Double:
                return gcnew itkPixel(itkPixelType::D, type->MaxValue);
            case itkPixelTypeEnum::Boolean:
                return gcnew itkPixel(itkPixelType::B, type->MaxValue);
            default:
                throw gcnew NotSupportedException("Could not make maximum: the PixelType '" + type->ToString() + "' is not supported by this method.");
        }// end switch
    }
}; // end ref class

///<summary>This class is a managed wrapper for UnsignedChar pixels.</summary>
public ref class itkPixel_UC : itkPixel
{
public:
    itkPixel_UC(Object^ value) : itkPixel ( itkPixelType::UC, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::UC ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::UC ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::UC ); }
};

///<summary>This class is a managed wrapper for SignedChar pixels.</summary>
public ref class itkPixel_SC : itkPixel
{
public:
    itkPixel_SC(Object^ value) : itkPixel ( itkPixelType::SC, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::SC ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::SC ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::SC ); }
};

///<summary>This class is a managed wrapper for UnsignedShort pixels.</summary>
public ref class itkPixel_US : itkPixel
{
public:
    itkPixel_US(Object^ value) : itkPixel ( itkPixelType::US, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::US ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::US ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::US ); }
};

///<summary>This class is a managed wrapper for SignedShort pixels.</summary>
public ref class itkPixel_SS : itkPixel
{
public:
    itkPixel_SS(Object^ value) : itkPixel ( itkPixelType::SS, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::SS ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::SS ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::SS ); }
};

///<summary>This class is a managed wrapper for UnsignedLong pixels.</summary>
public ref class itkPixel_UL : itkPixel
{
public:
    itkPixel_UL(Object^ value) : itkPixel ( itkPixelType::UL, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::UL ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::UL ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::UL ); }
};

///<summary>This class is a managed wrapper for SignedLong pixels.</summary>
public ref class itkPixel_SL : itkPixel
{
public:
    itkPixel_SL(Object^ value) : itkPixel ( itkPixelType::SL, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::SL ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::SL ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::SL ); }
};

///<summary>This class is a managed wrapper for Float pixels.</summary>
public ref class itkPixel_F : itkPixel
{
public:
    itkPixel_F(Object^ value) : itkPixel ( itkPixelType::F, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::F ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::F ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::F ); }
};

///<summary>This class is a managed wrapper for Double pixels.</summary>
public ref class itkPixel_D : itkPixel
{
public:
    itkPixel_D(Object^ value) : itkPixel ( itkPixelType::D, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::D ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::D ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::D ); }
};

///<summary>This class is a managed wrapper for boolean pixels.</summary>
public ref class itkPixel_B : itkPixel
{
public:
    itkPixel_B(Object^ value) : itkPixel ( itkPixelType::B, value )
    { }

    static itkPixel^ NewZero()
    { return itkPixel::NewZero( itkPixelType::B ); }

    static itkPixel^ NewMin()
    { return itkPixel::NewMin( itkPixelType::B ); }

    static itkPixel^ NewMax()
    { return itkPixel::NewMax( itkPixelType::B ); }
};

///<summary>This class is a managed wrapper for Vector Unsigned Char pixels.</summary>
public ref class itkPixel_VUC : itkPixel
{
public:
    itkPixel_VUC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for Vector Signed Char pixels.</summary>
public ref class itkPixel_VSC : itkPixel
{
public:
    itkPixel_VSC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for Vector Unsigned Short pixels.</summary>
public ref class itkPixel_VUS : itkPixel
{
public:
    itkPixel_VUS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for Vector Signed Short pixels.</summary>
public ref class itkPixel_VSS : itkPixel
{
public:
    itkPixel_VSS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for Vector Unsigned Long pixels.</summary>
public ref class itkPixel_VUL : itkPixel
{
public:
    itkPixel_VUL(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for Vector Signed Long pixels.</summary>
public ref class itkPixel_VSL : itkPixel
{
public:
    itkPixel_VSL(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for Vector Float pixels.</summary>
public ref class itkPixel_VF : itkPixel
{
public:
    itkPixel_VF(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for Vector Double pixels.</summary>
public ref class itkPixel_VD : itkPixel
{
public:
    itkPixel_VD(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Unsigned Char pixels.</summary>
public ref class itkPixel_CVUC : itkPixel
{
public:
    itkPixel_CVUC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Signed Char pixels.</summary>
public ref class itkPixel_CVSC : itkPixel
{
public:
    itkPixel_CVSC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedChar, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Unsigned Short pixels.</summary>
public ref class itkPixel_CVUS : itkPixel
{
public:
    itkPixel_CVUS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Signed Short pixels.</summary>
public ref class itkPixel_CVSS : itkPixel
{
public:
    itkPixel_CVSS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Unsigned Long pixels.</summary>
public ref class itkPixel_CVUL : itkPixel
{
public:
    itkPixel_CVUL(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedLong, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Signed Long pixels.</summary>
public ref class itkPixel_CVSL : itkPixel
{
public:
    itkPixel_CVSL(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedLong, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Float pixels.</summary>
public ref class itkPixel_CVF : itkPixel
{
public:
    itkPixel_CVF(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Double pixels.</summary>
public ref class itkPixel_CVD : itkPixel
{
public:
    itkPixel_CVD(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for CovariantVector Boolean pixels.</summary>
public ref class itkPixel_CVB : itkPixel
{
public:
    itkPixel_CVB(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Boolean, itkPixelArrayEnum::ArrayCovariantVector, (safe_cast<itkArray<Boolean>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VI UC pixels.</summary>
public ref class itkPixel_VIUC : itkPixel
{
public:
    itkPixel_VIUC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayVectorImage, (safe_cast<itkArray<System::Byte>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VI SS pixels.</summary>
public ref class itkPixel_VIUS : itkPixel
{
public:
    itkPixel_VIUS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayVectorImage, (safe_cast<itkArray<System::UInt16>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VI SS pixels.</summary>
public ref class itkPixel_VISS : itkPixel
{
public:
    itkPixel_VISS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayVectorImage, (safe_cast<itkArray<System::Int16>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VI F pixels.</summary>
public ref class itkPixel_VIF : itkPixel
{
public:
    itkPixel_VIF(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayVectorImage, (safe_cast<itkArray<System::Single>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VI D pixels.</summary>
public ref class itkPixel_VID : itkPixel
{
public:
    itkPixel_VID(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayVectorImage, (safe_cast<itkArray<System::Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VLV UC pixels.</summary>
public ref class itkPixel_VLVUC : itkPixel
{
public:
    itkPixel_VLVUC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayVariableLengthVector, (safe_cast<itkArray<System::Byte>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VLV SS pixels.</summary>
public ref class itkPixel_VLVUS : itkPixel
{
public:
    itkPixel_VLVUS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayVariableLengthVector, (safe_cast<itkArray<System::UInt16>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VLV SS pixels.</summary>
public ref class itkPixel_VLVSS : itkPixel
{
public:
    itkPixel_VLVSS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::SignedShort, itkPixelArrayEnum::ArrayVariableLengthVector, (safe_cast<itkArray<System::Int16>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VLV F pixels.</summary>
public ref class itkPixel_VLVF : itkPixel
{
public:
    itkPixel_VLVF(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Float, itkPixelArrayEnum::ArrayVariableLengthVector, (safe_cast<itkArray<System::Single>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for VLV D pixels.</summary>
public ref class itkPixel_VLVD : itkPixel
{
public:
    itkPixel_VLVD(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::Double, itkPixelArrayEnum::ArrayVariableLengthVector, (safe_cast<itkArray<System::Double>^>(value))->Length), value )
    { }
};

///<summary>This class is a managed wrapper for RGB UC pixels.</summary>
public ref class itkPixel_RGBUC : itkPixel
{
public:
    itkPixel_RGBUC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayRGB, 3), value )
    { }
};

///<summary>This class is a managed wrapper for RGB US pixels.</summary>
public ref class itkPixel_RGBUS : itkPixel
{
public:
    itkPixel_RGBUS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayRGB, 3), value )
    { }
};

///<summary>This class is a managed wrapper for RGB UC pixels.</summary>
public ref class itkPixel_RGBAUC : itkPixel
{
public:
    itkPixel_RGBAUC(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedChar, itkPixelArrayEnum::ArrayRGBA, 4), value )
    { }
};

///<summary>This class is a managed wrapper for RGB US pixels.</summary>
public ref class itkPixel_RGBAUS : itkPixel
{
public:
    itkPixel_RGBAUS(Object^ value) : itkPixel ( gcnew itkPixelType(itkPixelTypeEnum::UnsignedShort, itkPixelArrayEnum::ArrayRGBA, 4), value )
    { }
};

} // end namespace itk

#endif
