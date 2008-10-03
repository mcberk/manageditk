/*=============================================================================
  
  NOTE: THIS FILE IS A HANDMADE WRAPPER FOR THE ManagedITK PROJECT.

  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkManagedSegmentationLevelSetImageFilter.cxx
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

#ifndef __itkManagedSegmentationLevelSetImageFilter_cxx
#define __itkManagedSegmentationLevelSetImageFilter_cxx

// Include some ManagedITK files
#include "itkManagedPixel.cxx"
#include "itkManagedFiniteDifferenceImageFilter.cxx"

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
///This class is a managed replacement for itk::SegmentationLevelSetImageFilter.
///</summary>
///<remarks>
///This object defines the framework for a class of segmentation filters which
///use level set methods.  These filters work by constructing a "feature image"
///onto which the evolving level set locks as it moves.  In the feature image,
///values that are close to zero are associated with object boundaries.  An
///original (or preprocessed) image is given to the filter as the feature image
///and a seed for the level set is given as the input of the filter.  The seed is
///converted into a level set embedding which propagates according to the features
///calculated from the original image.
///</remarks>
public ref class itkSegmentationLevelSetImageFilter  abstract : itkFiniteDifferenceImageFilter
{

protected:
	///<summary>Protected constructor.</summary>
    ///<param name="name">A string representing the name of the ProcessObject.</param>
	itkSegmentationLevelSetImageFilter( String^ name ) : itkFiniteDifferenceImageFilter( name )
	{ }

public:
    ///<summary>
    ///Turn On/Off the flag which determines whether Positive or Negative speed
    ///terms will cause surface expansion. If set to TRUE then negative speed
    ///terms will cause the surface to expand and positive speed terms will cause
    ///the surface to contract. If set to FALSE (default) then positive speed terms
    ///will cause the surface to expand and negative speed terms will cause the
    ///surface to contract. This method can be safely used to reverse the
    ///expansion/contraction as appropriate to a particular application or data set/
    ///</summary>
    virtual property bool ReverseExpansionDirection { bool get()=0; void set( bool value )=0; }

    ///<summary>
    ///Turn On/Off automatic generation of Speed and Advection terms when Update
    ///is called. If set to Off, the Speed and Advection images must be set
    ///explicitly using SetSpeedImage, SetAdvectionImage OR the methods
    ///GenerateSpeedImage() and GenerateAdvectionImage() should be called prior
    ///to updating the filter.
    ///</summary>
    virtual property bool AutoGenerateSpeedAdvection { bool get()=0; void set( bool value )=0; }

    ///<summary>
    ///Set the combined scaling of the propagation and advection speed terms.
    ///You should use either this -or- Get/SetPropagationScaling and
    ///Get/SetAdvectionScaling (if appropriate).  See subclasses for details
    ///on when and whether to set these parameters.
    ///</summary>
    virtual property itkPixel^ FeatureScaling { void set( itkPixel^ value )=0; }

    ///<summary>
    ///Get/set the scaling of the propagation speed.
    ///Setting the FeatureScaling parameter overrides any previous values set for PropagationScaling.
    ///</summary>
    virtual property itkPixel^ PropagationScaling { itkPixel^ get()=0; void set( itkPixel^ value )=0; }
    
    ///<summary>
    ///Get/set the scaling of the advection field.
    ///Setting the FeatureScaling parameter will override any existing value for AdvectionScaling.
    ///</summary>
    virtual property itkPixel^ AdvectionScaling { itkPixel^ get()=0; void set( itkPixel^ value )=0; }
    
    ///<summary>
    ///Get/set the scaling of the curvature. 
    ///Use this parameter to increase the influence of curvature on the movement of the surface.
    ///Higher values relative to Advection and Propagation values will give smoother surfaces.
    ///</summary>
    virtual property itkPixel^ CurvatureScaling { itkPixel^ get()=0; void set( itkPixel^ value )=0; }
    
    ///<summary>
    ///No documentation provided in Code/Algorithms/itkSegmentationLevelSetImageFilter.h
    ///</summary>
    virtual property bool UseMinimalCurvature { bool get()=0; void set( bool value )=0; }
    
    ///<summary>
    ///Get/set the maximum constraint for the curvature term factor in the time step calculation.
    ///Changing this value from the default is not recommended or necessary but could be used 
    ///to speed up the surface evolution at the risk of creating an unstable solution.
    ///</summary>
    virtual property double MaximumCurvatureTimeStep { double get()=0; void set( double value )=0; }
    
    ///<summary>
    ///Get/set the maximum constraint for the scalar/vector term factor of the time step calculation.
    ///Changing this value from the default is not recommended or necessary but could be used to 
    ///speed up the surface evolution at the risk of creating an unstable solution.
    ///</summary>
    virtual property double MaximumPropagationTimeStep { double get()=0; void set( double value )=0; }
    
    // TODO:
    // property XXXX SegmentationFunction { XXXX get(); void set( XXXX value ); }

    ///<summary>Set the initial level set model. Equivalent to calling SetInput(..).</summary>
    virtual void SetInitialImage( itkDataObject^ initialImage )=0;

    ///<summary>
    ///Set the feature image to be used for speed function of the level set equation.
    ///Equivalent to calling SetInput(1, ..).
    ///</summary>
    virtual void SetFeatureImage( itkDataObject^ featureImage )=0;
    
    ///<summary>
    ///Get the feature image to be used for speed function of the level set equation.
    ///Equivalent to calling GetInput(1, ..).
    ///</summary>
    virtual void GetFeatureImage( itkDataObject^ featureImage )=0;

    ///<summary>
    ///This function is for advanced applications.
    ///Set the image sampled as the speed term of this segmentation method.
    ///In general, the speed image is generated automatically by a subclass of this filter.
    ///</summary>
    virtual void SetSpeedImage ( itkDataObject^ speedImage )=0;

    ///<summary>Return the image sampled as the speed term of the segmentation algorithm.</summary>
    virtual void GetSpeedImage ( itkDataObject^ speedImage )=0;
    
    ///<summary>
    ///This function is for advanced applications.
    ///Set the image sampled as the advection term of this segmentation method.
    ///In general, the advection image is generated automatically by a subclass of this filter.
    ///</summary>
    virtual void SetAdvectionImage ( itkDataObject^ advectionImage )=0;

    ///<summary>Return the image sampled as the advection term of the segmentation algorithm.</summary>
    virtual void GetAdvectionImage ( itkDataObject^ advectionImage )=0;
    
    ///<summary>
    ///Allocate and calculate the speed term image in the SegmentationFunction object.
    ///This method is called automatically on filter execution unless 
    ///AutoGenerateSpeedAdvection is set to Off.
    ///</summary>
    virtual void GenerateSpeedImage ( )=0;
    
    ///<summary>
    ///Allocate and calculate the advection term image in the SegmentationFunction object.
    ///This method is called automatically on filter execution unless 
    ///AutoGenerateSpeedAdvection is set to Off.
    ///</summary>
    virtual void GenerateAdvectionImage ( )=0;

}; // end ref class

} // end namespace itk

#endif