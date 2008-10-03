/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkSpeedFunctionToPathFilter.txx,v $
  Language:  C++
  Date:      $Date: 2007-09-06 08:19:55 +0200 (Thu, 06 Sep 2007) $
  Version:   $Revision: 5 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __itkSpeedFunctionToPathFilter_txx
#define __itkSpeedFunctionToPathFilter_txx

#include "vnl/vnl_math.h"
#include "itkSpeedFunctionToPathFilter.h"
#include "itkFastMarchingUpwindGradientImageFilter.h"
#include "itkImageFileWriter.h"

namespace itk
{

/**
 *
 */
template <class TInputImage, class TOutputPath>
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::SpeedFunctionToPathFilter()
{
  m_CurrentArrivalFunction = NULL;
}


/**
 *
 */
template <class TInputImage, class TOutputPath>
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::~SpeedFunctionToPathFilter()
{
}


/**
 *
 */
template<class TInputImage, class TOutputPath>
unsigned int
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::GetNumberOfPathsToExtract() const
{
  return m_Info.size();
}


/**
 *
 */
template<class TInputImage, class TOutputPath>
const typename SpeedFunctionToPathFilter<TInputImage,TOutputPath>::PointType &
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::GetNextEndPoint()
{
  return m_Info[m_CurrentOutput].GetEndPoint();
}


/**
 *
 */
template<class TInputImage, class TOutputPath>
typename SpeedFunctionToPathFilter<TInputImage,TOutputPath>::InputImageType *
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::ComputeArrivalFunction()
{
  // Get the speed image
  InputImagePointer speed = 
    const_cast< InputImageType * >( this->GetInput() );

  // TODO: Question: Can the speed image be masked by the previous arrival
  //       function to prevent re-processing the spatial positions?
    
  // Set the fast marching method for computing the arrival function
  typedef FastMarchingUpwindGradientImageFilter< TInputImage, TInputImage >
    FastMarchingType;
  typedef FastMarchingType::NodeContainer NodeContainer;
  typedef FastMarchingType::NodeType NodeType;
  FastMarchingType::Pointer marching = FastMarchingType::New();
  marching->SetInput( speed );
  marching->SetGenerateGradientImage( false );
  marching->SetTargetOffset( 2.0*m_TerminationValue );
  marching->SetTargetReachedModeToAllTargets( );

  // Add next and previous wavefront sources as target points to
  // limit the wavefront propagation to just the required zones
  IndexType indexTargetPrevious;
  IndexType indexTargetNext;
  speed->TransformPhysicalPointToIndex
    ( m_Info[m_CurrentOutput].PeekPreviousWavefront(), indexTargetPrevious );
  speed->TransformPhysicalPointToIndex
    ( m_Info[m_CurrentOutput].PeekNextWavefront(), indexTargetNext );
  NodeType nodeTargetPrevious;
  NodeType nodeTargetNext;
  nodeTargetPrevious.SetValue( 0.0 );
  nodeTargetNext.SetValue( 0.0 );
  nodeTargetPrevious.SetIndex( indexTargetPrevious );
  nodeTargetNext.SetIndex( indexTargetNext );
  NodeContainer::Pointer targets = NodeContainer::New();
  targets->Initialize();
  targets->InsertElement( 0, nodeTargetPrevious );
  targets->InsertElement( 1, nodeTargetNext );
  marching->SetTargetPoints( targets );

  // Get the next wavefront source point and add as trial point
  IndexType indexTrial;
  speed->TransformPhysicalPointToIndex
    ( m_Info[m_CurrentOutput].GetCurrentWavefrontAndAdvance(), indexTrial );
  NodeType nodeTrial;
  nodeTrial.SetValue( 0.0 );
  nodeTrial.SetIndex( indexTrial );
  NodeContainer::Pointer trial = NodeContainer::New();
  trial->Initialize();
  trial->InsertElement( 0, nodeTrial );
  marching->SetTrialPoints( trial );
  
  // Update the method and set the arrival function
  marching->UpdateLargestPossibleRegion( );
  m_CurrentArrivalFunction = marching->GetOutput( );
  //// START: DEBUG: TODO: =============================================
  //std::cout << "Trial: " << indexTrial << std::endl;
  //std::cout << "TargetPrevious: " << indexTargetPrevious << std::endl;
  //std::cout << "TargetNext: " << indexTargetNext << std::endl;
  //typedef ImageFileWriter< TInputImage > WriterType;
  //WriterType::Pointer writer = WriterType::New();
  //writer->SetFileName( "C:/Temp/MinimalPath-Arrival.mhd" );
  //writer->SetInput( marching->GetOutput( ) );
  //writer->Update();
  //// END: DEBUG: TODO: ===============================================
  m_CurrentArrivalFunction->DisconnectPipeline( );
  return m_CurrentArrivalFunction;
}


/**
 *
 */
template <class TInputImage, class TOutputPath>
void
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::GenerateData( void )
{
  // Get the speed function
  InputImagePointer speed = 
    const_cast< InputImageType * >( this->GetInput() );
  if ( speed.IsNull() )
    {
    itkExceptionMacro( "Speed function image must be provided" );
    }

  // Ensure the user has added at least one path info object
  if ( m_Info.size() == 0 )
    {
    itkExceptionMacro( "No PathInfo objects: at least one must be added." );
    }

  // Extract the path
  Superclass::GenerateData( );
}


/**
 *
 */
template <class TInputImage, class TOutputPath>
void
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::Execute( const Object * object, const EventObject & event )
{
  // Cast object to optmizer
  OptimizerType::Pointer optimizer = (OptimizerType*)
      dynamic_cast< const OptimizerType* >( object );
  if ( optimizer.IsNull() ) return;

  // Get current position and value
  OptimizerType::ParametersType currentParameters = optimizer->GetCurrentPosition();
  unsigned int lenParameters = currentParameters.GetSize();
  if ( lenParameters != InputImageDimension ) return;
  OptimizerType::MeasureType currentValue = optimizer->GetValue( currentParameters );

  // Convert parameters to point
  bool valid = false;
  unsigned int numparams = optimizer->GetCurrentPosition().GetSize();
  PointType point; point.Fill( 0.0 );
  for ( unsigned int i=0; i<numparams; i++ )
    {
    point[i] = optimizer->GetCurrentPosition()[i];
    valid = true;
    }
  if ( !valid ) return;

  // DEBUG:
  //unsigned int test = (int)currentValue;
  //if (test % 10 == 0) std::cout << "CurrentPosition: " << point << std::endl;	

  // Check if we have reached the termination value
  if ( currentValue < m_TerminationValue &&
       m_Info[m_CurrentOutput].HasNextWavefront() )
    {
    // We have terminated the current path segment, but there are more wavefronts
    // to propagate

    // Update the arrival function and re-initialise the cost function
    m_CostFunction->SetImage( this->ComputeArrivalFunction( ) );
    m_CostFunction->Initialize( );
    }
  else if ( currentValue >= m_TerminationValue )
    {
    // Convert point to continuous index
    InputImagePointer input = const_cast<InputImageType*>( this->GetInput() );
    ContinuousIndexType cindex;
    input->TransformPhysicalPointToContinuousIndex( point, cindex );

    // Add point as vertex in path
    OutputPathType::Pointer output = this->GetOutput( m_CurrentOutput );
    output->AddVertex( cindex );

	// DEBUG:
    //if (test % 10 == 0) std::cout << "Vertex: " << cindex << std::endl;	
    }
}


/**
 *
 */
template<class TInputImage, class TOutputPath>
void 
SpeedFunctionToPathFilter<TInputImage,TOutputPath>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
}


} // end namespace itk

#endif
