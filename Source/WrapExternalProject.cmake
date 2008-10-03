
################################################################################
MACRO(BEGIN_MANAGED_WRAP_EXTERNAL_PROJECT group_name)
# Setup for wrapping an external project.
# -----------------------------------------------------------------------------
# INPUTS:
# group_name: the name of the groupping this project belongs to
# -----------------------------------------------------------------------------

  # Begin a group
  BEGIN_MODULE_GROUP(${group_name})

  # Construct the default output location
  SET(MANAGED_WRAPPER_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}")

ENDMACRO(BEGIN_MANAGED_WRAP_EXTERNAL_PROJECT)

################################################################################
MACRO(END_MANAGED_WRAP_EXTERNAL_PROJECT)
# Complete the wrapping of an external project.
# -----------------------------------------------------------------------------

  # Get a list of all the cmake files
  FILE(GLOB managed_cmake_files "${CMAKE_CURRENT_SOURCE_DIR}/managed_*.cmake")

  # Include each managed wrap file
  FOREACH(file ${managed_cmake_files})
    INCLUDE(${file})
  ENDFOREACH(file)
  
  # End the groups
  END_MODULE_GROUP()

  # Configure final batch file
  CONFIGURE_FILE( "${MANAGED_ITK_CMAKE_PATH}/FinishCMake.bat.in"
                  "${CMAKE_BINARY_DIR}/FinishCMake.bat"
                  @ONLY )

ENDMACRO(END_MANAGED_WRAP_EXTERNAL_PROJECT)
