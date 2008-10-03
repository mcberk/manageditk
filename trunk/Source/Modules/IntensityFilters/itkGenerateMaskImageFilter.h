/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkGenerateMaskImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkGenerateMaskImageFilter_h
#define __itkGenerateMaskImageFilter_h

#include "itkConceptChecking.h"
#include "itkImageSource.h"
#include "itkImageRegionIteratorWithIndex.h"

namespace itk
{
    
/** \struct EllipseListItem
 * Holds the information about an ellipse in a list.
 */
template <class TPoint>
struct EllipseListItem
{
public:
  typedef EllipseListItem Self;
  
  /** Constructor */
  EllipseListItem(TPoint center, float radius)
  {
	Center = center;
	Radius = radius;
  }

  /** Copy construtor */
  EllipseListItem(const Self& in)
  {
	this->Center = in.Center;
	this->Radius = in.Radius;
  }

  TPoint Center;
  float Radius;
};


/** \class GenerateMaskImageFilter
 * \brief Generates a mask output image.
 *
 *  The user can add various shapes which are then 
 *  converted into a mask.
 */
template <class TOutputImage>
class ITK_EXPORT GenerateMaskImageFilter :
    public ImageSource<TOutputImage>
{
public:

  /** ImageDimension constant */
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

  /** Standard class typedefs. */
  typedef GenerateMaskImageFilter Self;
  typedef ImageSource<TOutputImage> Superclass;
  typedef SmartPointer<Self>  Pointer;
  typedef SmartPointer<const Self>  ConstPointer;
  typedef TOutputImage  OutputImageType;
  typedef typename OutputImageType::SizeType    SizeType;
  typedef typename OutputImageType::PointType   PointType;
  typedef typename OutputImageType::IndexType   IndexType;
  typedef typename OutputImageType::RegionType  RegionType;
  typedef typename OutputImageType::PixelType   OutputPixelType;
  typedef typename OutputImageType::Pointer     OutputImagePointer;
  typedef typename OutputImageType::ValueType   ValueType;
  typedef typename OutputImageType::SpacingType SpacingType;
  typedef Vector<long, OutputImageDimension>    VectorType;
  typedef unsigned char MaskPixelType;
  typedef itk::Image< MaskPixelType, OutputImageDimension> MaskImageType;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(GenerateMaskImageFilter, ImageSource);

  /** Set/Get Size */
  itkSetMacro(Size, SizeType);
  itkGetMacro(Size, SizeType);

  /** Spacing (size of a pixel) of the output image. The
   * spacing is the geometric distance between image samples.
   * It is stored internally as double, but may be set from
   * float. \sa GetSpacing() */
  virtual void SetSpacing( const SpacingType& spacing);
  virtual void SetSpacing( const double* spacing);
  virtual void SetSpacing( const float* spacing);
  virtual const double* GetSpacing() const;

  /** The origin of the output image. The origin is the geometric
   * coordinates of the index (0,0,...,0).  It is stored internally
   * as double but may be set from float.
   * \sa GetOrigin() */
  virtual void SetOrigin( const PointType& origin);
  virtual void SetOrigin( const double* origin);
  virtual void SetOrigin( const float* origin);
  virtual const double * GetOrigin() const;

  /** Set/Get the value for pixels inside the mask.
   * The default "inside" value is NumericTraits<OutputPixelType>::max(). 
   */
  itkSetMacro(InsideValue, ValueType);
  itkGetMacro(InsideValue, ValueType);

  /** Set/Get the value for pixels inside the mask.
   * The default "outside" value is NumericTraits<OutputPixelType>::Zero.
   */
  itkSetMacro(OutsideValue, ValueType);
  itkGetMacro(OutsideValue, ValueType);

  /** Add an ellipse object to the mask.
   * The center and radius are specified in physical space.
   */
  void AddEllipse(typename PointType center, float radius);

  /** Add an image region to the mask.
   */
  void AddRegion(typename RegionType region);

  /** Add a point object to the mask.
   * The point is specified in physical space.
   */
  void AddPoint(typename PointType point);

  /** Add an image object to the mask.
   *  All values greater than zero are assumed part of the mask.
   */
  void AddImage(typename MaskImageType* image);

protected:
  GenerateMaskImageFilter();
  ~GenerateMaskImageFilter();

  virtual void GenerateOutputInformation(){}; // do nothing
  virtual void GenerateData();
  virtual void GenerateDataForEllipses( TOutputImage* ptrOutputImage );
  virtual void GenerateDataForRegions ( TOutputImage* ptrOutputImage );
  virtual void GenerateDataForPoints  ( TOutputImage* ptrOutputImage );
  virtual void GenerateDataForImages  ( TOutputImage* ptrOutputImage );

  virtual void PrintSelf(std::ostream& os, Indent indent) const;

private:
  GenerateMaskImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  SizeType     m_Size;
  double       m_Spacing[OutputImageDimension];
  double       m_Origin[OutputImageDimension];
  ValueType    m_InsideValue;
  ValueType    m_OutsideValue;

  typedef ImageRegionIteratorWithIndex<typename OutputImageType> IteratorType;
  typedef ImageRegionIteratorWithIndex<typename MaskImageType> MaskIteratorType;

  // Hold a list of ellipses
  typedef EllipseListItem< typename PointType > EllipseListItemType;
  typedef std::list< typename EllipseListItemType > EllipseListType;
  typedef typename EllipseListType::iterator EllipseListIteratorType;
  EllipseListType m_EllipseList;
  
  // Hold a list of regions
  typedef std::list< typename RegionType > RegionListType;
  typedef typename RegionListType::iterator RegionListIteratorType;
  RegionListType m_RegionList;

  // Hold a list of points
  typedef std::list< typename PointType > PointListType;
  typedef typename PointListType::iterator PointListIteratorType;
  PointListType m_PointList;

  // Hold a list of images
  typedef std::list< typename MaskImageType* > ImageListType;
  typedef typename ImageListType::iterator ImageListIteratorType;
  ImageListType m_ImageList;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkGenerateMaskImageFilter.txx"
#endif

#endif
