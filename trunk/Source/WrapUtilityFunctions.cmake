################################################################################
# Macros to manage the grouping of wrapped classes.
################################################################################

MACRO(BEGIN_MODULE_GROUP group_name)
  # Begins a group.
  SET(GROUP ${group_name})
  SET(NAMESPACE "itk")
  SET(LIBRARY_FILES )
  SET(MANAGED_DEPENDENCIES )
  SET(MANAGED_WRAPPER_OUTPUT "${MANAGED_ITK_SOURCE_MODULES_BUILD_PATH}/${GROUP}")
  SET(MANAGED_WRAPPER_INPUT "${MANAGED_ITK_SOURCE_MODULES_PATH}/${GROUP}")
ENDMACRO(BEGIN_MODULE_GROUP)

MACRO(END_MODULE_GROUP)
  # Ends a group and creates the library.
  INCLUDE_DIRECTORIES( BEFORE
                       ${CMAKE_BINARY_DIR}
                       ${CMAKE_SOURCE_DIR}
                       ${MANAGED_WRAPPER_INPUT}
                       ${MANAGED_WRAPPER_OUTPUT}
                       ${MANAGED_ITK_SOURCE_BUILD_PATH}
                       ${MANAGED_ITK_SOURCE_COMMON_BUILD_PATH}
                       ${MANAGED_ITK_SOURCE_MODULES_BUILD_PATH}
                       ${MANAGED_ITK_VXL_INCLUDE_DIRS}
                        )
  ADD_LIBRARY( ${MANAGED_ITK_ASSEMBLY_PREFIX}.${GROUP} SHARED
               ${LIBRARY_FILES}
               ${MANAGED_ITK_SOURCE_COMMON_PATH}/AssemblyInfo.cpp )

  IF (NOT EXTERNAL_MANAGED_ITK_PROJECT)
    ADD_DEPENDENCIES(${MANAGED_ITK_ASSEMBLY_PREFIX}.${GROUP} ${MANAGED_ITK_ASSEMBLY_PREFIX}.Common)
  ENDIF (NOT EXTERNAL_MANAGED_ITK_PROJECT)

  IF (DEFINED MANAGED_DEPENDENCIES)
    ADD_DEPENDENCIES(${MANAGED_ITK_ASSEMBLY_PREFIX}.${GROUP} ${MANAGED_DEPENDENCIES})
  ENDIF (DEFINED MANAGED_DEPENDENCIES)

  TARGET_LINK_LIBRARIES( ${MANAGED_ITK_ASSEMBLY_PREFIX}.${GROUP}
                         ${ITK_LIBRARIES}
                         ${MANAGED_ITK_LIBRARIES}
                         ${WRAPPER_LINK_LIBRARIES} )

ENDMACRO(END_MODULE_GROUP)

MACRO(INCLUDE_MODULE_FILES)
  # Includes all the *.cmake files in this group directory.
  FILE(GLOB managed_cmake_files "${MANAGED_WRAPPER_INPUT}/managed_*.cmake")
  FOREACH(file ${managed_cmake_files})
    INCLUDE(${file})
  ENDFOREACH(file)
ENDMACRO(INCLUDE_MODULE_FILES)

MACRO(ADD_MANAGED_DEPENDENCY dependency)
  SET( MANAGED_DEPENDENCIES ${MANAGED_DEPENDENCIES} ${dependency} )
ENDMACRO(ADD_MANAGED_DEPENDENCY)


################################################################################
# Macros to be used in the wrap_*.cmake files themselves.
# These macros specify that a class is to be wrapped, that certain itk headers
# are to be included, and what specific template instatiations are to be wrapped.
################################################################################

MACRO(WRAP_CLASS class)
  # Wraps the c++ class 'class'. This parameter must be a fully-qualified c++
  # name.
  # The class will be named in the SWIG wrappers as the top-level namespace
  # concatenated to the base class name. E.g. itk::Image -> itkImage or
  # itk::Statistics::Sample -> itkSample.
  # If the top-level namespace is 'itk' amd WRAPPER_AUTO_INCLUDE_HEADERS is ON
  # then the appropriate itk header for this class will be included. Otherwise
  # WRAP_INCLUDE_TYPE should be manually called from the wrap_*.cmake file that calls
  # this macro.
  # Lastly, this class takes an optional 'wrap method' parameter. Valid values are:
  # POINTER, POINTER_WITH_SUPERCLASS, DEREF and SELF.
  #
  # Global vars used: none
  # Global vars modified: WRAPPER_INCLUDE_FILES

  # Clear various global parameters
  SET(AT "@")
  SET(MANGLED_PREFIX )
  SET(MANAGED_TYPE_TEMPLATE )
  SET(MANAGED_WRAPPER_TEMPLATE )
  SET(WRAP_TEMPLATE_LIST )
  SET(MANAGED_INCLUDE_TYPE_FILES )
  SET(MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED_FILES )
  SET(MANAGED_INCLUDE_WRAPPER_FILES )
  SET(MANAGED_SUBCLASS )
  SET(MANAGED_CONSTRUCTORS_TYPE )
  SET(MANAGED_CONSTRUCTORS_WRAPPER )
  SET(MANAGED_CONSTRUCTORS_TYPE_CONFIG )
  SET(MANAGED_CONSTRUCTORS_WRAPPER_CONFIG )
  SET(MANAGED_METHODS_TYPE )
  SET(MANAGED_METHODS_WRAPPER )
  SET(MANAGED_METHODS_TYPE_CONFIG )
  SET(MANAGED_METHODS_WRAPPER_CONFIG )
  SET(MANAGED_METHODS_INTERFACE_CONFIG )
  SET(MANAGED_PROPERTIES_TYPE )
  SET(MANAGED_PROPERTIES_WRAPPER )
  SET(MANAGED_PROPERTIES_INTERFACE )
  SET(MANAGED_PROPERTIES_TYPE_CONFIG )
  SET(MANAGED_PROPERTIES_WRAPPER_CONFIG )
  SET(MANAGED_PROPERTIES_INTERFACE_CONFIG )
  SET(MANAGED_EXTRA_TYPE )
  SET(MANAGED_EXTRA_WRAPPER )
  SET(MANAGED_EXTRA_TYPE_CONFIG )
  SET(MANAGED_EXTRA_WRAPPER_CONFIG )

  # Drop the namespace prefix
  IF("${class}" MATCHES "::")
    # there's at least one namespace in the name
    STRING(REGEX REPLACE ".*::" "" base_name "${class}")
    STRING(REGEX REPLACE "^([^:]*::)?.+" "\\1" top_namespace "${class}")
    STRING(REGEX REPLACE "::" "" top_namespace "${top_namespace}") # drop the :: from the namespace
    SET(swig_name "${top_namespace}${base_name}")
  ELSE("${class}" MATCHES "::")
    # no namespaces
    SET(swig_name "${class}")
  ENDIF("${class}" MATCHES "::")

  # Call the WRAP_NAMED_CLASS macro, including any optional arguments
  WRAP_NAMED_CLASS("${class}" "${swig_name}" ${ARGN})

  # Include the class's header
  WRAP_INCLUDE_TYPE("${swig_name}.h")

  # Remove "ImageFilter" off end of base_name
  IF("${base_name}" MATCHES "ImageFilter")
    # Strip the ImageFilter from the base_name
    STRING(REGEX REPLACE "ImageFilter" "" short_base_name "${base_name}")

    # Set default configuration templates
    SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageFilter_TYPE.cxx.in)
    SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageFilter_WRAPPER.cxx.in)

  ENDIF("${base_name}" MATCHES "ImageFilter")

  # Set global names
  SET(MANAGED_BASE_NAME ${base_name})
  SET(MANAGED_SHORT_BASE_NAME ${short_base_name})

ENDMACRO(WRAP_CLASS)

MACRO(WRAP_INCLUDE_TYPE include_file)
  # Add a header file to the list of files to be #included in the final
  # cxx file. This list is actually processed in WRITE_WRAP_CXX.
  #
  # Global vars used: WRAPPER_INCLUDE_TYPE_FILES
  # Global vars modified: WRAPPER_INCLUDE_TYPE_FILES
  SET(already_included 0)
  FOREACH(included ${MANAGED_INCLUDE_TYPE_FILES})
    IF("${include_file}" STREQUAL "${already_included}")
      SET(already_included 1)
    ENDIF("${include_file}" STREQUAL "${already_included}")
  ENDFOREACH(included)

  IF(NOT already_included)
    # include order IS important. Default values must be before the other ones
    SET(MANAGED_INCLUDE_TYPE_FILES
      ${MANAGED_INCLUDE_TYPE_FILES}
      ${include_file}
    )
  ENDIF(NOT already_included)
ENDMACRO(WRAP_INCLUDE_TYPE)

MACRO(WRAP_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED include_file)
  # Add a header file to the list of files to be #included in the final
  # cxx file. This list is actually processed in WRITE_WRAP_CXX.
  #
  # Global vars used: WRAPPER_INCLUDE_TYPE_FILES
  # Global vars modified: WRAPPER_INCLUDE_TYPE_FILES
  SET(already_included 0)
  FOREACH(included ${MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED_FILES})
    IF("${include_file}" STREQUAL "${already_included}")
      SET(already_included 1)
    ENDIF("${include_file}" STREQUAL "${already_included}")
  ENDFOREACH(included)

  IF(NOT already_included)
    # include order IS important. Default values must be before the other ones
    SET(MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED_FILES
      ${MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED_FILES}
      ${include_file}
    )
  ENDIF(NOT already_included)
ENDMACRO(WRAP_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED)

MACRO(WRAP_INCLUDE_WRAPPER include_file)
  # Add a header file to the list of files to be #included in the final
  # cxx file. This list is actually processed in WRITE_WRAP_CXX.
  #
  # Global vars used: WRAPPER_INCLUDE_WRAPPER_FILES
  # Global vars modified: WRAPPER_INCLUDE_WRAPPER_FILES
  SET(already_included 0)
  FOREACH(included ${MANAGED_INCLUDE_WRAPPER_FILES})
    IF("${include_file}" STREQUAL "${already_included}")
      SET(already_included 1)
    ENDIF("${include_file}" STREQUAL "${already_included}")
  ENDFOREACH(included)

  IF(NOT already_included)
    # include order IS important. Default values must be before the other ones
    SET(MANAGED_INCLUDE_WRAPPER_FILES
      ${MANAGED_INCLUDE_WRAPPER_FILES}
      ${include_file}
    )
  ENDIF(NOT already_included)
ENDMACRO(WRAP_INCLUDE_WRAPPER)

MACRO(WRAP_USE_NAMESPACE_WRAPPER use_namespace_file)
  # Add a namespace to the list of files to be #using in the wrapper
  # cxx file.
  #
  # Global vars used: MANAGED_USE_NAMESPACE_FILES
  # Global vars modified: MANAGED_USE_NAMESPACE_FILES
  SET(already_using 0)
  FOREACH(using_file ${MANAGED_USE_NAMESPACE_FILES})
    IF("${use_namespace_file}" STREQUAL "${already_using}")
      SET(already_using 1)
    ENDIF("${use_namespace_file}" STREQUAL "${already_using}")
  ENDFOREACH(using_file)

  IF(NOT already_using)
    # include order IS important. Default values must be before the other ones
    SET(MANAGED_USE_NAMESPACE_FILES
      ${MANAGED_USE_NAMESPACE_FILES}
      ${use_namespace_file}
    )
  ENDIF(NOT already_using)
ENDMACRO(WRAP_USE_NAMESPACE_WRAPPER)

MACRO(WRAP_NAMED_CLASS class swig_name)
  # Begin the wrapping of a new templated class. The 'class' parameter is a
  # fully-qualified C++ type name, including the namespace. Between WRAP_CLASS
  # and END_WRAP_CLASS various macros should be called to cause certain template
  # instances to be automatically added to the wrap_*.cxx file. END_WRAP_CLASS
  # actually parses through the template instaces that have been recorded and
  # creates the content of that cxx file. MANAGED_WRAP_NON_TEMPLATE_CLASS should be used
  # to create a definition for a non-templated class. (Note that internally,
  # MANAGED_WRAP_NON_TEMPLATE_CLASS eventually calls this macro. This macro should never
  # be called directly for a non-templated class though.)
  #
  # The second parameter of this macro is the name that the class should be given
  # in SWIG (with template definitions providing additional mangled suffixes to this name)
  #
  # Lastly, this class takes an optional 'wrap method' parameter. Valid values are:
  # POINTER and POINTER_WITH_SUPERCLASS.
  # If no parameter is given, the class is simply wrapped as-is. If the parameter
  # is "POINTER" then the class is wrapped and so is the SmartPointer template type
  # that is typedef'd as class::Pointer.
  # If POINTER_WITH_SUPERCLASS is given, class, class::Pointer, class::Superclass,
  # and class::Superclass::Pointer are wrapped. This requires that the class
  # has a typedef'd "Superclass" and that that superclass has Pointer and Self
  # typedefs.
  #
  # Global vars used: none
  # Global vars modified: WRAPPER_CLASS WRAPPER_TEMPLATES WRAPPER_INCLUDE_FILES
  #                       WRAPPER_WRAP_METHOD WRAPPER_SWIG_NAME

  SET(MANAGED_CLASS "${class}")
  SET(MANAGED_SWIG_NAME "${swig_name}")
ENDMACRO(WRAP_NAMED_CLASS)

MACRO(END_WRAP_CLASS)
  # Parse through the list of WRAP_TEMPLATE_LIST set up by the macros at the bottom
  # of this file.
  #
  # Global vars used: WRAPPER_CLASS WRAPPER_TEMPLATES WRAPPER_SWIG_NAME
  # Global vars modified: ?????

  # Create the unmanaged include code
  SET(MANAGED_INCLUDE_TYPE )
  SET(MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED )
  SET(MANAGED_INCLUDE_WRAPPER )
  FOREACH(include_file ${MANAGED_INCLUDE_TYPE_FILES})
    SET(MANAGED_INCLUDE_TYPE "${MANAGED_INCLUDE_TYPE}#include \"${include_file}\"\n")
  ENDFOREACH(include_file)
  FOREACH(include_file ${MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED_FILES})
    SET(MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED "${MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED}#include \"${include_file}\"\n")
  ENDFOREACH(include_file)
  FOREACH(include_file ${MANAGED_INCLUDE_WRAPPER_FILES})
    SET(MANAGED_INCLUDE_WRAPPER "${MANAGED_INCLUDE_WRAPPER}#include \"${include_file}\"\n")
  ENDFOREACH(include_file)
  FOREACH(using_file ${MANAGED_USE_NAMESPACE_FILES})
    SET(MANAGED_USING_NAMESPACE_WRAPPER "${MANAGED_USING_NAMESPACE_WRAPPER}#using <${using_file}.dll>\n")
  ENDFOREACH(using_file)

  # Configure the method and property strings (for types without wrap template list)
  STRING(CONFIGURE "${MANAGED_CONSTRUCTORS_TYPE_CONFIG}" MANAGED_CONSTRUCTORS_TYPE)
  STRING(CONFIGURE "${MANAGED_CONSTRUCTORS_WRAPPER_CONFIG}" MANAGED_CONSTRUCTORS_WRAPPER)
  STRING(CONFIGURE "${MANAGED_METHODS_TYPE_CONFIG}" MANAGED_METHODS_TYPE)
  STRING(CONFIGURE "${MANAGED_METHODS_WRAPPER_CONFIG}" MANAGED_METHODS_WRAPPER)
  STRING(CONFIGURE "${MANAGED_METHODS_INTERFACE_CONFIG}" MANAGED_METHODS_INTERFACE)
  STRING(CONFIGURE "${MANAGED_PROPERTIES_TYPE_CONFIG}" MANAGED_PROPERTIES_TYPE)
  STRING(CONFIGURE "${MANAGED_PROPERTIES_WRAPPER_CONFIG}" MANAGED_PROPERTIES_WRAPPER)
  STRING(CONFIGURE "${MANAGED_PROPERTIES_INTERFACE_CONFIG}" MANAGED_PROPERTIES_INTERFACE)
  STRING(CONFIGURE "${MANAGED_EXTRA_TYPE_CONFIG}" MANAGED_EXTRA_TYPE)
  STRING(CONFIGURE "${MANAGED_EXTRA_WRAPPER_CONFIG}" MANAGED_EXTRA_WRAPPER)

  # the regexp used to get the values separated by a #
  SET(sharp_regexp "([0-9A-Za-z_]*)[ ]*#[ ]*(.*)")
  FOREACH(wrap ${WRAP_TEMPLATE_LIST})
    STRING(REGEX REPLACE "${sharp_regexp}" "\\1" MANGLED_SUFFIX "${wrap}")
    STRING(REGEX REPLACE "${sharp_regexp}" "\\2" TEMPLATE_PARAMS "${wrap}")

    # Get the input and output pixel types from the mangled_suffix
    # ASSUMPTION: This assumes that the mangled_suffix is IXXDIXXD (ie. 1 input and 1 output only)
    SET(mangle_regexp "I([A-Za-z]*)([0-9])*I([A-Za-z]*)([0-9])*")
    STRING(REGEX REPLACE "${mangle_regexp}" "\\1" MANGLED_INPUT_PIXEL "${MANGLED_SUFFIX}")
    STRING(REGEX REPLACE "${mangle_regexp}" "\\2" MANGLED_INPUT_DIMENSION "${MANGLED_SUFFIX}")
    STRING(REGEX REPLACE "${mangle_regexp}" "\\3" MANGLED_OUTPUT_PIXEL "${MANGLED_SUFFIX}")
    STRING(REGEX REPLACE "${mangle_regexp}" "\\4" MANGLED_OUTPUT_DIMENSION "${MANGLED_SUFFIX}")

    # Get the pixel type (for InPlace filters)
    SET(inplace_regexp "I([A-Za-z]*)([0-9])")
    STRING(REGEX REPLACE "${inplace_regexp}" "\\1" MANGLED_PIXEL "${MANGLED_SUFFIX}")
    STRING(REGEX REPLACE "${inplace_regexp}" "\\2" MANGLED_DIMENSION "${MANGLED_SUFFIX}")

    # Configure the type method and property strings (again, this time with wrap templates)
    STRING(CONFIGURE "${MANAGED_CONSTRUCTORS_TYPE_CONFIG}" MANAGED_CONSTRUCTORS_TYPE)
    STRING(CONFIGURE "${MANAGED_METHODS_TYPE_CONFIG}" MANAGED_METHODS_TYPE)
    STRING(CONFIGURE "${MANAGED_METHODS_INTERFACE_CONFIG}" MANAGED_METHODS_INTERFACE)
    STRING(CONFIGURE "${MANAGED_PROPERTIES_TYPE_CONFIG}" MANAGED_PROPERTIES_TYPE)
    STRING(CONFIGURE "${MANAGED_PROPERTIES_INTERFACE_CONFIG}" MANAGED_PROPERTIES_INTERFACE)
    STRING(CONFIGURE "${MANAGED_EXTRA_TYPE_CONFIG}" MANAGED_EXTRA_TYPE)

    # Check if the template exists
    IF(NOT DEFINED MANAGED_TYPE_TEMPLATE)
        MESSAGE(SEND_ERROR "You must define a type template. See 'itkManagedImageToImageFilter_TYPE.cxx.in' for an example.")
    ENDIF(NOT DEFINED MANAGED_TYPE_TEMPLATE)

    IF(NOT DEFINED MANAGED_WRAPPER_TEMPLATE)
        MESSAGE(SEND_ERROR "You must define a wrapper template. See 'itkManagedImageToImageFilter_WRAPPER.cxx.in' for an example.")
    ENDIF(NOT DEFINED MANAGED_WRAPPER_TEMPLATE)

    # Configure the code type file
    # It is expecting the following variables:
    #   @MANAGED_BASE_NAME@, @MANGLED_SUFFIX@, @MANAGED_INCLUDE_TYPE@, @MANAGED_INCLUDE_WRAPPER@,
    #   @MANAGED_SHORT_BASE_NAME@, @MANAGED_CLASS@, @TEMPLATE_PARAMS@
    CONFIGURE_FILE( ${MANAGED_TYPE_TEMPLATE}
                    ${MANAGED_WRAPPER_OUTPUT}/${NAMESPACE}Managed${MANAGED_BASE_NAME}_${MANGLED_SUFFIX}.cxx
                    @ONLY )

    SET( LIBRARY_FILES
         ${LIBRARY_FILES}
         ${MANAGED_WRAPPER_OUTPUT}/${NAMESPACE}Managed${MANAGED_BASE_NAME}_${MANGLED_SUFFIX}.cxx
         )

  ENDFOREACH(wrap)

  # Configure the wrapper file
  # It is expecting the following variables:
  #   @MANAGED_BASE_NAME@, @MANGLED_SUFFIX@, @MANAGED_INCLUDE_BODY@,
  #   @MANAGED_SHORT_BASE_NAME@, @MANAGED_CLASS@, @TEMPLATE_PARAMS@
  CONFIGURE_FILE( ${MANAGED_WRAPPER_TEMPLATE}
                  ${MANAGED_WRAPPER_OUTPUT}/${NAMESPACE}Managed${MANAGED_BASE_NAME}.cxx
                  @ONLY )
  SET( LIBRARY_FILES
      ${LIBRARY_FILES}
      ${MANAGED_WRAPPER_OUTPUT}/${NAMESPACE}Managed${MANAGED_BASE_NAME}.cxx
      )

ENDMACRO(END_WRAP_CLASS)

MACRO(WRAP_NON_TEMPLATE_CLASS class)
  # Wraps the non-templated c++ class 'class'. This parameter must be a
  # fully-qualified c++ name.

  # Clear various global parameters
  SET(AT "@")
  SET(MANAGED_TYPE_TEMPLATE )
  SET(MANAGED_WRAPPER_TEMPLATE )
  SET(WRAP_TEMPLATE_LIST )
  SET(MANAGED_INCLUDE_TYPE_FILES )
  SET(MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED_FILES )
  SET(MANAGED_INCLUDE_WRAPPER_FILES )
  SET(MANAGED_SUBCLASS )
  SET(MANAGED_CONSTRUCTORS_TYPE )
  SET(MANAGED_CONSTRUCTORS_WRAPPER )
  SET(MANAGED_CONSTRUCTORS_TYPE_CONFIG )
  SET(MANAGED_CONSTRUCTORS_WRAPPER_CONFIG )
  SET(MANAGED_METHODS_TYPE )
  SET(MANAGED_METHODS_WRAPPER )
  SET(MANAGED_METHODS_TYPE_CONFIG )
  SET(MANAGED_METHODS_WRAPPER_CONFIG )
  SET(MANAGED_METHODS_INTERFACE_CONFIG )
  SET(MANAGED_PROPERTIES_TYPE )
  SET(MANAGED_PROPERTIES_WRAPPER )
  SET(MANAGED_PROPERTIES_INTERFACE )
  SET(MANAGED_PROPERTIES_TYPE_CONFIG )
  SET(MANAGED_PROPERTIES_WRAPPER_CONFIG )
  SET(MANAGED_PROPERTIES_INTERFACE_CONFIG )
  SET(MANAGED_EXTRA_TYPE )
  SET(MANAGED_EXTRA_WRAPPER )
  SET(MANAGED_EXTRA_TYPE_CONFIG )
  SET(MANAGED_EXTRA_WRAPPER_CONFIG )

  # Drop the namespace prefix
  IF("${class}" MATCHES "::")
    # there's at least one namespace in the name
    STRING(REGEX REPLACE ".*::" "" base_name "${class}")
    STRING(REGEX REPLACE "^([^:]*::)?.+" "\\1" top_namespace "${class}")
    STRING(REGEX REPLACE "::" "" top_namespace "${top_namespace}") # drop the :: from the namespace
    SET(swig_name "${top_namespace}${base_name}")
  ELSE("${class}" MATCHES "::")
    # no namespaces
    SET(swig_name "${class}")
  ENDIF("${class}" MATCHES "::")

  # Call the WRAP_NAMED_CLASS macro, including any optional arguments
  WRAP_NAMED_CLASS("${class}" "${swig_name}" ${ARGN})

  # Include the class's header
  WRAP_INCLUDE_TYPE("${swig_name}.h")

  # Set global names
  SET(MANAGED_BASE_NAME ${base_name})
  SET(MANAGED_SHORT_BASE_NAME ${short_base_name})

ENDMACRO(WRAP_NON_TEMPLATE_CLASS)

MACRO(END_WRAP_NON_TEMPLATE_CLASS)

  # Create the managed include code
  SET(MANAGED_INCLUDE_TYPE )
  SET(MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED )
  SET(MANAGED_INCLUDE_WRAPPER )
  FOREACH(include_file ${MANAGED_INCLUDE_TYPE_FILES})
    SET(MANAGED_INCLUDE_TYPE "${MANAGED_INCLUDE_TYPE}#include \"${include_file}\"\n")
  ENDFOREACH(include_file)
  FOREACH(include_file ${MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED_FILES})
    SET(MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED "${MANAGED_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED}#include \"${include_file}\"\n")
  ENDFOREACH(include_file)
  FOREACH(include_file ${MANAGED_INCLUDE_WRAPPER_FILES})
    SET(MANAGED_INCLUDE_WRAPPER "${MANAGED_INCLUDE_WRAPPER}#include \"${include_file}\"\n")
  ENDFOREACH(include_file)

  # Configure the method and property strings
  STRING(CONFIGURE "${MANAGED_CONSTRUCTORS_TYPE_CONFIG}" MANAGED_CONSTRUCTORS_TYPE)
  STRING(CONFIGURE "${MANAGED_CONSTRUCTORS_WRAPPER_CONFIG}" MANAGED_CONSTRUCTORS_WRAPPER)
  STRING(CONFIGURE "${MANAGED_METHODS_TYPE_CONFIG}" MANAGED_METHODS_TYPE)
  STRING(CONFIGURE "${MANAGED_METHODS_WRAPPER_CONFIG}" MANAGED_METHODS_WRAPPER)
  STRING(CONFIGURE "${MANAGED_METHODS_INTERFACE_CONFIG}" MANAGED_METHODS_INTERFACE)
  STRING(CONFIGURE "${MANAGED_PROPERTIES_TYPE_CONFIG}" MANAGED_PROPERTIES_TYPE)
  STRING(CONFIGURE "${MANAGED_PROPERTIES_WRAPPER_CONFIG}" MANAGED_PROPERTIES_WRAPPER)
  STRING(CONFIGURE "${MANAGED_PROPERTIES_INTERFACE_CONFIG}" MANAGED_PROPERTIES_INTERFACE)
  STRING(CONFIGURE "${MANAGED_EXTRA_TYPE_CONFIG}" MANAGED_EXTRA_TYPE)
  STRING(CONFIGURE "${MANAGED_EXTRA_WRAPPER_CONFIG}" MANAGED_EXTRA_WRAPPER)

  # Check if the template exists
  IF(NOT DEFINED MANAGED_TYPE_TEMPLATE)
      MESSAGE(SEND_ERROR "You must define a non-template type template. See 'itkManagedSingleValuedNonLinearOptimizer_TYPE.cxx.in' for an example.")
  ENDIF(NOT DEFINED MANAGED_TYPE_TEMPLATE)

  # Configure the code type file
  # It is expecting the following variables:
  #   @MANAGED_BASE_NAME@, @MANGLED_SUFFIX@, @MANAGED_INCLUDE_TYPE@, @MANAGED_INCLUDE_WRAPPER@,
  #   @MANAGED_SHORT_BASE_NAME@, @MANAGED_CLASS@, @TEMPLATE_PARAMS@
  CONFIGURE_FILE( ${MANAGED_TYPE_TEMPLATE}
                  ${MANAGED_WRAPPER_OUTPUT}/${NAMESPACE}Managed${MANAGED_BASE_NAME}.cxx
                  @ONLY )

  SET( LIBRARY_FILES
       ${LIBRARY_FILES}
       ${MANAGED_WRAPPER_OUTPUT}/${NAMESPACE}Managed${MANAGED_BASE_NAME}.cxx
       )

ENDMACRO(END_WRAP_NON_TEMPLATE_CLASS)


################################################################################
# Macros which cause one or more template instantiations to be added to the
# WRAPPER_TEMPLATES list. This list is initialized by the macro WRAP_CLASS above,
# and used by the macro END_WRAP_CLASS to produce the wrap_xxx.cxx files with
# the correct templates. These cxx files serve as the CableSwig inputs.
################################################################################

MACRO(WRAP_TEMPLATE name types)
  # This is the fundamental macro for creating a wrapping.
  # 'name' is a mangled suffix to be added to the class name (defined in WRAP_CLASS)
  # to uniquely identify this instantiation.
  # 'types' is a comma-separated list of the template parameters (in C++ form),
  # some common parameters (e.g. for images) are stored in variables by
  # WrapBasicTypes.cmake and WrapITKTypes.cmake.
  #
  # The format of the WRAP_TEMPLATE_LIST is a series of "name # types" strings
  # (because there's no CMake support for nested lists, name and types are
  # separated out from the strings with a regex).
  #
  # Global vars used: WRAP_TEMPLATE_LIST
  # Global vars modified: WRAP_TEMPLATE_LIST

  SET(WRAP_TEMPLATE_LIST ${WRAP_TEMPLATE_LIST} "${name} # ${types}")

ENDMACRO(WRAP_TEMPLATE)

###################################
# Macros for wrapping image filters
###################################

# First, a set of convenience macros for wrapping an image filter with all
# user-selected image types of a given class. These macros take a 'param_count'
# parameter which indicates how many template parameters the current image filter
# takes. The parameters are filled with the exact same image type. To wrap image
# filters which take different image types as different template parameters, use
# WRAP_IMAGE_FILTER_TYPES or CSHARP_WRAP_IMAGE_FILTER_COMBINATIONS.
# These macros also take an optional second parameter which is a "dimensionality
# condition" to restrict the dimensions that theis filter will be instantiated
# for. The condition can either be a single number indicating the one dimension
# allowed, a list of dimensions that are allowed (either as a single ;-delimited
# string or just a set of separate parameters), or something of the form "n+"
# (where n is a number) indicating that instantiations are allowed for dimension
# n and above.
#
# E.g., if only WRAP_unsigned_char is selected and 2- and 3-dimensional images
# are selected, then WRAP_IMAGE_FILTER_USIGN_INT(2)  will create instantiations for
# filter<itk::Image<unsigned char, 2>, itk::Image<unsigned char, 2> >
# and
# filter<itk::Image<unsigned char, 3>, itk::Image<unsigned char, 3> >

MACRO(WRAP_IMAGE_FILTER_ALL param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_ALL}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_ALL)

MACRO(WRAP_IMAGE_FILTER_SCALAR param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_SCALAR}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_SCALAR)

MACRO(WRAP_IMAGE_FILTER_VECTOR param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_VECTOR}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_VECTOR)

MACRO(WRAP_IMAGE_FILTER_USIGN_INT param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_USIGN_INT}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_USIGN_INT)

MACRO(WRAP_IMAGE_FILTER_SIGN_INT param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_SIGN_INT}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_SIGN_INT)

MACRO(WRAP_IMAGE_FILTER_INT param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_INT}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_INT)

MACRO(WRAP_IMAGE_FILTER_BOOL param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_BOOL}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_BOOL)

MACRO(WRAP_IMAGE_FILTER_REAL param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_REAL}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_REAL)

MACRO(WRAP_IMAGE_FILTER_RGB param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_RGB}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_RGB)

MACRO(WRAP_IMAGE_FILTER_RGBA param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_RGBA}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_RGBA)

MACRO(WRAP_IMAGE_FILTER_COLOR param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_COLOR}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_COLOR)

MACRO(WRAP_IMAGE_FILTER_VECTOR param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_VECTOR}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_VECTOR)

MACRO(WRAP_IMAGE_FILTER_COV_VECTOR param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_COV_VECTOR}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_COV_VECTOR)

MACRO(WRAP_IMAGE_FILTER_COMPLEX_REAL param_count)
  WRAP_IMAGE_FILTER("${WRAP_ITK_COMPLEX_REAL}" ${param_count} "${ARGN}")
ENDMACRO(WRAP_IMAGE_FILTER_COMPLEX_REAL)


MACRO(WRAP_IMAGE_FILTER param_types param_count)
  # WRAP_IMAGE_FILTER is a more general macro for wrapping image filters that
  # need one or more image parameters of the same type. The first parameter to this
  # macro is a list of image pixel types for which filter instantiations should be
  # created. The second is a 'param_count' parameter which controls how many image
  # template parameters are created (see above). The optional third parameter is
  # a dimensionality condition (see above also).
  #
  # E.g. WRAP_IMAGE_FILTER("${WRAP_ITK_ALL}" 2) will create template instantiations
  # of the filter for every pixel type that the user has selected.

  SET(have_dim_cond OFF)
  IF(NOT "${ARGN}" STREQUAL "")
    SET(have_dim_cond ON)
  ENDIF(NOT "${ARGN}" STREQUAL "")

  FOREACH(param_type ${param_types})
    SET(param_list "")
    FOREACH(i RANGE 1 ${param_count})
      SET(param_list ${param_list} ${param_type})
    ENDFOREACH(i)
    IF(have_dim_cond)
      WRAP_IMAGE_FILTER_TYPES(${param_list} "${ARGN}")
    ELSE(have_dim_cond)
      WRAP_IMAGE_FILTER_TYPES(${param_list})
    ENDIF(have_dim_cond)
  ENDFOREACH(param_type)

ENDMACRO(WRAP_IMAGE_FILTER)

MACRO(WRAP_IMAGE_FILTER_COMBINATIONS)
  # WRAP_IMAGE_FILTER_COMBINATIONS takes a variable number of parameters. Each
  # parameter is a list of image pixel types. Filter instantiations are created
  # for every combination of different pixel types in different parameters.
  # A dimensionality condition may be optionally specified as the first parameter.
  #
  # E.g. WRAP_IMAGE_FILTER_COMBINATIONS("UC;US" "UC;US") will create:
  # filter<itk::Image<unsigned char, d>, itk::Image<unsigned char, d> >
  # filter<itk::Image<unsigned char, d>, itk::Image<unsigned short, d> >
  # filter<itk::Image<unsigned short, d>, itk::Image<unsigned char, d> >
  # filter<itk::Image<unsigned short, d>, itk::Image<unsigned short, d> >
  # where 'd' is the image dimension, for each selected image dimension.

  # First, store the variable args in real varables, not the macro parameters.
  # Parameters can't be looked up like this: ${ARGV${num}} because they are
  # textually substituted before the macro is evaluated.
  SET(arg0 ${ARGV0})
  SET(arg1 ${ARGV1})
  SET(arg2 ${ARGV2})
  SET(arg3 ${ARGV3})
  SET(arg4 ${ARGV4})
  SET(arg5 ${ARGV5})
  SET(arg6 ${ARGV6})
  SET(arg7 ${ARGV7})
  SET(arg8 ${ARGV8})
  SET(arg9 ${ARGV9})
  DECREMENT(last_arg_number ${ARGC})

  # Now see if we have a dimension condition, and if so, note it and remove it
  # from the list of args that we will process later
  SET(have_dim_cond OFF)
  SET(last_arg "${arg${last_arg_number}}")
  IF("${last_arg}" MATCHES "^[0-9]")
    # We have a dimensionality condition
    SET(have_dim_cond ON)
    DECREMENT(last_arg_number ${last_arg_number})
  ENDIF("${last_arg}" MATCHES "^[0-9]")

  # Build up a list of all of the combinations of all of the elements in each
  # argument. Each combinarion is stored as a #-delimited list of pixel types.
  # The #-delimiter is needed because CMake can't store nested lists.
  # Also note the need to check for empty lists and note invalidity if so.
  SET(all_args_valid ON)
  IF(NOT arg0)
    SET(all_args_valid OFF)
  ELSE(NOT arg0)
    SET(template_combinations ${arg0})
  ENDIF(NOT arg0)

  FOREACH(num RANGE 1 ${last_arg_number})
    SET(types "${arg${num}}")
    IF(NOT types)
      SET(all_args_valid OFF)
    ELSE(NOT types)
      SET(temp "")
      FOREACH(type_list ${template_combinations})
        FOREACH(type ${types})
          SET(temp ${temp} "${type_list}#${type}")
        ENDFOREACH(type)
      ENDFOREACH(type_list)
      SET(template_combinations ${temp})
    ENDIF(NOT types)
  ENDFOREACH(num)

  IF(all_args_valid)
    FOREACH(param_set ${template_combinations})
      # Each param_set is a #-delimited list of pixel types. First thing, we unpack
      # param_set back to a CMake list (;-delimited). Then we instantiate the filter
      # for that combination of image pixel types.
      STRING(REPLACE "#" ";" param_list "${param_set}")
      IF(have_dim_cond)
        WRAP_IMAGE_FILTER_TYPES(${param_list} "${last_arg}")
      ELSE(have_dim_cond)
        WRAP_IMAGE_FILTER_TYPES(${param_list})
      ENDIF(have_dim_cond)
    ENDFOREACH(param_set)
  ENDIF(all_args_valid)
ENDMACRO(WRAP_IMAGE_FILTER_COMBINATIONS)


MACRO(WRAP_IMAGE_FILTER_TYPES)
  # WRAP_IMAGE_FILTER_TYPES creates template instantiations of the current image
  # filter, for all the selected dimensions (or dimensions that meet the optional
  # dimensionality condition). This macro takes a variable number of arguments,
  # which should correspond to the image pixel types of the images in the filter's
  # template parameter list. The optional dimensionality condition should be
  # placed in the first parameter.

  # First, store the variable args in real varables, not the macro parameters.
  # Parameters can't be looked up like this: ${ARGV${num}} because they are
  # textually substituted before the macro is evaluated.
  SET(arg0 ${ARGV0})
  SET(arg1 ${ARGV1})
  SET(arg2 ${ARGV2})
  SET(arg3 ${ARGV3})
  SET(arg4 ${ARGV4})
  SET(arg5 ${ARGV5})
  SET(arg6 ${ARGV6})
  SET(arg7 ${ARGV7})
  SET(arg8 ${ARGV8})
  SET(arg9 ${ARGV9})
  DECREMENT(last_arg_number ${ARGC})

  SET(last_arg "${arg${last_arg_number}}")
  IF("${last_arg}" MATCHES "^[0-9]")
    # We have a dimensionality condition
    FILTER_DIMS(dims ${last_arg})
    DECREMENT(last_arg_number ${last_arg_number})
  ELSE("${last_arg}" MATCHES "^[0-9]")
    SET(dims ${WRAP_ITK_DIMS})
  ENDIF("${last_arg}" MATCHES "^[0-9]")

  FOREACH(d ${dims})
    SET(template_params "")
    SET(mangled_name "")
    SET(comma "") # Don't add a comma before the first template param!
    FOREACH(num RANGE 0 ${last_arg_number})
      SET(type "${arg${num}}")
      IF("${WRAP_ITK_VECTOR}" MATCHES "(^|;)${type}(;|$)")
        # if the type is a vector type with no dimension specified, make the
        # vector dimension match the image dimension.
        SET(type "${type}${d}")
      ENDIF("${WRAP_ITK_VECTOR}" MATCHES "(^|;)${type}(;|$)")
      SET(image_type ${ITKT_I${type}${d}})
      SET(mangle_type ${ITKM_I${type}${d}})
      IF(NOT DEFINED image_type)
        MESSAGE(FATAL_ERROR "Wrapping ${MANAGED_CLASS}: No image type for '${type}' pixels is known (ie. ITKT_I${type}${d} is not defined).")
      ENDIF(NOT DEFINED image_type)

      SET(template_params "${template_params}${comma}${image_type}")
      SET(mangled_name "${mangled_name}${mangle_type}")
      SET(comma ", ") # now add commas after the subsequent template params
    ENDFOREACH(num)
    WRAP_TEMPLATE("${mangled_name}" "${template_params}")
  ENDFOREACH(d)
ENDMACRO(WRAP_IMAGE_FILTER_TYPES)

MACRO(FILTER_DIMS var_name dimension_condition)
  # FILTER_DIMS processes a dimension_condition and returns a list of the dimensions
  # that (a) meet the condition, and (b) were selected to be wrapped. Recall
  # that the condition is either a CMake list of dimensions, or a string of the
  # form "n+" where n is a number.

  IF("${dimension_condition}" MATCHES "^[0-9]+\\+$")
    # The condition is of the form "n+". Make a list of the
    # selected wrapping dims that are >= that number.
    STRING(REGEX REPLACE "^([0-9]+)\\+$" "\\1" min_dim "${dimension_condition}")
    DECREMENT(max_disallowed ${min_dim})
    SET(${var_name} "")
    FOREACH(d ${WRAP_ITK_DIMS})
      IF("${d}" GREATER "${max_disallowed}")
        SET(${var_name} ${${var_name}} ${d})
      ENDIF("${d}" GREATER "${max_disallowed}")
    ENDFOREACH(d)
  ELSE("${dimension_condition}" MATCHES "^[0-9]+\\+$")
    # The condition is just a list of dims. Return the intersection of these
    # dims with the selected ones.
    INTERSECTION(${var_name} "${dimension_condition}" "${WRAP_ITK_DIMS}")
  ENDIF("${dimension_condition}" MATCHES "^[0-9]+\\+$")
ENDMACRO(FILTER_DIMS)
