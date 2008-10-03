################################################################################
# Expose some 'wrapping' options to the user
################################################################################
OPTION(WRAP_unsigned_char "Wrap unsigned char type" ON)
OPTION(WRAP_unsigned_short "Wrap unsigned short type" OFF)
OPTION(WRAP_unsigned_long "Wrap unsigned long type" OFF)

OPTION(WRAP_signed_char "Wrap signed char type" OFF)
OPTION(WRAP_signed_short "Wrap signed short type" ON)
OPTION(WRAP_signed_long "Wrap signed long type" OFF)

OPTION(WRAP_float "Wrap float type" ON)
OPTION(WRAP_double "Wrap double type" OFF)
OPTION(WRAP_bool "Wrap bool type" OFF)

OPTION(WRAP_vector "Wrap vector type" ON)
OPTION(WRAP_covariant_vector "Wrap covariant vector type" ON)

OPTION(WRAP_rgb_unsigned_char "Wrap RGB< unsigned char > type" ON)
OPTION(WRAP_rgb_unsigned_short "Wrap RGB< unsigned short > type" OFF)
OPTION(WRAP_rgba_unsigned_char "Wrap RGBA< unsigned char > type" ON)
OPTION(WRAP_rgba_unsigned_short "Wrap RGBA< unsigned short > type" OFF)

SET(WRAP_dimensions "2;3" CACHE STRING "Dimensions available separated by semicolons (;)")
SET(WRAP_ITK_DIMS ${WRAP_dimensions})
#-------------------------------------------------------------------------------


################################################################################
# Include some useful CMake files
################################################################################
INCLUDE(CMakeUtilityFunctions.cmake)
INCLUDE(WrapUtilityFunctions.cmake)
INCLUDE(WrapBasicTypes.cmake)
INCLUDE(WrapCodeGen.cmake)
#-------------------------------------------------------------------------------


################################################################################
# Wrap the basic types and images
################################################################################
INCLUDE(WrapITKTypes.cmake)
#-------------------------------------------------------------------------------


################################################################################
# Configure the source files for itk::Image
################################################################################
# itkManagedImage.cxx.in expects the following variables to be configured:
#   MANGLED_SUFFIX, TEMPLATE_PARAMS, MANGLED_PIXEL, DIMENSION

SET(common_files )
SET(template_regex "([0-9A-Za-z_]*)[ ]*#[ ]*(.*)")

# Wrap itk::Images
SET(IMAGE_TYPE "itk::Image")
FOREACH(wrap ${itk_Wrap_Image})

    STRING(REGEX REPLACE "${template_regex}" "\\1" MANGLED_SUFFIX "${wrap}")
    STRING(REGEX REPLACE "${template_regex}" "\\2" TEMPLATE_PARAMS "${wrap}")

    # Get the mangled pixel type and image dimension
    SET(pixel_regex "([A-Za-z]+[0-9]?)([0-9])")
    STRING(REGEX REPLACE "${pixel_regex}" "\\1" MANGLED_PIXEL "${MANGLED_SUFFIX}")
    STRING(REGEX REPLACE "${pixel_regex}" "\\2" DIMENSION "${MANGLED_SUFFIX}")

    # Configure itkManagedImage file
    CONFIGURE_FILE( ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImage_TYPE.cxx.in
                    ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}/itkManagedImage_${MANGLED_SUFFIX}.cxx
                    @ONLY )

    # Add file to project
    SET(  common_files ${common_files}
        ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}/itkManagedImage_${MANGLED_SUFFIX}.cxx)

ENDFOREACH(wrap)

# Wrap itk::VectorImages
SET(IMAGE_TYPE "itk::VectorImage")
FOREACH(wrap ${itk_Wrap_VectorImage})

    STRING(REGEX REPLACE "${template_regex}" "\\1" MANGLED_SUFFIX "${wrap}")
    STRING(REGEX REPLACE "${template_regex}" "\\2" TEMPLATE_PARAMS "${wrap}")
    SET(MANGLED_SUFFIX "VI${MANGLED_SUFFIX}")

    # Get the mangled pixel type and image dimension
    SET(pixel_regex "([A-Za-z]+[0-9]?)([0-9])")
    STRING(REGEX REPLACE "${pixel_regex}" "\\1" MANGLED_PIXEL "${MANGLED_SUFFIX}")
    STRING(REGEX REPLACE "${pixel_regex}" "\\2" DIMENSION "${MANGLED_SUFFIX}")

    # Configure itkManagedImage file
    CONFIGURE_FILE( ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImage_TYPE.cxx.in
                    ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}/itkManagedImage_${MANGLED_SUFFIX}.cxx
                    @ONLY )

    # Add file to project
    SET(  common_files ${common_files}
        ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}/itkManagedImage_${MANGLED_SUFFIX}.cxx)

ENDFOREACH(wrap)

# Wrap itk::FlatStructuringElement
FOREACH(d ${WRAP_ITK_DIMS})
    # Configure itkManagedFlatStructuringElement file
    SET( MANAGED_DIMENSION ${d} )
    CONFIGURE_FILE( ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFlatStructuringElement_TYPE.cxx.in
                    ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}/itkManagedFlatStructuringElement_${MANAGED_DIMENSION}.cxx
                    @ONLY )

    # Add file to project
    SET(  common_files ${common_files}
        ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}/itkManagedFlatStructuringElement_${MANAGED_DIMENSION}.cxx)
ENDFOREACH(d)

# Configure required common files
SET( common_files_needing_configuring
     itkManagedTypes.cxx
     itkManagedObjectCommand.cxx
     itkManagedProcessObjectCommand.cxx
     )
FOREACH( file ${common_files_needing_configuring})
         CONFIGURE_FILE( ${MANAGED_ITK_SOURCE_COMMON_PATH}/${file}.in
                         ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}/${file}
                         @ONLY )
ENDFOREACH(file)

# Add Common files
SET(  common_files ${common_files}
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/AssemblyInfo.cpp
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedInvalidWrappedTypeException.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedINativePointer.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedDimension.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedRadius.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialOrientation.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedArray.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedExceptionObject.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedPixelType.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedPixel.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedContinuousIndex.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedIndex.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedOffset.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedPoint.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSize.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpacing.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedVector.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMatrix.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedQuaternion.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedVersor.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageRegion.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedObject.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedNoSmartPointerObject.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedDataObject.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedDataObjectWithReadWrite.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageInformation.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageBase.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImage.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedNeighborhood.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedNeighborhoodOperator.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFlatStructuringElement.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageConstIterator.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIterator.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageConstIteratorWithIndex.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIteratorWithIndex.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedProcessObject.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageSource.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageFilter.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedPipeline.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedParametricPath.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedPathSource.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToPathFilter.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedTransform.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMatrixOffsetTransform.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedCostFunction.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSingleValuedCostFunction.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedOptimizer.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedNonLinearOptimizer.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSingleValuedNonLinearOptimizer.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedLevelSetNode.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFiniteDifferenceImageFilter.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSegmentationLevelSetImageFilter.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMultiThreader.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObjectBase.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedPointSetBase.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedCell.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshBase.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshSource.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToMeshFilter.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshToMeshFilter.cxx
      ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIOBase.cxx
      )

# Add the Common shared library
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /AI \"${MANAGED_ITK_SOURCE_OUTPUT_PATH}\"")
INCLUDE_DIRECTORIES( BEFORE
    ${MANAGED_ITK_SOURCE_MODULES_PATH}
    ${MANAGED_ITK_SOURCE_COMMON_PATH}
    ${MANAGED_ITK_SOURCE_COMMON_PATH}/FastMorphology
    ${VXL_INCLUDE_DIRS}
)
ADD_LIBRARY( ${MANAGED_ITK_ASSEMBLY_PREFIX}.Common SHARED ${common_files} )
TARGET_LINK_LIBRARIES( ${MANAGED_ITK_ASSEMBLY_PREFIX}.Common ${ITK_LIBRARIES} ${MANAGED_ITK_LIBRARIES} )

#-------------------------------------------------------------------------------


################################################################################
# Process modules
################################################################################
SUBDIRS(Modules)
#-------------------------------------------------------------------------------

