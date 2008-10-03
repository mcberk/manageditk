/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkLevelSetSpeedImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkLevelSetSpeedImageFilter_h
#define __itkLevelSetSpeedImageFilter_h

#include "itkImageToImageFilter.h"

namespace itk {

/** \class LevelSetSpeedImageFilter
 * \brief Compute a speed image for level set algorithms.
 *
 * The resultant speed image is an edge-based function followed
 * by a non-linear remapping. A threshold is also provided to 
 * easily exclude areas based on intensity. The speed image is
 * controlled by five parameters:
 *   1. Gaussian Sigma
 *   2. Sigmoid Alpha
 *   3. Sigmoid Beta
 *   4. Threshold Lower
 *   5. Threshold Upper.
 *
 * The output minimum and output maximum can also be set to cater
 * for level sets (varying [-1.0...1.0] or fast marching (varying
 * [0.0...1.0]).
 *
 * The input and output images must have a real-valued pixel type
 * (eg. float or double).
 */
template<class TInputImage, class TOutputImage>
class ITK_EXPORT LevelSetSpeedImageFilter :
    public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef LevelSetSpeedImageFilter Self;
  typedef ImageToImageFilter<TInputImage, TOutputImage> Superclass;
  typedef SmartPointer<Self>        Pointer;
  typedef SmartPointer<const Self>  ConstPointer;

  /** Some convenient typedefs. */
  typedef TInputImage InputImageType;
  typedef TOutputImage OutputImageType;
  typedef typename InputImageType::Pointer         InputImagePointer;
  typedef typename InputImageType::ConstPointer    InputImageConstPointer;
  typedef typename InputImageType::RegionType      InputImageRegionType;
  typedef typename InputImageType::PixelType       InputImagePixelType;
  typedef typename OutputImageType::Pointer        OutputImagePointer;
  typedef typename OutputImageType::ConstPointer   OutputImageConstPointer;
  typedef typename OutputImageType::RegionType     OutputImageRegionType;
  typedef typename OutputImageType::PixelType      OutputImagePixelType;
  
  /** ImageDimension constants */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TInputImage::ImageDimension);

  /** Standard New method. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(LevelSetSpeedImageFilter, ImageToImageFilter);

  /**
   * Set/Get if the gaussian is normalized across the scale.
   */
  itkSetMacro(GaussianNormalizeAcrossScale, bool);
  itkGetConstReferenceMacro(GaussianNormalizeAcrossScale, bool);

  /**
   * Set/Get the sigma value for the gradient magnitude.
   */
  itkSetMacro(GaussianSigma, double);
  itkGetConstReferenceMacro(GaussianSigma, double);

  /**
   * Set/Get the sigmoid values.
   */
  itkSetMacro(SigmoidAlpha, double);
  itkGetConstReferenceMacro(SigmoidAlpha, double);
  itkSetMacro(SigmoidBeta, double);
  itkGetConstReferenceMacro(SigmoidBeta, double);
  
  /**
   * Set/Get the threshold values. Values outside of this
   * range are ignored.
   */
  itkSetMacro(ThresholdLower, InputImagePixelType);
  itkGetConstReferenceMacro(ThresholdLower, InputImagePixelType);
  itkSetMacro(ThresholdUpper, InputImagePixelType);
  itkGetConstReferenceMacro(ThresholdUpper, InputImagePixelType);
  
  /**
   * Set/Get output minimum and maximum values. Typical values
   * are -1.0 for minimum and 1.0 for maximum (except for fast
   * marching methods which expect 0.0 minimum).
   */
  itkSetMacro(OutputMinimum, OutputImagePixelType);
  itkGetConstReferenceMacro(OutputMinimum, OutputImagePixelType);
  itkSetMacro(OutputMaximum, OutputImagePixelType);
  itkGetConstReferenceMacro(OutputMaximum, OutputImagePixelType);

protected:
  LevelSetSpeedImageFilter();
  ~LevelSetSpeedImageFilter() {};
  void PrintSelf(std::ostream& os, Indent indent) const;

  /** LevelSetSpeedImageFilter needs the entire input be
   * available. Thus, it needs to provide an implementation of
   * GenerateInputRequestedRegion(). */
  void GenerateInputRequestedRegion() ;
  
  /** LevelSetSpeedImageFilter will produce the entire output. */
  void EnlargeOutputRequestedRegion(DataObject *itkNotUsed(output));

  /** Single-threaded version of GenerateData. */
  void GenerateData();
  

private:
  LevelSetSpeedImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  bool m_GaussianNormalizeAcrossScale;
  double m_GaussianSigma;
  double m_SigmoidAlpha;
  double m_SigmoidBeta;
  InputImagePixelType m_ThresholdLower;
  InputImagePixelType m_ThresholdUpper;
  OutputImagePixelType m_OutputMinimum;
  OutputImagePixelType m_OutputMaximum;

} ; // end of class

} // end namespace itk
  
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkLevelSetSpeedImageFilter.txx"
#endif

#endif
