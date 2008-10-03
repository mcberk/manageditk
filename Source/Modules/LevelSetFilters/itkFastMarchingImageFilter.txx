/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkFastMarchingImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkFastMarchingImageFilter_txx
#define _itkFastMarchingImageFilter_txx

#include "itkBinaryBallStructuringElement.h"
#include "itkBinaryThresholdImageFilter.h"
#include "itkBinaryErodeImageFilter.h"
#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkImageRegionIterator.h"
#include "itkNumericTraits.h"
#include "vnl/vnl_math.h"
#include <algorithm>
#include "itkFastMarchingImageFilter.h"

namespace itk
{

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::FastMarchingImageFilter()
  : m_TrialHeap( )
{

  this->ProcessObject::SetNumberOfRequiredInputs(0);

  OutputSizeType outputSize;
  outputSize.Fill( 16 );
  typename LevelSetImageType::IndexType outputIndex;
  outputIndex.Fill( 0 );

  m_OutputRegion.SetSize( outputSize );
  m_OutputRegion.SetIndex( outputIndex ); 

  m_OutputOrigin.Fill( 0.0 );
  m_OutputSpacing.Fill( 1.0 );
  m_OverrideOutputInformation = false;

  m_AlivePoints = NULL;
  m_TrialPoints = NULL;
  m_ProcessedPoints = NULL;

  m_SpeedConstant = 1.0;
  m_InverseSpeed = -1.0;
  m_ManualLabelImage = false;
  m_LabelImage = LabelImageType::New();

  typedef typename LevelSetImageType::PixelType PixelType;
  m_LargeValue    = static_cast<PixelType>( NumericTraits<PixelType>::max() / 2.0 );
  m_StoppingValue = static_cast<double>( m_LargeValue );
  m_CollectPoints = false;

  m_NormalizationFactor = 1.0;
}

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os,indent);
  os << indent << "Alive points: " << m_AlivePoints.GetPointer() << std::endl;
  os << indent << "Trial points: " << m_TrialPoints.GetPointer() << std::endl;
  os << indent << "Speed constant: " << m_SpeedConstant << std::endl;
  os << indent << "Stopping value: " << m_StoppingValue << std::endl;
  os << indent << "Large Value: "
     << static_cast<typename NumericTraits<PixelType>::PrintType>(m_LargeValue)
     << std::endl;
  os << indent << "Normalization Factor: " << m_NormalizationFactor << std::endl;
  os << indent << "Collect points: " << m_CollectPoints << std::endl;
  os << indent << "OverrideOutputInformation: ";
  os << m_OverrideOutputInformation << std::endl;
  os << indent << "OutputRegion: " << m_OutputRegion << std::endl;
  os << indent << "OutputSpacing: " << m_OutputSpacing << std::endl;
  os << indent << "OutputOrigin:  " << m_OutputOrigin << std::endl;
}

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::SetAlivePointsFromImage( LabelImagePointer image )
{
  // Setup
  typedef ImageRegionConstIteratorWithIndex< LabelImageType > IteratorType;
  NodeContainer::Pointer nodes = NodeContainer::New();
  nodes->Initialize();
  IteratorType it( image, image->GetLargestPossibleRegion() );

  // Walk image
  unsigned int count = 0;
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    {
    if (it.Get() > NumericTraits< LabelPixelType >::Zero)
      {
      NodeType node;
      node.SetIndex( it.GetIndex() );
      nodes->InsertElement( count, node );
      count++;
      }
    }

  // Set nodes
  this->SetAlivePoints( nodes );
  this->Modified();
}

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::SetTrialPointsFromImage( LabelImagePointer image )
{
  // Setup
  typedef ImageRegionConstIteratorWithIndex< LabelImageType > IteratorType;
  NodeContainer::Pointer nodes = NodeContainer::New();
  nodes->Initialize();
  IteratorType it( image, image->GetLargestPossibleRegion() );

  // Walk image
  unsigned int count = 0;
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    {
    if (it.Get() > NumericTraits< LabelPixelType >::Zero)
      {
      NodeType node;
      node.SetIndex( it.GetIndex() );
      nodes->InsertElement( count, node );
      count++;
      }
    }

  // Set nodes
  this->SetTrialPoints( nodes );
  this->Modified();
}

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::SetLabelImage( LabelImagePointer image )
{
  m_ManualLabelImage = true;
  m_LabelImage = image;
  this->Modified();
}

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::SetLabelImageFromContour( LabelImagePointer image )
{
  if ( image.IsNull() )
    {
    return;
    }

  // Record that the user has set the label image
  m_ManualLabelImage = true;

  // allocate memory for the LabelTypeImage
  m_LabelImage->CopyInformation( image );
  m_LabelImage->SetBufferedRegion( image->GetBufferedRegion() );
  m_LabelImage->Allocate();

  // threshold the given image
  typedef BinaryThresholdImageFilter< LabelImageType, LabelImageType >
    ThresholdFilterType;
  ThresholdFilterType::Pointer filterThreshold = ThresholdFilterType::New();
  filterThreshold->SetInput( image );
  filterThreshold->SetLowerThreshold( NumericTraits<LabelPixelType>::One );
  filterThreshold->SetUpperThreshold( NumericTraits<LabelPixelType>::max() );
  
  // setup the structuring element
  typedef BinaryBallStructuringElement< LabelPixelType, TLevelSet::ImageDimension >
    KernelType;
  KernelType kernel;
  kernel.SetRadius( 1 );
  kernel.CreateStructuringElement( );

  // erode the thresholded image
  typedef BinaryErodeImageFilter< LabelImageType, LabelImageType, KernelType >
    ErodeFilterType;
  ErodeFilterType::Pointer filterErode = ErodeFilterType::New();
  filterErode->SetInput( filterThreshold->GetOutput() );
  filterErode->SetKernel( kernel );
  filterErode->Update( );

  // walk the given and eroded images to set label values
  typedef ImageRegionIterator< LabelImageType > LabelIteratorType;
  LabelIteratorType itLabel( m_LabelImage, m_LabelImage->GetLargestPossibleRegion() );
  typedef ImageRegionConstIteratorWithIndex< LabelImageType > IteratorType;
  IteratorType itImage( image, image->GetLargestPossibleRegion() );
  IteratorType itErode( filterErode->GetOutput(),
                        filterErode->GetOutput()->GetLargestPossibleRegion() );
  for (itLabel.GoToBegin(), itImage.GoToBegin(), itErode.GoToBegin();
      !itLabel.IsAtEnd();
      ++itLabel, ++itImage, ++itErode)
    {
    if (itErode.Get() > NumericTraits< LabelPixelType >::Zero)
      {
      // an alive point
      itLabel.Set( AlivePoint );
      }
    else if (itImage.Get() > NumericTraits< LabelPixelType >::Zero)
      {
      // a trial point
      itLabel.Set( TrialPoint );
      }
    else
      {
      // a far point
      itLabel.Set( FarPoint );
      }
    }

  this->Modified();
}

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::GenerateOutputInformation()
{

  // copy output information from input image
  Superclass::GenerateOutputInformation();

  // use user-specified output information
  if ( this->GetInput() == NULL || m_OverrideOutputInformation )
    {
    LevelSetPointer output = this->GetOutput();
    output->SetLargestPossibleRegion( m_OutputRegion );
    output->SetSpacing( m_OutputSpacing );
    output->SetOrigin( m_OutputOrigin );
    }
    
}


/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::EnlargeOutputRequestedRegion(
  DataObject *output )
{
  // enlarge the requested region of the output
  // to the whole data set
  TLevelSet * imgData;

  imgData = dynamic_cast<TLevelSet*>( output );
  if ( imgData )
    {
    imgData->SetRequestedRegionToLargestPossibleRegion();
    }
  else
    {
    // Pointer could not be cast to TLevelSet *
    itkWarningMacro(<< "itk::FastMarchingImageFilter" <<
                    "::EnlargeOutputRequestedRegion cannot cast "
                    << typeid(output).name() << " to "
                    << typeid(TLevelSet*).name() );    
    }

}



/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::Initialize( LevelSetImageType * output )
{

  // allocate memory for the output buffer
  output->SetBufferedRegion( output->GetRequestedRegion() );
  output->Allocate();

  // cache some buffered region information
  m_BufferedRegion = output->GetBufferedRegion();
  m_StartIndex = m_BufferedRegion.GetIndex();
  m_LastIndex = m_StartIndex + m_BufferedRegion.GetSize();
  typename LevelSetImageType::OffsetType offset;
  offset.Fill( 1 );
  m_LastIndex -= offset;
  
  // set all output value to infinity
  typedef ImageRegionIterator<LevelSetImageType>
    OutputIterator;
  
  OutputIterator outIt ( output, output->GetBufferedRegion() );

  PixelType outputPixel;
  outputPixel = m_LargeValue;
  
  for ( outIt.GoToBegin(); !outIt.IsAtEnd(); ++outIt )
    {
    outIt.Set( outputPixel );
    }
    
  // make sure the heap is empty
  while ( !m_TrialHeap.empty() )
    {
    m_TrialHeap.pop();
    }

  // check if we need to create the label image
  if (m_ManualLabelImage)
    {

    // walk the image and add trial points to heap and output
    typedef ImageRegionConstIteratorWithIndex< LabelImageType > IteratorType;
    IteratorType it( m_LabelImage, m_LabelImage->GetLargestPossibleRegion() );
    for (it.GoToBegin(); !it.IsAtEnd(); ++it)
      {
      if (it.Get() == static_cast< LabelPixelType >(TrialPoint))
        {
        AxisNodeType node;
        node.SetIndex( it.GetIndex() );
        m_TrialHeap.push( node );
		output->SetPixel( it.GetIndex(), 0.0F );
        }
	  else if (it.Get() == static_cast< LabelPixelType >(AlivePoint))
	    {
		output->SetPixel( it.GetIndex(), 0.0F );
	    }
      }

    // no more work, return
    return;
    }

  // only get this far if creating label image from points

  // allocate memory for the LabelTypeImage
  m_LabelImage->CopyInformation( output );
  m_LabelImage->SetBufferedRegion( output->GetBufferedRegion() );
  m_LabelImage->Allocate();

  // set all points type to FarPoint
  typedef ImageRegionIterator< LabelImageType > 
    LabelIterator;

  LabelIterator typeIt( m_LabelImage, m_LabelImage->GetBufferedRegion() );

  for ( typeIt.GoToBegin(); !typeIt.IsAtEnd(); ++typeIt )
    {
    typeIt.Set( FarPoint );
    }


  // process input alive points
  AxisNodeType node;
  if ( m_AlivePoints )
    {
    typename NodeContainer::ConstIterator pointsIter = m_AlivePoints->Begin();
    typename NodeContainer::ConstIterator pointsEnd = m_AlivePoints->End();

    for ( ; pointsIter != pointsEnd; ++pointsIter )
      {

      // get node from alive points container
      node = pointsIter.Value();

      // check if node index is within the output level set
      if ( !m_BufferedRegion.IsInside( node.GetIndex() ) ) 
        {
        continue;
        }

      // make this an alive point
      m_LabelImage->SetPixel( node.GetIndex(), AlivePoint );
      output->SetPixel( node.GetIndex(), node.GetValue() );

      }
    }

  // process the input trial points
  if ( m_TrialPoints )
    {
    typename NodeContainer::ConstIterator pointsIter = m_TrialPoints->Begin();
    typename NodeContainer::ConstIterator pointsEnd = m_TrialPoints->End();

    for ( ; pointsIter != pointsEnd; ++pointsIter )
      {

      // get node from trial points container
      node = pointsIter.Value();

      // check if node index is within the output level set
      if ( !m_BufferedRegion.IsInside( node.GetIndex() ) ) 
        {
        continue;
        }

      // make this a trial point
      m_LabelImage->SetPixel( node.GetIndex(), TrialPoint );

      outputPixel = node.GetValue();
      output->SetPixel( node.GetIndex(), outputPixel );

      m_TrialHeap.push( node );

      }
    }
      
}


/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::GenerateData()
{

  LevelSetPointer         output      = this->GetOutput();
  SpeedImageConstPointer  speedImage  = this->GetInput();

  this->Initialize( output );

  if ( m_CollectPoints )
    {
    m_ProcessedPoints = NodeContainer::New();
    }
  
  // process points on the heap
  AxisNodeType node;
  double currentValue;
  double oldProgress = 0;

  this->UpdateProgress( 0.0 ); // Send first progress event

  while ( !m_TrialHeap.empty() )
    {
    // get the node with the smallest value
    node = m_TrialHeap.top();
    m_TrialHeap.pop();

    // does this node contain the current value ?
    currentValue = (double) output->GetPixel( node.GetIndex() );

    if ( node.GetValue() != currentValue )
      {
      continue;
      } 

    // is this node already alive ?
    if ( m_LabelImage->GetPixel( node.GetIndex() ) != TrialPoint ) 
      {
      continue;
      }

    if ( currentValue > m_StoppingValue )
      {
      break;
      }

    if ( m_CollectPoints )
      {
      m_ProcessedPoints->InsertElement( m_ProcessedPoints->Size(), node );
      }
    
    // set this node as alive
    m_LabelImage->SetPixel( node.GetIndex(), AlivePoint );

    // update its neighbors
    this->UpdateNeighbors( node.GetIndex(), speedImage, output );


    // Send events every certain number of points.
    const double newProgress = currentValue / m_StoppingValue;
    if( newProgress - oldProgress > 0.01 )  // update every 1%
      {
      this->UpdateProgress( newProgress );
      oldProgress = newProgress;
      if( this->GetAbortGenerateData() )
        {
        this->InvokeEvent( AbortEvent() );
        this->ResetPipeline();
        ProcessAborted e(__FILE__,__LINE__);
        e.SetDescription("Process aborted.");
        e.SetLocation(ITK_LOCATION);
        throw e;
        }
      }

    }
  
}

/*
 *
 */
template <class TLevelSet, class TSpeedImage>
void
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::UpdateNeighbors(
  const IndexType& index,
  const SpeedImageType * speedImage,
  LevelSetImageType * output )
{
  IndexType neighIndex = index;

  for ( unsigned int j = 0; j < SetDimension; j++ )
    {
    // update left neighbor
    if( index[j] > m_StartIndex[j] )
      {
      neighIndex[j] = index[j] - 1;
      }
    if ( m_LabelImage->GetPixel( neighIndex ) != AlivePoint )
      {
      this->UpdateValue( neighIndex, speedImage, output );
      }

    // update right neighbor
    if ( index[j] < m_LastIndex[j] )
      {
      neighIndex[j] = index[j] + 1;
      }
    if ( m_LabelImage->GetPixel( neighIndex ) != AlivePoint )
      {
      this->UpdateValue( neighIndex, speedImage, output );
      }

    //reset neighIndex
    neighIndex[j] = index[j];
      
    }

}


/*
 *
 */
template <class TLevelSet, class TSpeedImage>
double
FastMarchingImageFilter<TLevelSet,TSpeedImage>
::UpdateValue(
  const IndexType& index,
  const SpeedImageType * speedImage,
  LevelSetImageType * output )
{

  IndexType neighIndex = index;
  typename TLevelSet::PixelType neighValue;
  PixelType outputPixel;
  AxisNodeType node;
  
  for ( unsigned int j = 0; j < SetDimension; j++ )
    {
    node.SetValue( m_LargeValue );

    // find smallest valued neighbor in this dimension
    for( int s = -1; s < 2; s = s + 2 )
      {
      neighIndex[j] = index[j] + s;

      if( neighIndex[j] > m_LastIndex[j] || 
          neighIndex[j] < m_StartIndex[j] )
        {
        continue;
        }

      if ( m_LabelImage->GetPixel( neighIndex ) == AlivePoint )
        {
        outputPixel = output->GetPixel( neighIndex );
        neighValue = outputPixel ;

        if( node.GetValue() > neighValue )
          {
          node.SetValue( neighValue );
          node.SetIndex( neighIndex );
          }
        }

      }

    // put the minimum neighbor onto the heap
    m_NodesUsed[j] = node;
    m_NodesUsed[j].SetAxis(j);
    
    // reset neighIndex
    neighIndex[j] = index[j];
    }

  // sort the local list
  std::sort( m_NodesUsed, m_NodesUsed + SetDimension );

  // solve quadratic equation
  double aa, bb, cc;
  double solution = m_LargeValue;
  
  aa = 0.0;
  bb = 0.0;
  if ( speedImage )
    {
    typedef typename SpeedImageType::PixelType SpeedPixelType;
    cc = (double) speedImage->GetPixel( index ) / m_NormalizationFactor;
    cc = -1.0 * vnl_math_sqr( 1.0 / cc );
    }
  else 
    {
    cc = m_InverseSpeed;
    }

  OutputSpacingType spacing = this->GetOutput()->GetSpacing();

  double discrim;

  for ( unsigned int j = 0; j < SetDimension; j++ )
    {
    node = m_NodesUsed[j];

    if ( solution >= node.GetValue() )
      {
      const int axis = node.GetAxis();
      const double spaceFactor = vnl_math_sqr( 1.0 / spacing[axis] );
      const double value = double(node.GetValue());
      aa += spaceFactor;
      bb += value * spaceFactor;
      cc += vnl_math_sqr( value ) * spaceFactor;

      discrim = vnl_math_sqr( bb ) - aa * cc;
      if ( discrim < 0.0 )
        {
        // Discriminant of quadratic eqn. is negative
        ExceptionObject err(__FILE__, __LINE__);
        err.SetLocation( ITK_LOCATION );
        err.SetDescription( "Discriminant of quadratic equation is negative" );
        throw err;
        }
    
      solution = ( vcl_sqrt( discrim ) + bb ) / aa;
      }
    else
      {
      break;
      }
    }

  if ( solution < m_LargeValue )
    {
    // write solution to m_OutputLevelSet
    outputPixel = static_cast<PixelType>( solution );
    output->SetPixel( index, outputPixel );

    // insert point into trial heap
    m_LabelImage->SetPixel( index, TrialPoint );
    node.SetValue( static_cast<PixelType>( solution ) );
    node.SetIndex( index );
    m_TrialHeap.push( node );
    }

  return solution;

}

} // namespace itk


#endif
