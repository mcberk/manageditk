/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkArrivalFunctionToPathFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkArrivalFunctionToPathFilter_h
#define __itkArrivalFunctionToPathFilter_h

#include "itkImage.h"
#include "itkCommand.h"
#include "itkImageToPathFilter.h"
#include "itkSingleImageCostFunction.h"
#include "itkRegularStepGradientDescentOptimizer.h"
#include "itkSingleValuedNonLinearOptimizer.h"
#include "itkPolyLineParametricPath.h"

namespace itk
{

/** A command to listen for Optimizer Iteration events. */
template <class TFilter>
class ArrivalFunctionToPathCommand : public itk::Command
{
public:
  /** Standard class typedefs. */
  typedef  ArrivalFunctionToPathCommand   Self;
  typedef  itk::Command             Superclass;
  typedef  itk::SmartPointer<Self>  Pointer;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );
  
  /** Some useful typedefs. */
  typedef TFilter FilterType;

protected:
  ArrivalFunctionToPathCommand(){};
  
private:
  typename FilterType::Pointer m_Filter;

public:

  /** Get/set the Filter. */
  itkSetObjectMacro( Filter, FilterType );
  itkGetConstObjectMacro( Filter, FilterType );

  /** Execute */
  void Execute(itk::Object *caller, const itk::EventObject & event)
  {
    Execute( (const itk::Object *)caller, event);
  }

  /** Execute */
  void Execute(const itk::Object * object, const itk::EventObject & event)
  {
    if( ! itk::IterationEvent().CheckEvent( &event ) )
      {
      return;
      }
    // Pass event to Filter
    if ( m_Filter.IsNotNull() )
      {
      m_Filter->Execute( object, event );
      }
  }
};

  
/** \class ArrivalFunctionToPathFilter
 * \brief Extracts a path to the given point from the arrival function.
 *
 * This filter expects the input to be an arrival function indicating the
 * minimal action surface (such as an arrival time function generated
 * as the output of the Fast Marching method). At least one point must be
 * given to indicate the end location of the path to extract (the starting
 * point is implicitly specified in the arrival function). The output is
 * the path between the two points (it may be minimal depending on the 
 * specified optimizer). If more than one point is given, then each output
 * corresponds to the path extracted by back-propagating from the associated
 * end point.
 *
 * If an optimizer is not provided, a RegularStepGradientDescentOptimizer
 * is created with default settings. Other suitable optimizers include
 * GradientDescentOptimizer and IterateNeighborhoodOptimizer.
 *
 * At present, the resultant path(s) is in reverse order: the vertices are
 * listed from end to start. The start point is embedded in the arrival function
 * and at least one end point must be provided to this filter.
 *
 * This filter is inspired by Thomas Deschamps, "Curve and Shape Extraction
 * with Minimal Path and Level-Sets techniques: Applications to 3D Medical
 * Imaging", PhD Thesis, University of Paris Dauphine, December 2001.
 * URL: http://math.lbl.gov/~deschamp/html/phdthesis.html
 *
 * There may be patents covering this algorithm:
 * See: http://math.lbl.gov/~deschamp/html/publications.html#SECT3
 *
 * \author Dan Mueller, Queensland University of Technology, dan.muel[at]gmail.com
 *
 * \ingroup ImageToPathFilters
 */
template <class TInputImage,
          class TOutputPath = PolyLineParametricPath<TInputImage::ImageDimension> >
class ITK_EXPORT ArrivalFunctionToPathFilter :
    public ImageToPathFilter<TInputImage,TOutputPath>
{
public:
  /** Standard class typedefs. */
  typedef ArrivalFunctionToPathFilter                Self;
  typedef ImageToPathFilter<TInputImage,TOutputPath> Superclass;
  typedef SmartPointer<Self>                         Pointer;
  typedef SmartPointer<const Self>                   ConstPointer;

  /** Run-time type information (and related methods). */
  itkTypeMacro(ArrivalFunctionToPathFilter,ImageToPathFilter);
  
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
  typedef Index< InputImageDimension >                   IndexType;
  typedef ContinuousIndex< double, InputImageDimension > ContinuousIndexType;
  typedef Point< double, InputImageDimension >           PointType;
  typedef ArrivalFunctionToPathCommand< Self >           CommandType;
  typedef SingleImageCostFunction< InputImageType >      CostFunctionType;
  typedef SingleValuedNonLinearOptimizer                 OptimizerType;
  typedef RegularStepGradientDescentOptimizer            DefaultOptimizerType;

  /** Get/set the Optimizer. */
  itkSetObjectMacro( Optimizer, OptimizerType );
  itkGetConstObjectMacro( Optimizer, OptimizerType );

  /** Get/set the cost function. The filter (not the user) is responsible
   *  for connecting the arrival function to the cost function. */
  itkSetObjectMacro( CostFunction, CostFunctionType );
  itkGetConstObjectMacro( CostFunction, CostFunctionType );

  /** Clears the list of end points and adds the given point to the list. */
  virtual void SetPathEndPoint( const PointType & point )
  {
    this->ClearPathEndPoints();
    this->AddPathEndPoint( point );
  }

  /** Adds the given point to the list. */
  virtual void AddPathEndPoint( const PointType & point )
  {
    m_PointList.push_back( point );
    this->Modified();
  };

  /** Clear the list of end points. */
  virtual void ClearPathEndPoints()
  {
    if (m_PointList.size() > 0)
      {
      m_PointList.clear();
      this->Modified();
      }
  };

  /** Get/set the termination. Once the current optimizer value falls below
   *  TerminationValue,no further points will be appended to the path.
   *  The default value is 0.0. */
  itkSetMacro(TerminationValue, OptimizerType::MeasureType);
  itkGetMacro(TerminationValue, OptimizerType::MeasureType);

  /** Handle optimizer iteration events. */
  virtual void Execute( const itk::Object * object, const itk::EventObject & event );

protected:
  ArrivalFunctionToPathFilter();
  ~ArrivalFunctionToPathFilter();
  virtual void PrintSelf(std::ostream& os, Indent indent) const;

  /** Override since the filter needs all the data for the algorithm */
  void GenerateInputRequestedRegion();

  /** Implemention of algorithm */
  void GenerateData(void);

  /** Get the arrival function from which to extract the path. */
  virtual unsigned int GetNumberOfPathsToExtract( ) const;

  /** Compute the arrival function from which to extract the path.
   *  In this case it is simply the filter input. */
  virtual InputImageType * ComputeArrivalFunction( );

  /** Get the next end point from which to back propagate. */
  virtual const PointType & GetNextEndPoint( );

  typename CostFunctionType::Pointer m_CostFunction; 
  OptimizerType::Pointer m_Optimizer;
  OptimizerType::MeasureType m_TerminationValue;
  std::vector<PointType> m_PointList;
  unsigned int m_CurrentOutput;

private:
  ArrivalFunctionToPathFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkArrivalFunctionToPathFilter.txx"
#endif

#endif
