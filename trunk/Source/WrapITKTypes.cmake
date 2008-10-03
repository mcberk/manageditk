#------------------------------------------------------------------------------

# define some macro to help creation of types vars

MACRO(WRAP_TYPE class prefix)
   # begin the creation of a type vars
   # call to this macro should be followed by one or several call to WRAP_TEMPLATE()
   # and one call to END_WRAP_TYPE to really create the vars
   SET(WRAP_TEMPLATE_LIST "")
   SET(itk_Wrap_Prefix "${prefix}")
   SET(itk_Wrap_Class "${class}")
ENDMACRO(WRAP_TYPE)

MACRO(END_WRAP_TYPE)
   # create the type vars.
   # must be called after END_WRAP_TYPE
   # Create the vars used for to designe types in all the cmake
   # files. This method ensure all the type names are constructed
   # with the same method
   FOREACH(wrap ${WRAP_TEMPLATE_LIST})
      STRING(REGEX REPLACE "([0-9A-Za-z]*)[ ]*#[ ]*(.*)" "\\1" wrapTpl "${wrap}")
      STRING(REGEX REPLACE "([0-9A-Za-z]*)[ ]*#[ ]*(.*)" "\\2" wrapType "${wrap}")

      SET(ITKT_${itk_Wrap_Prefix}${wrapTpl} "${itk_Wrap_Class}< ${wrapType} >")
      SET(ITKM_${itk_Wrap_Prefix}${wrapTpl} "${itk_Wrap_Prefix}${wrapTpl}")
   ENDFOREACH(wrap)
ENDMACRO(END_WRAP_TYPE)

#------------------------------------------------------------------------------

# now, define types vars
# the result is stored in itk_Wrap_XXX where XXX is the name of the class
# to be wrapped in there own file, most of the time in CommonA

# WRAP_TYPE("itk::Offset" "O")
#   FOREACH(d ${WRAP_ITK_DIMS})
#     WRAP_TEMPLATE("${d}"  "${d}")
#   ENDFOREACH(d)
# END_WRAP_TYPE()
# SET(itk_Wrap_Offset ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::Vector" "V")
  FOREACH(d ${WRAP_ITK_DIMS})
    UNIQUE(wrap_types "${WRAP_ITK_SCALAR};UC;F;D")
    FOREACH(type ${wrap_types})
      WRAP_TEMPLATE("${ITKM_${type}}${d}"  "${ITKT_${type}},${d}")
    ENDFOREACH(type)
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_Vector ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::Vector" "VI")
  FOREACH(d ${WRAP_ITK_DIMS})
    UNIQUE(wrap_types "${WRAP_ITK_SCALAR};UC;F;D")
    FOREACH(type ${wrap_types})
      WRAP_TEMPLATE("${ITKM_${type}}${d}"  "${ITKT_${type}},${d}")
    ENDFOREACH(type)
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_VectorImage ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::CovariantVector" "CV")
  FOREACH(d ${WRAP_ITK_DIMS})
    UNIQUE(wrap_types "${WRAP_ITK_SCALAR};UC;F;D")
    FOREACH(type ${wrap_types})
      WRAP_TEMPLATE("${ITKM_${type}}${d}"  "${ITKT_${type}},${d}")
    ENDFOREACH(type)
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_CovariantVector ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::VariableLengthVector" "VLV")
  # Make a list of all of the selected image pixel types and also uchar
  # (for 8-bit image output)
  UNIQUE(wrap_types "${WRAP_ITK_SCALAR};UC;F")
  FOREACH(type ${wrap_types})
    WRAP_TEMPLATE("${ITKM_${type}}"  "${ITKT_${type}}")
  ENDFOREACH(type)
END_WRAP_TYPE()
SET(itk_Wrap_VariableLengthVector ${WRAP_TEMPLATE_LIST})

# WRAP_TYPE("itk::ContinuousIndex" "CI")
#   FOREACH(d ${WRAP_ITK_DIMS})
#     WRAP_TEMPLATE("${ITKM_F}${d}"  "${ITKT_F},${d}")
#     WRAP_TEMPLATE("${ITKM_D}${d}"  "${ITKT_D},${d}")
#   ENDFOREACH(d)
# END_WRAP_TYPE()
# SET(itk_Wrap_ContinuousIndex ${WRAP_TEMPLATE_LIST})

# WRAP_TYPE("itk::Array" "A")
#   WRAP_TEMPLATE("${ITKM_D}" "${ITKT_D}")
#   WRAP_TEMPLATE("${ITKM_F}" "${ITKT_F}")
# END_WRAP_TYPE()
# SET(itk_Wrap_Array ${WRAP_TEMPLATE_LIST})

# WRAP_TYPE("itk::FixedArray" "FA")
#   UNIQUE(array_sizes "${WRAP_ITK_DIMS};1")
#   # make sure that 1-D FixedArrays are wrapped. Also wrap for each selected
#   # image dimension.
#   # TODO: Do we need fixed arrays for all of these types? For just the selected
#   # pixel types plus some few basic cases? Or just for a basic set of types?
#   FOREACH(d ${array_sizes})
#     WRAP_TEMPLATE("${ITKM_D}${d}"  "${ITKT_D},${d}")
#     WRAP_TEMPLATE("${ITKM_F}${d}"  "${ITKT_F},${d}")
#     WRAP_TEMPLATE("${ITKM_UL}${d}" "${ITKT_UL},${d}")
#     WRAP_TEMPLATE("${ITKM_US}${d}" "${ITKT_US},${d}")
#     WRAP_TEMPLATE("${ITKM_UC}${d}" "${ITKT_UC},${d}")
#     WRAP_TEMPLATE("${ITKM_UI}${d}" "${ITKT_UI},${d}")
#     WRAP_TEMPLATE("${ITKM_SL}${d}" "${ITKT_SL},${d}")
#     WRAP_TEMPLATE("${ITKM_SS}${d}" "${ITKT_SS},${d}")
#     WRAP_TEMPLATE("${ITKM_SC}${d}" "${ITKT_SC},${d}")
#     WRAP_TEMPLATE("${ITKM_B}${d}"  "${ITKT_B},${d}")
#   ENDFOREACH(d)
# END_WRAP_TYPE()
# SET(itk_Wrap_FixedArray ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::RGBPixel" "RGB")
  IF(WRAP_rgb_unsigned_char)
    WRAP_TEMPLATE("${ITKM_UC}" "${ITKT_UC}")
  ENDIF(WRAP_rgb_unsigned_char)

  IF(WRAP_rgb_unsigned_short)
    WRAP_TEMPLATE("${ITKM_US}" "${ITKT_US}")
  ENDIF(WRAP_rgb_unsigned_short)
END_WRAP_TYPE()
SET(itk_Wrap_RGBPixel ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::RGBAPixel" "RGBA")
  IF(WRAP_rgba_unsigned_char)
    WRAP_TEMPLATE("${ITKM_UC}" "${ITKT_UC}")
  ENDIF(WRAP_rgba_unsigned_char)

  IF(WRAP_rgba_unsigned_short)
    WRAP_TEMPLATE("${ITKM_US}" "${ITKT_US}")
  ENDIF(WRAP_rgba_unsigned_short)
END_WRAP_TYPE()
SET(itk_Wrap_RGBAPixel ${WRAP_TEMPLATE_LIST})

# WRAP_TYPE("std::complex" "C")
#   IF(WRAP_complex_float)
#     WRAP_TEMPLATE("${ITKM_F}"  "${ITKT_F}")
#   ENDIF(WRAP_complex_float)
#   IF(WRAP_complex_double)
#     WRAP_TEMPLATE("${ITKM_D}"  "${ITKT_D}")
#   ENDIF(WRAP_complex_double)
# END_WRAP_TYPE()
# SET(itk_Wrap_vcl_complex ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::Image" "I")
  # Make a list of all of the selected image pixel types and also double (for
  # BSplineDeformableTransform), uchar (for 8-bit image output), and ulong
  # (for the watershed and relabel filters).
  UNIQUE(wrap_image_types "${WRAP_ITK_ALL_TYPES};UC;SS;UL;F;D;RGBUC;RGBAUC;VD;CVD;")

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(type ${wrap_image_types})
      IF("${WRAP_ITK_VECTOR};VD;CVD" MATCHES "(^|;)${type}(;|$)")
        # if the type is a vector type with no dimension specified, make the
        # vector dimension match the image dimension.
        SET(type "${type}${d}")
      ENDIF("${WRAP_ITK_VECTOR};VD;CVD" MATCHES "(^|;)${type}(;|$)")

      WRAP_TEMPLATE("${ITKM_${type}}${d}"  "${ITKT_${type}},${d}")
    ENDFOREACH(type)
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_Image ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::VectorImage" "IVI")
  # Make a list of all of the selected image pixel types and also uchar 
  # (for 8-bit image output)
  UNIQUE(wrap_image_types "${WRAP_ITK_SCALAR_NO_BOOL};UC")

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(type ${wrap_image_types})
      WRAP_TEMPLATE("${ITKM_${type}}${d}"  "${ITKT_${type}},${d}")
    ENDFOREACH(type)
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_VectorImage ${WRAP_TEMPLATE_LIST})

# WRAP_TYPE("itk::Point" "P")
#   FOREACH(d ${WRAP_ITK_DIMS})
#     WRAP_TEMPLATE("${ITKM_F}${d}"  "${ITKT_F},${d}")
#     WRAP_TEMPLATE("${ITKM_D}${d}"  "${ITKT_D},${d}")
#   ENDFOREACH(d)
# END_WRAP_TYPE()
# SET(itk_Wrap_Point ${WRAP_TEMPLATE_LIST})

# WRAP_TYPE("itk::LevelSetNode" "LSN")
#   # Only make level set nodes for the selected image pixel types
#   FOREACH(d ${WRAP_ITK_DIMS})
#     FOREACH(type ${WRAP_ITK_SCALAR})
#       WRAP_TEMPLATE("${ITKM_${type}}${d}"  "${ITKT_${type}},${d}")
#     ENDFOREACH(type)
#   ENDFOREACH(d)
# END_WRAP_TYPE()
# SET(itk_Wrap_LevelSetNode ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::BinaryBallStructuringElement" "BBSE")
  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(type ${WRAP_ITK_SCALAR})
      WRAP_TEMPLATE("${ITKM_${type}}${d}"  "${ITKT_${type}},${d}")
    ENDFOREACH(type)
    WRAP_TEMPLATE("${ITKM_B}${d}"  "${ITKT_B},${d}")
  ENDFOREACH(d)
END_WRAP_TYPE()

WRAP_TYPE("itk::FlatStructuringElement" "FSE")
  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}"  "${d}")
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_StructuringElement ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::PolyLineParametricPath" "PLPP")
  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}"  "${d}")
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_PolyLineParametricPath ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::Mesh" "M") # M = Mesh
  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_MESH_PIXELS})
      WRAP_TEMPLATE("${ITKM_${t}}${d}S"
        "${ITKT_${t}},${d},itk::DefaultStaticMeshTraits< ${ITKT_${t}},${d},${d},${ITKT_${t}} >")
      WRAP_TEMPLATE("${ITKM_${t}}${d}D"
        "${ITKT_${t}},${d},itk::DefaultDynamicMeshTraits< ${ITKT_${t}},${d},${d},${ITKT_${t}} >")
    ENDFOREACH(t)
  ENDFOREACH(d)
END_WRAP_TYPE()
WRAP_TYPE("itk::SimplexMesh" "SM") # SM = Simple Mesh
  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_MESH_PIXELS})
      WRAP_TEMPLATE("${ITKM_${t}}${d}S"
        "${ITKT_${t}},${d},itk::DefaultStaticMeshTraits< ${ITKT_${t}},${d},${d},${ITKT_${t}} >")
      WRAP_TEMPLATE("${ITKM_${t}}${d}D"
        "${ITKT_${t}},${d},itk::DefaultDynamicMeshTraits< ${ITKT_${t}},${d},${d},${ITKT_${t}} >")
    ENDFOREACH(t)
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_Mesh ${WRAP_TEMPLATE_LIST})

WRAP_TYPE("itk::SpatialObject" "SO")
  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}"  "${d}")
  ENDFOREACH(d)
END_WRAP_TYPE()
SET(itk_Wrap_SpatialObject ${WRAP_TEMPLATE_LIST})

#------------------------------------------------------------------------------

# set the default include files for the generated wrapper files
SET(WRAPPER_DEFAULT_INCLUDE
  "itkOffset.h"
  "itkVector.h"
  "itkCovariantVector.h"
  "itkContinuousIndex.h"
  "itkArray.h"
  "itkFixedArray.h"
  "itkRGBPixel.h"
  "itkRGBAPixel.h"
  "itkImage.h"
  "itkVectorImage.h"
  "itkVariableLengthVector.h"
  "itkPoint.h"
  "itkLevelSet.h"
  "itkBinaryBallStructuringElement.h"
  "itkFlatStructuringElement.h"
  "itkSpatialObject.h"
  "itkCommand.h"
  "vcl_complex.h"
)

