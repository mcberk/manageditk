/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedArray.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date: 2008-06-15 19:38:31 +0200 (Sun, 15 Jun 2008) $
  Revision:  $Revision: 16 $

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

#ifndef __itkManagedArray_cxx
#define __itkManagedArray_cxx

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
///The base array class from with all ManagedITK arrays are derived.
///</summary>
///<remarks>
///This class is templated (generic) over the array data value type (TValueType).
///</remarks>
generic<typename TValueType> 
where TValueType : System::IComparable<TValueType>, System::IConvertible
public ref class itkArray
{

private:
    array<typename TValueType>^ m_Data;

public:
    ///<summary>Constructor taking the data values as a params array.</summary>
    ///<param name="data">The variable length data array. The dimension will be initialised as data.Length. The data is cloned.</param>
    itkArray ( ... array<typename TValueType>^ data )
    {
        this->m_Data = (array<typename TValueType>^)data->Clone();
    }

    ///<summary>Constructor taking the number of dimensions for the array.</summary>
    ///<remarks>The data values are initialised as zero.</remarks>
    ///<param name="dimension">The dimensionality of the array to initialise.</param>
    itkArray( unsigned int dimension )
    {
        this->m_Data = gcnew array<typename TValueType>(dimension);
    }

    ///<summary>Constructor taking another array.</summary>
    ///<param name="other">Another array to clone the data from.</param>
    itkArray ( itkArray<TValueType>^ other)
    {
        this->m_Data = (array<typename TValueType>^)other->Data->Clone();
    }

    ///<summary>Get/set the data values via the given index.</summary>
    property typename TValueType default[int]
    {
        typename TValueType get(int index) 
        { return this->m_Data[index]; }
        void set(int index, typename TValueType value) 
        { this->m_Data[index] = value; }
    }

    ///<summary>Get the underlying data array.</summary>
    property array<typename TValueType>^ Data
    {
        array<typename TValueType>^ get() { return this->m_Data; }
    }

    ///<summary>Get the number of dimensions or length of the data array.</summary>
    property unsigned int Dimension
    {
        unsigned int get() { return this->m_Data->Length; }
    }

    ///<summary>Get the number of dimensions or length of the data array.</summary>
    ///<remarks>This is another way to access Dimension.</remarks>
    property unsigned int Length
    {
        unsigned int get() { return this->Dimension; }
    }

    ///<summary>Assign the given value to each dimension in the array.</summary>
    ///<param name="value">The data value to assign to each element of the array.</param>
    void Fill(typename TValueType value)
    {
        for (unsigned int i = 0; i < this->Dimension; i++)
            this[i] = value;
    }

    ///<summary>
    ///Converts the array to a string representation in the following format:
    ///   Real types: "[0.00 1.00 2.00]"
    ///   Integer types: "[1 12 123]"
    ///</summary>
    ///<returns>A string representation of the array.</returns>
    virtual String^ ToString() override
    {
        Type^ type = TValueType::typeid;
        if ( type == Single::typeid || 
             type == Double::typeid ||
             type == Decimal::typeid )
        {
            // Force 2 decimal places for real types
            return this->ToString("000.00");
        }
        else
        {
            // Use the default conversion for all other types
            return this->ToString("");
        }
    }

    ///<summary>Converts the array to a string represenation using the given format.</summary>
    ///<param name="format">The number formatting string. Eg. "00.00", "#00.0", etc.</param>
    ///<returns>A string representation of the array using the given format.</returns>
    virtual String^ ToString(String^ format)
    {
        // Add starting bracket
        String^ result = "[";

        // Construct the array string
        for (unsigned int i = 0; i < this->Dimension; i++)
        {
            Type^ type = TValueType::typeid;
            if ( type == Byte::typeid )
                result += Convert::ToByte(this->Data[i]).ToString(format);
            else if ( type == SByte::typeid )
                result += Convert::ToSByte(this->Data[i]).ToString(format);
            else if ( type == Int16::typeid )
                result += Convert::ToInt16(this->Data[i]).ToString(format);
            else if ( type == UInt16::typeid )
                result += Convert::ToUInt16(this->Data[i]).ToString(format);
            else if ( type == Int32::typeid )
                result += Convert::ToInt32(this->Data[i]).ToString(format);
            else if ( type == UInt32::typeid )
                result += Convert::ToUInt32(this->Data[i]).ToString(format);
            else if ( type == Int64::typeid )
                result += Convert::ToInt64(this->Data[i]).ToString(format);
            else if ( type == UInt64::typeid )
                result += Convert::ToUInt64(this->Data[i]).ToString(format);
            else if ( type == Single::typeid )
                result += Convert::ToSingle(this->Data[i]).ToString(format);
            else if ( type == Double::typeid )
                result += Convert::ToDouble(this->Data[i]).ToString(format);
            else if ( type == Decimal::typeid )
                result += Convert::ToDecimal(this->Data[i]).ToString(format);
            else
                // Use default ToString and ignore format
                result += this->Data[i]->System::Object::ToString();

            // Add separator
            result += ", ";
        }

        // Trim the trailing separator chars
        result = result->TrimEnd(',', ' ');

        // Add trailing bracket
        result += "]";

        return result;
    }

    ///<summary>Serves as a hash function for a particular type.</summary>
    ///<returns>A hashcode computed from the Data array elements.</returns>
    virtual int GetHashCode() override
    {
        if (this->m_Data == nullptr)
        {
            return 0;
        }
        else if (this->m_Data->Length == 0)
        {
            return this->m_Data->GetHashCode();
        }
        else
        {
            int result = this->m_Data[0]->GetHashCode();
            for (unsigned int i = 1; i < (unsigned int)this->m_Data->Length; i++)
            {
              result = result ^ this->m_Data[i]->GetHashCode();
            }
            return result;
        }
    }

}; // end ref class

} // end namespace itk

#endif