/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkGenerateMaskImageFilter.txx,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkGenerateMaskImageFilter_txx
#define __itkGenerateMaskImageFilter_txx

#include "vnl/vnl_math.h"
#include "itkNumericTraits.h"
#include "itkProgressAccumulator.h"
#include "itkGenerateMaskImageFilter.h"

namespace itk
{

/** Constructor */
template <class TOutputImage>
GenerateMaskImageFilter<TOutputImage>
::GenerateMaskImageFilter()
{
  m_Size.Fill( 0 );

  for (unsigned int i = 0; i < OutputImageDimension; i++)
    {
    m_Spacing[i] = 0.0;
    m_Origin[i] = 0.0;
    }

  m_InsideValue = NumericTraits<typename OutputPixelType>::max();
  m_OutsideValue = NumericTraits<typename OutputPixelType>::Zero;
}

/** Destructor */
template <class TOutputImage>
GenerateMaskImageFilter<TOutputImage>
::~GenerateMaskImageFilter()
{
}
  
/** SetSpacing */
template <class TOutputImage>
void 
GenerateMaskImageFilter<TOutputImage>
::SetSpacing(const SpacingType& spacing )
{
  unsigned int i; 
  for (i=0; i<TOutputImage::ImageDimension; i++)
    {
    if ( (double)spacing[i] != m_Spacing[i] )
      {
      break;
      }
    } 
  if ( i < TOutputImage::ImageDimension ) 
    { 
    for (i=0; i<TOutputImage::ImageDimension; i++)
      {
      m_Spacing[i] = spacing[i];
      }
    this->Modified();
    }
}

/** SetSpacing */
template <class TOutputImage>
void 
GenerateMaskImageFilter<TOutputImage>
::SetSpacing(const double* spacing)
{
  unsigned int i; 
  for (i=0; i<OutputImageDimension; i++)
    {
    if ( spacing[i] != m_Spacing[i] )
      {
      break;
      }
    } 
  if ( i < OutputImageDimension ) 
    { 
    for (i=0; i<OutputImageDimension; i++)
      {
      m_Spacing[i] = spacing[i];
      }
    }
}

/** SetSpacing */
template <class TOutputImage>
void 
GenerateMaskImageFilter<TOutputImage>
::SetSpacing(const float* spacing)
{
  unsigned int i; 
  for (i=0; i<OutputImageDimension; i++)
    {
    if ( (double)spacing[i] != m_Spacing[i] )
      {
      break;
      }
    } 
  if ( i < OutputImageDimension ) 
    { 
    for (i=0; i<OutputImageDimension; i++)
      {
      m_Spacing[i] = spacing[i];
      }
    }
}

/** GetSpacing */
template <class TOutputImage>
const double * 
GenerateMaskImageFilter<TOutputImage>
::GetSpacing() const
{
  return m_Spacing;
}

/** SetOrigin */
template <class TOutputImage>
void 
GenerateMaskImageFilter<TOutputImage>
::SetOrigin(const PointType& origin)
{
  unsigned int i; 
  for (i=0; i<TOutputImage::ImageDimension; i++)
    {
    if ( (double)origin[i] != m_Origin[i] )
      {
      break;
      }
    } 
  if ( i < TOutputImage::ImageDimension ) 
    { 
    for (i=0; i<TOutputImage::ImageDimension; i++)
      {
      m_Origin[i] = origin[i];
      }
    this->Modified();
    }
}

/** SetOrigin */
template <class TOutputImage>
void 
GenerateMaskImageFilter<TOutputImage>
::SetOrigin(const double* origin)
{
  unsigned int i; 
  for (i=0; i<OutputImageDimension; i++)
    {
    if ( origin[i] != m_Origin[i] )
      {
      break;
      }
    } 
  if ( i < OutputImageDimension ) 
    { 
    for (i=0; i<OutputImageDimension; i++)
      {
      m_Origin[i] = origin[i];
      }
    this->Modified();
    }
}

/** SetOrigin */
template <class TOutputImage>
void 
GenerateMaskImageFilter<TOutputImage>
::SetOrigin(const float* origin)
{
  unsigned int i; 
  for (i=0; i<OutputImageDimension; i++)
    {
    if ( (double)origin[i] != m_Origin[i] )
      {
      break;
      }
    } 
  if ( i < OutputImageDimension ) 
    { 
    for (i=0; i<OutputImageDimension; i++)
      {
      m_Origin[i] = origin[i];
      }
    this->Modified();
    }
}

/** GetOrigin */
template <class TOutputImage>
const double * 
GenerateMaskImageFilter<TOutputImage>
::GetOrigin() const
{
  return m_Origin;
}

/** AddEllipse */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::AddEllipse(typename PointType center, float radius)
{
  EllipseListItem<typename PointType> item( center, radius );
  m_EllipseList.push_back( item );
}

/** AddRegion */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::AddRegion(typename RegionType region)
{
  m_RegionList.push_back( region );
}

/** AddPoint */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::AddPoint(typename PointType point)
{
  m_PointList.push_back( point );
}

/** AddImage */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::AddImage(typename MaskImageType* image)
{
  m_ImageList.push_back( image );
}

/** GenerateData */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::GenerateData(void)
{
  // Get the output pointer
  OutputImagePointer ptrOutputImage = this->GetOutput();

  // Generate the output image
  typename OutputImageType::RegionType region;
  typename OutputImageType::IndexType index;
  index.Fill( 0 );
  region.SetSize( this->GetSize() );
  region.SetIndex( index );
  ptrOutputImage->SetRegions( region );

  unsigned int i = 0;
  for ( i=0; i<OutputImageDimension; i++ )
    {
    ptrOutputImage->SetSpacing( this->GetSpacing() );
    }

  ptrOutputImage->SetOrigin( this->GetOrigin() );
  ptrOutputImage->Allocate();
  ptrOutputImage->FillBuffer( this->GetOutsideValue() );

  // Generate the data from the different types
  this->GenerateDataForEllipses( ptrOutputImage );
  this->GenerateDataForRegions ( ptrOutputImage );
  this->GenerateDataForPoints  ( ptrOutputImage );
  this->GenerateDataForImages  ( ptrOutputImage );
}

/** GenerateDataForEllipses */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::GenerateDataForEllipses( TOutputImage* ptrOutputImage )
{
  // Get the inside value
  ValueType insideValue = this->GetInsideValue();

  // Fill the ellipses by computing their bounding box and walking the region.
  // NOTE: The below code is adapted from InsightApplications-2.8.1/SNAP/..
  //	   ../Logic/Framework/SNAPImageData.cxx(250-304)
  for ( typename EllipseListIteratorType itEllipse = m_EllipseList.begin();
	    itEllipse != m_EllipseList.end();
	    itEllipse++ )
	{
	typename EllipseListItemType ellipse = *itEllipse;
 
    // Compute the extents of the ellipse
    PointType ptLower,ptUpper,ptCenter;
	ptCenter = ellipse.Center;

    // Compute the upper and lower bounds of the region that contains the bubble
    for ( unsigned int i=0; i<OutputImageDimension; i++ )
      {
      ptLower[i] = ptCenter[i] - ellipse.Radius;
      ptUpper[i] = ptCenter[i] + ellipse.Radius;
      }

    // Index locations corresponding to the extents of the ellipse
    typename OutputImageType::IndexType idxLower, idxUpper;     
    ptrOutputImage->TransformPhysicalPointToIndex(ptLower,idxLower);
    ptrOutputImage->TransformPhysicalPointToIndex(ptUpper,idxUpper);

    // Create a region
    typename OutputImageType::SizeType szEllipse;
    for ( unsigned int i=0; i<OutputImageDimension; i++ )
	  {
      szEllipse[i] = 1 + idxUpper[i] - idxLower[i];
	  }
    typename OutputImageType::RegionType regEllipse(idxLower,szEllipse);
    regEllipse.Crop(ptrOutputImage->GetLargestPossibleRegion());

    // Create an iterator to fill the ellipse
    IteratorType itOut(ptrOutputImage, regEllipse);
    for ( itOut.GoToBegin(); !itOut.IsAtEnd(); ++itOut )
      {
      PointType pt;
      ptrOutputImage->TransformIndexToPhysicalPoint(itOut.GetIndex(),pt);
      
      if ( pt.EuclideanDistanceTo(ptCenter) <= ellipse.Radius )
        {
        itOut.Set( insideValue );
        }
      }

    } //end foreach ellipse
}

/** GenerateDataForRegions */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::GenerateDataForRegions( TOutputImage* ptrOutputImage )
{
  // Get the inside value
  ValueType insideValue = this->GetInsideValue();

  for ( typename RegionListIteratorType itRegion = m_RegionList.begin();
	    itRegion != m_RegionList.end();
	    itRegion++ )
	{
    // Crop the region by the largest possible region
    RegionType region = *itRegion;
    region.Crop( ptrOutputImage->GetLargestPossibleRegion() );

    // Create an iterator to walk the region
    IteratorType itOut(ptrOutputImage, region);
    for ( itOut.GoToBegin(); !itOut.IsAtEnd(); ++itOut )
      {
      itOut.Set( insideValue );
      }
    }
}

/** GenerateDataForPoints */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::GenerateDataForPoints( TOutputImage* ptrOutputImage )
{
  // Get the inside value
  ValueType insideValue = this->GetInsideValue();
  
  // Do for each point in the list
  for ( typename PointListIteratorType itPoint = m_PointList.begin();
	    itPoint != m_PointList.end();
	    itPoint++ )
	{
	typename PointType point = *itPoint;
	
	// Convert the point to an index
	typename IndexType index;
    if ( ptrOutputImage->TransformPhysicalPointToIndex(*itPoint, index) )
      {
      ptrOutputImage->SetPixel( index, insideValue );
      }
    }
}

/** GenerateDataForImages */
template <class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::GenerateDataForImages( TOutputImage* ptrOutputImage )
{
  // Get the inside and outside values
  ValueType insideValue = this->GetInsideValue();

  // Do for each image in the list
  for ( typename ImageListIteratorType itImage = m_ImageList.begin();
	    itImage != m_ImageList.end();
	    itImage++ )
	{
	typename MaskImageType* mask = *itImage;

    // Create an iterator to walk the region in the output and the mask
    RegionType region = ptrOutputImage->GetLargestPossibleRegion();
    IteratorType itOut(ptrOutputImage, region);
    MaskIteratorType itMask(mask, region);
    for ( itOut.GoToBegin(), itMask.GoToBegin();
         !itOut.IsAtEnd(); 
         ++itOut, ++itMask )
      {
      if (itMask.Get() > itk::NumericTraits< MaskPixelType >::Zero)
        itOut.Set( insideValue );
      }
    }
}

/** PrintSelf */
template<class TOutputImage>
void
GenerateMaskImageFilter<TOutputImage>
::PrintSelf(std::ostream& os, Indent indent) const
{
  Superclass::PrintSelf(os, indent);
  os << indent << "Size : " << m_Size << std::endl;
  os << indent << "Spacing : " << m_Spacing << std::endl;
  os << indent << "Origin : " << m_Origin << std::endl;
  os << indent << "Inside Value : " << m_InsideValue << std::endl;
  os << indent << "Outside Value : " << m_OutsideValue << std::endl;
}

} // end namespace itk

#endif
