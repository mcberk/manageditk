/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkPathInfo.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkPathInfo_h
#define __itkPathInfo_h

#include "itkPoint.h"

namespace itk
{

/** \class PathInfo
 * \brief PathInfo class for encapsulating information about a path.
 *
 *  The points are stored as follows: end, start, way0, way1, way2, ..., wayN.
 *  Wavefronts are propagated in reverse order: wayN, ..., way2, way1, way0, start.
 *  (NOTE: a wavefront is never propagated from end).
 */
template < unsigned int VDimension >
class PathInfo
{
public:
    /** Some useful typedefs */
	typedef double CoordRepType;
    typedef Point< CoordRepType, VDimension > PointType;

    PathInfo()
      { this->ClearInfo(); }
    void ClearInfo()
      { m_Info.clear();  m_Info.resize(2); m_Wavefront = 1; }
    void SetStartPoint( const PointType & start )
      { m_Info[1] = start; }
    void SetEndPoint( const PointType & end )
      { m_Info[0] = end; }
    void AddWayPoint( const PointType & way )
      { m_Info.push_back( way ); m_Wavefront++; }
    unsigned int GetNumberOfPoints( ) const
      { return m_Info.size(); }
    const PointType & GetStartPoint( ) const
      { return m_Info[1]; }
    const PointType & GetEndPoint( ) const
      { return m_Info[0]; }
    const PointType & GetWayPoint( unsigned int i ) const
      { return m_Info[2+i]; }
    const bool HasNextWavefront( ) const
      { return m_Wavefront >= 1; }
    const PointType & GetCurrentWavefrontAndAdvance( )
      { return m_Info[m_Wavefront--]; }
    const PointType & PeekCurrentWavefront( )
      { return m_Info[m_Wavefront]; }
    const PointType & PeekNextWavefront( )
      {
      if ( m_Wavefront <= 1 ) return m_Info[1];
      else return m_Info[m_Wavefront-1];
	  }
    const PointType & PeekPreviousWavefront( )
      {
      if ( m_Wavefront == m_Info.size()-1 ) return m_Info[0];
      else return m_Info[m_Wavefront+1];
	  }
private:
    std::vector< PointType > m_Info;
    unsigned int m_Wavefront;
  };
  
} // end namespace itk

#endif