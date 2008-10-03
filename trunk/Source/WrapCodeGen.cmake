
MACRO(BEGIN_MANAGED_METHOD method_name)
# Constructs the managed method signature.
# -----------------------------------------------------------------------------
# INPUTS:
# method_name: the name of the method to create.
# interface: ON to make the method extend the interface, OFF to not extend.
# -----------------------------------------------------------------------------
# OUTPUTS:
# MANAGED_METHOD_NAME: the name of the current method.
# -----------------------------------------------------------------------------

  # Setup the macro variables
  SET(AT "@")
  SET(MANAGED_METHOD_NAME ${method_name})
  SET(MANAGED_METHOD_INTERFACE ON)
  SET(MANAGED_METHOD_SUMMARY )
  SET(MANAGED_METHOD_RETURNS )
  SET(MANAGED_METHOD_RETURN_TYPE )
  SET(MANAGED_METHOD_PARAMS )
  SET(MANAGED_METHOD_TYPE_BODY )
  SET(MANAGED_METHOD_WRAPPER_BODY )
  #SET(MANAGED_PRIVATE_VARIABLES )

  SET(arg1 ${ARGV1})

ENDMACRO(BEGIN_MANAGED_METHOD)


MACRO(END_MANAGED_METHOD)
# Constructs the unmanaged and managed method signature.
# The outputs texts must be configured to replace @variables@.
# -----------------------------------------------------------------------------
# OUTPUTS:
#  MANAGED_METHODS_TYPE_CONFIG: the method code block with the new method appended.
#  MANAGED_METHODS_WRAPPER_CONFIG: the method code block (for the wrapper class).
#  MANAGED_METHODS_INTERFACE_CONFIG: the interface prototype with the new method appended.
# -----------------------------------------------------------------------------

  # Prepare method for type classes (eg. "IUC2IUC2", "F3F2", etc.)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_METHOD_SUMMARY}</summary>\n")
  IF(DEFINED MANAGED_METHOD_DOC_RETURNS)
    SET(text "${text}\t///<returns>${MANAGED_METHOD_RETURNS}</returns>\n")
  ENDIF(DEFINED MANAGED_METHOD_DOC_RETURNS)
  IF(MANAGED_METHOD_INTERFACE)
    SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} ) = I${MANAGED_BASE_NAME}::${MANAGED_METHOD_NAME}\n")
  ELSE(MANAGED_METHOD_INTERFACE)
    SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} )\n")
  ENDIF(MANAGED_METHOD_INTERFACE)
  SET(text "${text}\t{\n")
  SET(text "${text}\t\t${MANAGED_METHOD_TYPE_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_METHODS_TYPE_CONFIG "${MANAGED_METHODS_TYPE_CONFIG}${text}")

  # Prepare method of wrapper classes (the wrapper around the type classes)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_METHOD_SUMMARY}</summary>\n")
  IF(DEFINED MANAGED_METHOD_DOC_RETURNS)
    SET(text "${text}\t///<returns>${MANAGED_METHOD_RETURNS}</returns>\n")
  ENDIF(DEFINED MANAGED_METHOD_DOC_RETURNS)
  IF(MANAGED_METHOD_INTERFACE)
    SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} ) = I${MANAGED_BASE_NAME}::${MANAGED_METHOD_NAME}\n")
  ELSE(MANAGED_METHOD_INTERFACE)
    SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} )\n")
  ENDIF(MANAGED_METHOD_INTERFACE)
  SET(text "${text}\t{\n")
  SET(text "${text}\t\tI${MANAGED_BASE_NAME}^ iInstance = safe_cast<I${MANAGED_BASE_NAME}^>(this->m_Instance);\n")
  SET(text "${text}\t\t${MANAGED_METHOD_WRAPPER_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_METHODS_WRAPPER_CONFIG "${MANAGED_METHODS_WRAPPER_CONFIG}${text}")

   # Prepare method signatures for interface
  SET(MANAGED_METHODS_INTERFACE_CONFIG "${MANAGED_METHODS_INTERFACE_CONFIG}\n\t${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} );")

ENDMACRO(END_MANAGED_METHOD)


MACRO(BEGIN_MANAGED_METHOD_OVERRIDE method_name)
# Constructs the managed method signature.
# -----------------------------------------------------------------------------
# INPUTS:
# method_name: the name of the method to create.
# -----------------------------------------------------------------------------
# OUTPUTS:
# MANAGED_METHOD_NAME: the name of the current method.
# -----------------------------------------------------------------------------

  # Setup the macro variables
  SET(AT "@")
  SET(MANAGED_METHOD_NAME ${method_name})
  SET(MANAGED_METHOD_SUMMARY )
  SET(MANAGED_METHOD_RETURNS )
  SET(MANAGED_METHOD_RETURN_TYPE )
  SET(MANAGED_METHOD_PARAMS )
  SET(MANAGED_METHOD_TYPE_BODY )
  SET(MANAGED_METHOD_WRAPPER_BODY )

  SET(arg1 ${ARGV1})

ENDMACRO(BEGIN_MANAGED_METHOD_OVERRIDE)


MACRO(END_MANAGED_METHOD_OVERRIDE)
# Constructs the unmanaged and managed method signature.
# The outputs texts must be configured to replace @variables@.
# -----------------------------------------------------------------------------
# OUTPUTS:
#  MANAGED_METHODS_TYPE_CONFIG: the method code block with the new method appended.
#  MANAGED_METHODS_WRAPPER_CONFIG: the method code block (for the wrapper class).
# -----------------------------------------------------------------------------

  # Prepare method for type classes (eg. "IUC2IUC2", "F3F2", etc.)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_METHOD_SUMMARY}</summary>\n")
  IF(DEFINED MANAGED_METHOD_DOC_RETURNS)
    SET(text "${text}\t///<returns>${MANAGED_METHOD_RETURNS}</returns>\n")
  ENDIF(DEFINED MANAGED_METHOD_DOC_RETURNS)
  SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} ) override\n")
  SET(text "${text}\t{\n")
  SET(text "${text}\t\t${MANAGED_METHOD_TYPE_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_METHODS_TYPE_CONFIG "${MANAGED_METHODS_TYPE_CONFIG}${text}")

  # Prepare method of wrapper classes (the wrapper around the type classes)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_METHOD_SUMMARY}</summary>\n")
  IF(DEFINED MANAGED_METHOD_DOC_RETURNS)
    SET(text "${text}\t///<returns>${MANAGED_METHOD_RETURNS}</returns>\n")
  ENDIF(DEFINED MANAGED_METHOD_DOC_RETURNS)
  SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} ) override\n")
  SET(text "${text}\t{\n")
  SET(text "${text}\t\t${MANAGED_METHOD_WRAPPER_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_METHODS_WRAPPER_CONFIG "${MANAGED_METHODS_WRAPPER_CONFIG}${text}")

ENDMACRO(END_MANAGED_METHOD_OVERRIDE)


MACRO(BEGIN_MANAGED_METHOD_NO_INTERFACE method_name)
# Constructs the managed method signature.
# -----------------------------------------------------------------------------
# INPUTS:
# method_name: the name of the method to create.
# -----------------------------------------------------------------------------
# OUTPUTS:
# MANAGED_METHOD_NAME: the name of the current method.
# -----------------------------------------------------------------------------

  # Setup the macro variables
  SET(AT "@")
  SET(MANAGED_METHOD_NAME ${method_name})
  SET(MANAGED_METHOD_SUMMARY )
  SET(MANAGED_METHOD_RETURNS )
  SET(MANAGED_METHOD_RETURN_TYPE )
  SET(MANAGED_METHOD_PARAMS )
  SET(MANAGED_METHOD_TYPE_BODY )
  SET(MANAGED_METHOD_WRAPPER_BODY )

  SET(arg1 ${ARGV1})

ENDMACRO(BEGIN_MANAGED_METHOD_NO_INTERFACE)


MACRO(END_MANAGED_METHOD_NO_INTERFACE)
# Constructs the unmanaged and managed method signature.
# The outputs texts must be configured to replace @variables@.
# -----------------------------------------------------------------------------
# OUTPUTS:
#  MANAGED_METHODS_TYPE_CONFIG: the method code block with the new method appended.
#  MANAGED_METHODS_WRAPPER_CONFIG: the method code block (for the wrapper class).
# -----------------------------------------------------------------------------

  # Prepare method for type classes (eg. "IUC2IUC2", "F3F2", etc.)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_METHOD_SUMMARY}</summary>\n")
  IF(DEFINED MANAGED_METHOD_DOC_RETURNS)
    SET(text "${text}\t///<returns>${MANAGED_METHOD_RETURNS}</returns>\n")
  ENDIF(DEFINED MANAGED_METHOD_DOC_RETURNS)
  SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} ) \n")
  SET(text "${text}\t{\n")
  SET(text "${text}\t\t${MANAGED_METHOD_TYPE_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_METHODS_TYPE_CONFIG "${MANAGED_METHODS_TYPE_CONFIG}${text}")

  # Prepare method of wrapper classes (the wrapper around the type classes)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_METHOD_SUMMARY}</summary>\n")
  IF(DEFINED MANAGED_METHOD_DOC_RETURNS)
    SET(text "${text}\t///<returns>${MANAGED_METHOD_RETURNS}</returns>\n")
  ENDIF(DEFINED MANAGED_METHOD_DOC_RETURNS)
  SET(text "${text}\tvirtual ${MANAGED_METHOD_RETURN_TYPE} ${MANAGED_METHOD_NAME} ( ${MANAGED_METHOD_PARAMS} ) \n")
  SET(text "${text}\t{\n")
  SET(text "${text}\t\t${MANAGED_METHOD_WRAPPER_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_METHODS_WRAPPER_CONFIG "${MANAGED_METHODS_WRAPPER_CONFIG}${text}")

ENDMACRO(END_MANAGED_METHOD_NO_INTERFACE)


MACRO(BEGIN_MANAGED_CONSTRUCTOR)
# Constructs the managed constructor signature.
# -----------------------------------------------------------------------------
# INPUTS:
# constructor_name: the name of the method to create.
# -----------------------------------------------------------------------------

  # Setup the macro variables
  SET(AT "@")
  SET(MANAGED_CONSTRUCTOR_SUMMARY )
  SET(MANAGED_CONSTRUCTOR_PARAMS )
  SET(MANAGED_CONSTRUCTOR_TYPE_PARAMS )
  SET(MANAGED_CONSTRUCTOR_WRAPPER_PARAMS )
  SET(MANAGED_CONSTRUCTOR_TYPE_BODY )
  SET(MANAGED_CONSTRUCTOR_WRAPPER_BODY )

ENDMACRO(BEGIN_MANAGED_CONSTRUCTOR)


MACRO(END_MANAGED_CONSTRUCTOR)
# Constructs the unmanaged and managed constructor signature.
# The outputs texts must be configured to replace @variables@.
# -----------------------------------------------------------------------------
# OUTPUTS:
#  MANAGED_CONSTRUCTORS_TYPE_CONFIG: the constructor code block with the new method appended.
#  MANAGED_CONSTRUCTORS_WRAPPER_CONFIG: the constructor code block (for the wrapper class).
# -----------------------------------------------------------------------------

  # The user may have defined the params for both, or the type and wrapper separately.
  # Copy the both to each individual params variable
  IF(NOT DEFINED MANAGED_CONSTRUCTOR_TYPE_PARAMS)
    SET(MANAGED_CONSTRUCTOR_TYPE_PARAMS ${MANAGED_CONSTRUCTOR_PARAMS})
  ENDIF(NOT DEFINED MANAGED_CONSTRUCTOR_TYPE_PARAMS)
  
  IF(NOT DEFINED MANAGED_CONSTRUCTOR_WRAPPER_PARAMS)
    SET(MANAGED_CONSTRUCTOR_WRAPPER_PARAMS ${MANAGED_CONSTRUCTOR_PARAMS})
  ENDIF(NOT DEFINED MANAGED_CONSTRUCTOR_WRAPPER_PARAMS)

  # Prepare constructor for type classes (eg. "IUC2IUC2", "F3F2", etc.)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_CONSTRUCTOR_SUMMARY}</summary>\n")
  SET(text "${text}\t${AT}NAMESPACE${AT}${AT}MANAGED_BASE_NAME${AT}_${AT}MANGLED_SUFFIX${AT} ( ${MANAGED_CONSTRUCTOR_TYPE_PARAMS} ) : ${AT}MANAGED_SUBCLASS${AT}( )\n")
  SET(text "${text}\t{\n")
  SET(text "${text}\t\t${MANAGED_CONSTRUCTOR_TYPE_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_CONSTRUCTORS_TYPE_CONFIG "${MANAGED_CONSTRUCTORS_TYPE_CONFIG}${text}")

  # Prepare constructor for wrapper classes (the wrapper around the type classes)
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_CONSTRUCTOR_SUMMARY}</summary>\n")
  SET(text "${text}\t${AT}NAMESPACE${AT}${AT}MANAGED_BASE_NAME${AT} ( ${MANAGED_CONSTRUCTOR_WRAPPER_PARAMS} ) : ${AT}MANAGED_SUBCLASS${AT}( )\n")
  SET(text "${text}\t{\n")
  SET(text "${text}\t\t${MANAGED_CONSTRUCTOR_WRAPPER_BODY}\n")
  SET(text "${text}\t}\n")
  SET(MANAGED_CONSTRUCTORS_WRAPPER_CONFIG "${MANAGED_CONSTRUCTORS_WRAPPER_CONFIG}${text}")

ENDMACRO(END_MANAGED_CONSTRUCTOR)


MACRO(BEGIN_MANAGED_PROPERTY property_name)
# Constructs the unmanaged and managed method signature.
# -----------------------------------------------------------------------------
# INPUTS:
# property_name: the name of the property to wrap.
# [GET|SET|GETSET]: a flag indicating the combinations of get, set or both.
# -----------------------------------------------------------------------------

  # Setup the macro variables
  SET(AT "@")
  SET(MANAGED_PROPERTY_NAME ${property_name})
  SET(MANAGED_PROPERTY_SUMMARY )
  SET(MANAGED_PROPERTY_TYPE )
  SET(MANAGED_PROPERTY_DESC )
  SET(MANAGED_PROPERTY_GET_BODY )
  SET(MANAGED_PROPERTY_SET_BODY )
  SET(MANAGED_PROPERTY_WRAPPER_GET_BODY )
  SET(MANAGED_PROPERTY_WRAPPER_SET_BODY )

  SET(MANAGED_PROPERTY_GET )
  SET(MANAGED_PROPERTY_SET )
  SET(MANAGED_PROPERTY_GETSET )

  IF("${ARGV1}" STREQUAL "GET")
    SET(MANAGED_PROPERTY_GET "GET")
  ENDIF("${ARGV1}" STREQUAL "GET")

  IF("${ARGV1}" STREQUAL "SET")
    SET(MANAGED_PROPERTY_SET "SET")
  ENDIF("${ARGV1}" STREQUAL "SET")

  IF("${ARGV1}" STREQUAL "GETSET")
    SET(MANAGED_PROPERTY_GETSET "GETSET")
  ENDIF("${ARGV1}" STREQUAL "GETSET")

ENDMACRO(BEGIN_MANAGED_PROPERTY)


MACRO(END_MANAGED_PROPERTY)
# Constructs the unmanaged and managed property accessor and mutator signature.
# The outputs texts must be configured to replace @variables@.
# -----------------------------------------------------------------------------
# OUTPUTS:
# MANAGED_PROPERTIES_TYPE_CONFIG:
# MANAGED_PROPERTIES_WRAPPER_CONFIG:
# MANAGED_PROPERTIES_INTERFACE_CONFIG:
# -----------------------------------------------------------------------------

  # Prepare property for type classes -----------------------------------------
  # Property header
  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_PROPERTY_SUMMARY}</summary>\n")
  SET(text "${text}\tproperty ${MANAGED_PROPERTY_TYPE} ${MANAGED_PROPERTY_NAME}\n")
  SET(text "${text}\t{\n")

  # GET
  IF(DEFINED MANAGED_PROPERTY_GET OR DEFINED MANAGED_PROPERTY_GETSET)
    SET(text "${text}\t\tvirtual ${MANAGED_PROPERTY_TYPE} get()\n")
    SET(text "${text}\t\t{\n")
    SET(text "${text}\t\t\t${MANAGED_PROPERTY_GET_BODY}\n")
    SET(text "${text}\t\t}\n")
  ENDIF(DEFINED MANAGED_PROPERTY_GET OR DEFINED MANAGED_PROPERTY_GETSET)

  # SET
  IF(DEFINED MANAGED_PROPERTY_SET OR DEFINED MANAGED_PROPERTY_GETSET)
    SET(text "${text}\t\tvirtual void set ( ${MANAGED_PROPERTY_TYPE} value )\n")
    SET(text "${text}\t\t{\n")
    SET(text "${text}\t\t\t${MANAGED_PROPERTY_SET_BODY}\n")
    SET(text "${text}\t\t}\n")
  ENDIF(DEFINED MANAGED_PROPERTY_SET OR DEFINED MANAGED_PROPERTY_GETSET)
  
  # Property footer
  SET(text "${text}\t}\n")
  SET(MANAGED_PROPERTIES_TYPE_CONFIG "${MANAGED_PROPERTIES_TYPE_CONFIG}${text}")

  # Prepare property for wrapper class ---------------------------------------
  IF(NOT DEFINED MANAGED_PROPERTY_WRAPPER_GET_BODY)
    SET(MANAGED_PROPERTY_WRAPPER_GET_BODY "return iInstance->${MANAGED_PROPERTY_NAME};")
  ENDIF(NOT DEFINED MANAGED_PROPERTY_WRAPPER_GET_BODY)

  IF(NOT DEFINED MANAGED_PROPERTY_WRAPPER_SET_BODY)
    SET(MANAGED_PROPERTY_WRAPPER_SET_BODY "iInstance->${MANAGED_PROPERTY_NAME} = value;")
  ENDIF(NOT DEFINED MANAGED_PROPERTY_WRAPPER_SET_BODY)

  SET(text )
  SET(text "${text}\n")
  SET(text "${text}\t///<summary>${MANAGED_PROPERTY_SUMMARY}</summary>\n")
  SET(text "${text}\t[ComponentModel::Browsable(true)]\n")
  SET(text "${text}\t[ComponentModel::Description(\"${MANAGED_PROPERTY_SUMMARY}\")]\n")
  SET(text "${text}\tproperty ${MANAGED_PROPERTY_TYPE} ${MANAGED_PROPERTY_NAME}\n")
  SET(text "${text}\t{\n")

  # GET
  IF(DEFINED MANAGED_PROPERTY_GET OR DEFINED MANAGED_PROPERTY_GETSET)
    SET(text "${text}\t\tvirtual ${MANAGED_PROPERTY_TYPE} get()\n")
    SET(text "${text}\t\t{\n")
    SET(text "${text}\t\t\tI${MANAGED_BASE_NAME}^ iInstance = safe_cast<I${MANAGED_BASE_NAME}^>(this->m_Instance);\n")
    SET(text "${text}\t\t\t${MANAGED_PROPERTY_WRAPPER_GET_BODY}\n")
    SET(text "${text}\t\t}\n")
  ENDIF(DEFINED MANAGED_PROPERTY_GET OR DEFINED MANAGED_PROPERTY_GETSET)

  # SET
  IF(DEFINED MANAGED_PROPERTY_SET OR DEFINED MANAGED_PROPERTY_GETSET)
    SET(text "${text}\t\tvirtual void set ( ${MANAGED_PROPERTY_TYPE} value )\n")
    SET(text "${text}\t\t{\n")
    SET(text "${text}\t\t\tI${MANAGED_BASE_NAME}^ iInstance = safe_cast<I${MANAGED_BASE_NAME}^>(this->m_Instance);\n")
    SET(text "${text}\t\t\t${MANAGED_PROPERTY_WRAPPER_SET_BODY}\n")
    SET(text "${text}\t\t}\n")
  ENDIF(DEFINED MANAGED_PROPERTY_SET OR DEFINED MANAGED_PROPERTY_GETSET)
  
  # Property footer
  SET(text "${text}\t}\n")
  SET(MANAGED_PROPERTIES_WRAPPER_CONFIG "${MANAGED_PROPERTIES_WRAPPER_CONFIG}${text}")
  
  # Prepare property for interface -----------------------------------------
  IF(DEFINED MANAGED_PROPERTY_GET)
    SET(MANAGED_PROPERTIES_INTERFACE_CONFIG "${MANAGED_PROPERTIES_INTERFACE_CONFIG}\n\tproperty ${MANAGED_PROPERTY_TYPE} ${MANAGED_PROPERTY_NAME} { ${MANAGED_PROPERTY_TYPE} get(); }")
  ENDIF(DEFINED MANAGED_PROPERTY_GET)

  IF(DEFINED MANAGED_PROPERTY_SET)
    SET(MANAGED_PROPERTIES_INTERFACE_CONFIG "${MANAGED_PROPERTIES_INTERFACE_CONFIG}\n\tproperty ${MANAGED_PROPERTY_TYPE} ${MANAGED_PROPERTY_NAME} { void set( ${MANAGED_PROPERTY_TYPE} value ); }")
  ENDIF(DEFINED MANAGED_PROPERTY_SET)

  IF(DEFINED MANAGED_PROPERTY_GETSET)
    SET(MANAGED_PROPERTIES_INTERFACE_CONFIG "${MANAGED_PROPERTIES_INTERFACE_CONFIG}\n\tproperty ${MANAGED_PROPERTY_TYPE} ${MANAGED_PROPERTY_NAME} { ${MANAGED_PROPERTY_TYPE} get(); void set( ${MANAGED_PROPERTY_TYPE} value ); }")
  ENDIF(DEFINED MANAGED_PROPERTY_GETSET)

ENDMACRO(END_MANAGED_PROPERTY)
