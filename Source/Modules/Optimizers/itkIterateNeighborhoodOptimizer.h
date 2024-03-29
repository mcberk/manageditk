/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkIterateNeighborhoodOptimizer.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkIterateNeighborhoodOptimizer_h
#define __itkIterateNeighborhoodOptimizer_h

#include "itkArray.h"
#include "itkSingleValuedNonLinearOptimizer.h"

namespace itk
{
  
/** \class IterateNeighborhoodOptimizer
 * \brief Finds the local minima/maxima by iteratively choosing the
 *        minimum/maximum value in a neighborhood.
 *
 * This optimizer is designed to operate on a monotonic cost function
 * WITHOUT using gradient information (derivatives). The user must set
 * the Neighborhood size, and optionally the connectivity.
 * 
 * \ingroup Numerics Optimizers
 */  
class ITK_EXPORT IterateNeighborhoodOptimizer :
    public SingleValuedNonLinearOptimizer
{
public:
  /** Standard class typedefs. */
  typedef IterateNeighborhoodOptimizer   Self;
  typedef SingleValuedNonLinearOptimizer Superclass;
  typedef SmartPointer<Self>             Pointer;
  typedef SmartPointer<const Self>       ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro( Self );

  /** Run-time type information (and related methods). */
  itkTypeMacro( IterateNeighborhoodOptimizer, SingleValuedNonLinearOptimizer );

  /** Configure whether the local maxima or minima is found.
   *  The default is to minimize the cost function (maximize = false ).*/
  itkGetConstReferenceMacro( Maximize, bool );
  itkSetMacro( Maximize, bool );
  itkBooleanMacro( Maximize );
  bool GetMinimize( ) const
    { return !m_Maximize; }
  void SetMinimize(bool v)
    { this->SetMaximize(!v); }
  void MinimizeOn()
    { this->MaximizeOff(); }
  void MinimizeOff()
    { this->MaximizeOn(); }

  /** Advance one step. */
  virtual void AdvanceOneStep( void );

  /** Start optimization. */
  void StartOptimization( void );

  /** Resume previously stopped optimization with current parameters
   * \sa StopOptimization. */
  void ResumeOptimization( void );

  /** Stop optimization.
   * \sa ResumeOptimization */
  void StopOptimization( void );
  
  /**
   * Get/set whether the nieghborhood is defined by face connectivity or
   * by face+edge+vertex connectivity.  Default is FullyConnectedOn.
   */
  itkSetMacro(FullyConnected, bool);
  itkGetConstReferenceMacro(FullyConnected, bool);
  itkBooleanMacro(FullyConnected);

  /** Get/set the nieghborhood size (in physical space).
   *  The default is [1.0,1.0] and MUST be specified for all 3-D images
   *  and 2-D images with non-unity spacing. */
  typedef Array<double> NeighborhoodSizeType;
  itkSetMacro( NeighborhoodSize, NeighborhoodSizeType );
  itkGetConstReferenceMacro( NeighborhoodSize, NeighborhoodSizeType );

  /** Get the current iteration number. */
  itkGetConstMacro( CurrentIteration, unsigned int );

  /** Get the current value. */
  itkGetConstReferenceMacro( CurrentValue, double );

protected:
  IterateNeighborhoodOptimizer();
  virtual ~IterateNeighborhoodOptimizer() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

private:
  IterateNeighborhoodOptimizer(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented
  
  bool                 m_Stop;
  bool                 m_Maximize;
  bool                 m_FullyConnected;
  double               m_CurrentValue;
  unsigned long        m_CurrentIteration;
  NeighborhoodSizeType m_NeighborhoodSize;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkIterateNeighborhoodOptimizer.txx"
#endif

#endif
