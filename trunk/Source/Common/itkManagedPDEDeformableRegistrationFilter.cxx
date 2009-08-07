/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedPDEDeformableRegistrationFilter.cxx
  Language:  C++/CLI
  Author:    Dan Mueller
  Date:      $Date$
  Revision:  $Revision$

  Portions of this code are covered under the ITK and VTK copyright.
  See http://www.itk.org/HTML/Copyright.htm for details.
  See http://www.vtk.org/copyright.php for details.

  Copyright (c) 2007-2009 Daniel Mueller

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

#ifndef __itkManagedPDEDeformableRegistrationFilter_cxx
#define __itkManagedPDEDeformableRegistrationFilter_cxx

// Include some ManagedITK files
#include "itkFiniteDifferenceImageFilter.cxx"

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
///This class is a managed replacement for itk::PDEDeformableRegistrationFilter.
///</summary>
///<remarks>
///Deformably register two images using a PDE algorithm.
///</remarks>
public ref class itkPDEDeformableRegistrationFilter abstract : itkFiniteDifferenceImageFilter
{

public:
    ///<summary>Default constructor.</summary>
    ///<param name="name">A string representing the name of the ProcessObject.</param>
    itkPDEDeformableRegistrationFilter( String^ name ) : itkFiniteDifferenceImageFilter( name ) { }

    ///<summary>
    ///Set the fixed image.
    ///</summary>
    virtual void SetFixedImage(itkImageBase^ image) = 0;

    ///<summary>
    ///Get the fixed image.
    ///</summary>
    virtual void GetFixedImage(itkImageBase^ image) = 0;

    ///<summary>
    ///Set the moving image.
    ///</summary>
    virtual void SetMovingImage(itkImageBase^ image) = 0;

    ///<summary>
    ///Get the moving image.
    ///</summary>
    virtual void GetMovingImage(itkImageBase^ image) = 0;

    ///<summary>
    ///Set the initial deformation field.
    ///</summary>
    virtual void SetInitialDeformationField( System::IntPtr ptr ) = 0;

    ///<summary>
    ///Get the initial deformation field.
    ///</summary>
    virtual IntPtr GetInitialDeformationField( ) = 0;

    ///<summary>
    ///Get/set whether the deformation field is smoothed (regularized). Smoothing the deformation yields a solution elastic in nature. If SmoothDeformationField is on, then the deformation field is smoothed with a Gaussian whose standard deviations are specified with SetStandardDeviations().
    ///</summary>
    virtual property bool SmoothDeformationField { bool get()=0; void set( bool value )=0; }

    ///<summary>
    ///Get/set the Gaussian smoothing standard deviations for the deformation field. The values are set with respect to pixel coordinates.
    ///</summary>
    virtual property double[] StandardDeviations { double[] get()=0; void set( double[] value )=0; }
    
    ///<summary>
    ///Get/set hether the update field is smoothed (regularized). Smoothing the update field yields a solution viscous in nature. If SmoothUpdateField is on, then the update field is smoothed with a Gaussian whose standard deviations are specified with SetUpdateFieldStandardDeviations().
    ///</summary>
    virtual property bool SmoothUpdateField { bool get()=0; void set( bool value )=0; }

    ///<summary>
    ///Get/set the Gaussian smoothing standard deviations for the update field. The values are set with respect to pixel coordinates.
    ///</summary>
    virtual property double[] UpdateFieldStandardDeviations { double[] get()=0; void set( double[] value )=0; }

    ///<summary>
    ///Get/set the desired maximum error of the Guassian kernel approximate.
    ///</summary>
    virtual property double MaximumError { double get()=0; void set( double value )=0; }

    ///<summary>
    ///Get/set the desired limits of the Gaussian kernel width.
    ///</summary>
    virtual property unsigned int MaximumKernelWidth { unsigned int get()=0; void set( unsigned int value )=0; }

    ///<summary>
    ///Stop the registration after the current iteration.
    ///</summary>
    virtual void StopRegistration( ) = 0;

}; // end ref class

} // end namespace itk

#endif