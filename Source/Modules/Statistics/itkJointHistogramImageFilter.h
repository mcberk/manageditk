/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile: itkJointHistogramImageFilter.h,v $
  Language:  C++
  Date:      $Date: 2007-08-31 22:17:25 +0200 (Fri, 31 Aug 2007) $
  Version:   $Revision: 2 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkJointHistogramImageFilter_h
#define __itkJointHistogramImageFilter_h

#include "itkArray.h"
#include "itkNumericTraits.h"
#include "itkImage.h"
#include "itkImageToImageFilter.h"

namespace itk {

/** /class JointHistogramImageFilter
 * \brief Generate a joint histogram image from two inputs.
 *
 * JointHistogramImageFilter generates a joint histogram image from two
 * inputs. The inputs are firstly joined using the JoinImageFilter, the
 * histogram is then generated, and finally converted to an output image.
 * The user can specify the number of bins, the marginal scale, and the
 * type of mapping from histogram to output image (intensity, entropy,
 * probablility, or log probability).
 *
 *
 * \author Dan Mueller
 *
 * This class was contributed to the Insight Journal by author Dan Mueller.
 * Queensland University of Technology, Brisbane, Australia.
 * The paper can be found at http://hdl.handle.net/1926/XXX
 *
 * \ingroup Statistics
 */
template <class TInputImage, class TOutputImage>
class ITK_EXPORT JointHistogramImageFilter:
    public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard class typedefs. */
  typedef JointHistogramImageFilter Self;
  typedef ImageToImageFilter<TInputImage,TOutputImage> Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods).  */
  itkTypeMacro(JointHistogramImageFilter,
               ImageToImageFilter);

  /** Some useful typedefs */
  typedef TInputImage InputImageType;
  typedef typename InputImageType::Pointer InputImagePointer;
  typedef typename InputImageType::ConstPointer InputImageConstPointer;
  typedef typename InputImageType::RegionType InputImageRegionType; 
  typedef typename InputImageType::PixelType InputImagePixelType; 
  typedef typename InputImageType::IndexType IndexType;
  typedef typename InputImageType::SizeType SizeType;
  
  typedef TOutputImage OutputImageType;
  typedef typename OutputImageType::Pointer OutputImagePointer;
  typedef typename OutputImageType::RegionType OutputImageRegionType; 
  typedef typename OutputImageType::PixelType OutputImagePixelType;
  typedef typename OutputImageType::SizeType OutputSizeType;

  typedef Array<unsigned int> NumberOfBinsType;

  /** Declare the HistogramToImageMapping type */
  enum HistogramToImageMappingEnum
  {
    Intensity,
    Entropy,
    Probability,
    LogProbability
  };

  /**
   * Get/set the number of bins in the different directions.
   * This array must be the same length as the number of inputs.
   */
  itkSetMacro(NumberOfBins, NumberOfBinsType);
  itkGetConstMacro(NumberOfBins, NumberOfBinsType);

  /**
   * Get/set the marginal scale value.
   */
  itkSetMacro(MarginalScale, double);
  itkGetConstMacro(MarginalScale, double);
  
  /**
   * Get/set the histogram to image mapping type.
   * Valid mappings are: Intensity, Entropy, Probability,
   * and LogProbability.
   */
  itkSetEnumMacro(Mapping, HistogramToImageMappingEnum);
  itkGetEnumMacro(Mapping, HistogramToImageMappingEnum);

  /** Image dimension constants */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      TInputImage::ImageDimension);
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      TOutputImage::ImageDimension);

#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  // TODO:
  /** End concept checking */
#endif

protected:
  JointHistogramImageFilter();
  ~JointHistogramImageFilter(){};
  void PrintSelf ( std::ostream& os, Indent indent ) const;
  
  // Override since the filter needs all the data for the algorithm
  void GenerateInputRequestedRegion();

  // This filter can produce an image which is a different resolution
  // than its input image.  As such, we need to provide an implementation
  // for GenerateOutputInformation() in order to inform the pipeline
  // execution model. 
  void GenerateOutputInformation();

  // Override since the filter produces the entire dataset
  void EnlargeOutputRequestedRegion(DataObject *output);

  // Override
  void GenerateData();
  
private:
  JointHistogramImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  NumberOfBinsType m_NumberOfBins;
  double m_MarginalScale;
  HistogramToImageMappingEnum m_Mapping;

};

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkJointHistogramImageFilter.txx"
#endif

#endif
