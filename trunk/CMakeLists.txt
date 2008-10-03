################################################################################
# Project: ManagedITK
#-------------------------------------------------------------------------------
# This project creates Managed (ie. .NET) wrappers for common ITK filters and
# algorithms.
#
# Dan Mueller
# dan.muel[at]gmail.com
#
################################################################################

# Set the project name
PROJECT(ManagedITK)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Include some useful macros associated with the Insight Journal
INCLUDE(${CMAKE_SOURCE_DIR}/IJMacros.txt)

# Set external dependencies.
SET(Required_Packages
    ITK
)

# This foreach loads all of the packages that you specified as required.
FOREACH(Package ${Required_Packages})
  LOADPACKAGE(${Package})
ENDFOREACH(Package)

# Setup some useful paths
SET(MANAGED_ITK_CMAKE_PATH "${CMAKE_SOURCE_DIR}")
SET(MANAGED_ITK_SOURCE_PATH "${MANAGED_ITK_CMAKE_PATH}/Source")
SET(MANAGED_ITK_IMAGES_PATH "${MANAGED_ITK_CMAKE_PATH}/Images")
SET(MANAGED_ITK_TESTING_PATH "${MANAGED_ITK_CMAKE_PATH}/Testing")
SET(MANAGED_ITK_EXAMPLES_PATH "${MANAGED_ITK_CMAKE_PATH}/Examples")
SET(MANAGED_ITK_UTILITIES_PATH "${MANAGED_ITK_CMAKE_PATH}/Utilities")

SET(MANAGED_ITK_SOURCE_COMMON_PATH "${MANAGED_ITK_SOURCE_PATH}/Common")
SET(MANAGED_ITK_SOURCE_MODULES_PATH "${MANAGED_ITK_SOURCE_PATH}/Modules")
SET(MANAGED_ITK_SOURCE_REFERENCES_PATH "${MANAGED_ITK_SOURCE_PATH}/References")

SET(MANAGED_ITK_SOURCE_BUILD_PATH "${CMAKE_BINARY_DIR}/Source")
SET(MANAGED_ITK_SOURCE_COMMON_BUILD_PATH "${MANAGED_ITK_SOURCE_BUILD_PATH}/Common")
SET(MANAGED_ITK_SOURCE_MODULES_BUILD_PATH "${MANAGED_ITK_SOURCE_BUILD_PATH}/Modules")
SET(MANAGED_ITK_SOURCE_REFERENCES_BUILD_PATH "${MANAGED_ITK_SOURCE_BUILD_PATH}/References")

# Setup some cached variables
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Single output directory for building all libraries." FORCE)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Single output directory for building all executables." FORCE)
SET(MANAGED_ITK_ASSEMBLY_PREFIX "ManagedITK" CACHE STRING "The prefix for the assembly name.")

# Setup various useful source and testing paths
SET(MANAGED_ITK_SOURCE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_CFG_INTDIR})
SET(MANAGED_ITK_TESTING_BUILD_PATH ${CMAKE_BINARY_DIR}/Testing/Temporary)

# Construct VXL/VNL includes
SET(MANAGED_ITK_VXL_INCLUDE_DIRS
    ${ITK_SOURCE_DIR}/Utilities/vxl
    ${ITK_SOURCE_DIR}/Utilities/vxl/core
    ${ITK_SOURCE_DIR}/Utilities/vxl/core/vnl
    ${ITK_SOURCE_DIR}/Utilities/vxl/vcl)

# Set dependent libraries
SET(VXL_NUMERICS_LIBRARIES itkvnl itkvnl_algo)
SET(MANAGED_ITK_LIBRARIES
    ITKIO
    ITKCommon
    ITKNumerics
    ITKBasicFilters
    ITKSpatialObject
    ITKMetaIO
    ITKStatistics
    ITKQuadEdgeMesh
    itksys
    ${VXL_NUMERICS_LIBRARIES}
)

# Set the USE File
SET(MANAGED_ITK_USE_FILE "${CMAKE_SOURCE_DIR}/UseManagedITK.cmake")

# Add Source
SUBDIRS(Source)

# Configure finish batch file
CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/FinishCMake.bat.in
                ${CMAKE_BINARY_DIR}/FinishCMake.bat
                @ONLY )

# Configure project config file
CONFIGURE_FILE( ${CMAKE_SOURCE_DIR}/ManagedITKConfig.cmake.in
                ${CMAKE_BINARY_DIR}/ManagedITKConfig.cmake
                @ONLY )
