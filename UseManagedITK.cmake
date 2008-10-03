#
# This file sets up include directories, link directories, and
# compiler settings for a project to use ManagedITK.  It should not be
# included directly, but rather through the MANAGED_ITK_USE_FILE setting
# obtained from ManagedITKConfig.cmake.
#

# Configure the compiler flags
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /AI \"@MANAGED_ITK_SOURCE_OUTPUT_PATH@\"")

# Add include directories needed to use ManagedITK.
INCLUDE_DIRECTORIES(BEFORE ${MANAGED_ITK_VXL_INCLUDE_DIRS}
                           ${MANAGED_ITK_SOURCE_PATH}
                           ${MANAGED_ITK_SOURCE_BUILD_PATH}
                           ${MANAGED_ITK_SOURCE_COMMON_PATH}
                           ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}
)

# Add link directories needed to use ManagedITK.
LINK_DIRECTORIES(${MANAGED_ITK_LIBRARY_DIRS})
