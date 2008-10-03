/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkSpeedFunctionToPathFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkSpeedFunctionToPathFilter_h
#define __itkSpeedFunctionToPathFilter_h

#include "itkPathInfo.h"
#include "itkArrivalFunctionToPathFilter.h"

namespace itk
{

/** \class SpeedFunctionToPathFilter
 * \brief Extracts a path from a speed function between a start point
 *       and end point which also passes through the given way points.
 *
 * This filter expects the input to be a speed function for guiding
 * minmal path extraction. A path is extracted which travels from
 * start to end, and passes through the given way points. The speed
 * image should be of real (float or double) type.
 *
 * If an optimizer is not provided, a RegularStepGradientDescentOptimizer
 * is created with default settings. Other suitable optimizers include
 * GradientDescentOptimizer and IterateNeighborhoodOptimizer.
 *
 * At present, the resultant path(s) are in reverse order: the vertices are
 * listed from end to start. See itkArrivalFunctionToPathFilter for more details.
 *
 * \author Dan Mueller, Queensland University of Technology, dan.muel[at]gmail.com
 *
 * \sa itkArrivalFunctionToPathFilter
 * \ingroup ImageToPathFilters
 */
template <class TInputImage,
          class TOutputPath = PolyLineParametricPath<TInputImage::ImageDimension> >
class ITK_EXPORT SpeedFunctionToPathFilter :
    public ArrivalFunctionToPathFilter<TInputImage,TOutputPath>
{
public:
  /** Standard class typedefs. */
  typedef SpeedFunctionToPathFilter                Self;
  typedef ArrivalFunctionToPathFilter<TInputImage,TOutputPath> Superclass;
  typedef SmartPointer<Self>                                   Pointer;
  typedef SmartPointer<const Self>                             ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(SpeedFunctionToPathFilter,ArrivalFunctionToPathFilter);
  
  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** ImageDimension constants */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Some image typedefs. */
  typedef TInputImage InputImageType;
  typedef typename InputImageType::Pointer        InputImagePointer;
  typedef typename InputImageType::ConstPointer   InputImageConstPointer;
  typedef typename InputImageType::RegionType     InputImageRegionType; 
  typedef typename InputImageType::PixelType      InputImagePixelType; 

  /** Some convenient typedefs. */
  typedef typename Superclass::ContinuousIndexType ContinuousIndexType;
  typedef typename Superclass::PointType           PointType;
  typedef typename Superclass::CostFunctionType    CostFunctionType;
  typedef typename Superclass::OptimizerType       OptimizerType;
  typedef typename PathInfo<InputImageDimension>   PathInfoType;
  
  /** Override superclass behaviour. */
  void SetPathEndPoint( const PointType & point )
  {
    itkWarningMacro("SetPathEndPoint is not valid for this filter. Use AddPathInfo instead.");
  }

  /** Override superclass behaviour. */
  void AddPathEndPoint( const PointType & point )
  {
    itkWarningMacro("AddPathEndPoint is not valid for this filter. Use AddPathInfo instead.");
  };

  /** Override superclass behaviour. */
  void ClearPathEndPoints()
  {
    itkWarningMacro("ClearPathEndPoints is not valid for this filter. Use ClearPathInfo instead.");
  };

  /** Add a path information object to process. */
  void AddPathInfo( const PathInfoType & info )
  {
    m_Info.push_back( info );
  };

  /** Clear the list of path information objects. */
  void ClearPathInfo()
  {
    m_Info.clear( );
  };

  /** Override handling of optimizer iteration events. */
  virtual void Execute( const itk::Object * object, const itk::EventObject & event );

protected:
  SpeedFunctionToPathFilter();
  ~SpeedFunctionToPathFilter();
  virtual void PrintSelf(std::ostream& os, Indent indent) const;
  
  /** Implemention of algorithm. */
  void GenerateData( void );

  /** Get the arrival function from which to extract the path. */
  virtual unsigned int GetNumberOfPathsToExtract( ) const;

  /** Compute the arrival function from which to extract the path. */
  virtual InputImageType * ComputeArrivalFunction( );

  /** Override handling of optimizer iteration events to accomodate way points. */
  virtual const PointType & GetNextEndPoint( );

  std::vector< PathInfoType > m_Info;
  InputImagePointer m_CurrentArrivalFunction;

private:
  SpeedFunctionToPathFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
    
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkSpeedFunctionToPathFilter.txx"
#endif

#endif
