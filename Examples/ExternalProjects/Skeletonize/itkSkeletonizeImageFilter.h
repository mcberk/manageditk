#ifndef itkSkeletonizationImageFilter_h
#define itkSkeletonizationImageFilter_h

#include <itkImage.h>
#include <itkImageFunction.h>
#include <itkImageToImageFilter.h>

#include "itkConnectivity.h"

namespace itk
{

/**
 * @brief Computes the skeleton of an image using homotopic thinning.
 *
 * @param FGC the connectivity used in the foreground
 *
 * This algorithm needs the following inputs :
 * - An image to be skeletonized
 * - An image to order the removal
 * - A simplicity criterion
 * - A terminality criterion
 *
 * @pre The object in the image must not touch the border.
 *
 * If no simplicity criterion is provided, the default is to compute the 
 * topological numbers and to qualify a point as simple iff both numbers are 
 * equal to 1.
 * @sa itk::SimplicityByTopologicalNumbersImageFunction
 *
 * If no terminality criterion is provided, the default is to keep the line 
 * terminal points, i.e. points having only one neighbor in the object.
 * @sa itk::LineTerminalityImageFunction
 */
template<typename TImage, typename TOrderingImage, typename TForegroundConnectivity=itk::Connectivity<TImage::ImageDimension, 0> >
class SkeletonizeImageFilter : public ImageToImageFilter<TImage,TImage>
  {
  public :
    /**
     * @name Standard ITK declarations
     */
    //@{
    typedef SkeletonizeImageFilter Self;
    typedef ImageToImageFilter<TImage,TImage> Superclass;
    typedef SmartPointer<Self> Pointer;
    typedef SmartPointer<Self const> ConstPointer;

    itkNewMacro(Self);
    itkTypeMacro(SkeletonizeImageFilter, ImageToImageFilter);
    
    //@}
    
    /**
     * @name Standard filter typedefs.
     */
    //@{
    typedef TImage InputImageType;
    typedef TImage OutputImageType;
    //@}
    
    /**
     * @name Define the type of the ordering image.
     */
    //@{
    typedef TOrderingImage OrderingImageType;
    typedef typename OrderingImageType::PixelType OrderingVoxelType;
    //@}
    
    /**
     * @brief Type of the simplicity and terminality functors.
     */
    typedef ImageFunction<OutputImageType, bool> Criterion;
    
    /**
     * @name Accessors for the ordering image.
     */
    //@{
    void SetOrderingImage(OrderingImageType *input);
    OrderingImageType * GetOrderingImage();

    //@}
    
    /**
     * @name Accessors for the simplicity criterion.
     */
    //@{
    itkGetConstObjectMacro(SimplicityCriterion, Criterion);
    itkSetObjectMacro(SimplicityCriterion, Criterion);
    //@}
    
    /**
     * @name Accessors for the terminality criterion.
     */
    //@{
    itkGetConstObjectMacro(TerminalityCriterion, Criterion);
    itkSetObjectMacro(TerminalityCriterion, Criterion);
    //@}
    
    /**
     * @brief Connectivity used in the foreground of the image.
     */
    typedef TForegroundConnectivity ForegroundConnectivity;
      
  protected :
    SkeletonizeImageFilter();
    SkeletonizeImageFilter(Self const &); // Purposedly not implemented
    void operator=(Self const &); // Purposedly not implemented

    void PrintSelf(std::ostream& os, Indent indent) const;
    void GenerateInputRequestedRegion();
    void GenerateData();
    
    typename OrderingImageType::Pointer m_OrderingImage;
    
    typename ImageFunction<TImage, bool >::Pointer m_SimplicityCriterion;
    typename ImageFunction<TImage, bool >::Pointer m_TerminalityCriterion;
      
  };

} // namespace itk

#include "itkSkeletonizeImageFilter.txx"

#endif
