# WindowedSincInterpolateImageFunction with CosineWindowFunction
WRAP_CLASS("itk::CosineWindowedSincInterpolateImageFunction")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})
      FOREACH(r RANGE 4 5)
        WRAP_TEMPLATE("${ITKM_I${t}${d}}R${r}" "${ITKT_I${t}${d}},${r}")
      ENDFOREACH(r)
    ENDFOREACH(t)
  ENDFOREACH(d)

END_WRAP_CLASS()

# WindowedSincInterpolateImageFunction with HammingWindowFunction
WRAP_CLASS("itk::HammingWindowedSincInterpolateImageFunction")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})
      FOREACH(r RANGE 4 5)
        WRAP_TEMPLATE("${ITKM_I${t}${d}}R${r}" "${ITKT_I${t}${d}},${r}")
      ENDFOREACH(r)
    ENDFOREACH(t)
  ENDFOREACH(d)

END_WRAP_CLASS()

# WindowedSincInterpolateImageFunction with LanczosWindowFunction
WRAP_CLASS("itk::LanczosWindowedSincInterpolateImageFunction")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})
      FOREACH(r RANGE 4 5)
        WRAP_TEMPLATE("${ITKM_I${t}${d}}R${r}" "${ITKT_I${t}${d}},${r}")
      ENDFOREACH(r)
    ENDFOREACH(t)
  ENDFOREACH(d)

END_WRAP_CLASS()

# WindowedSincInterpolateImageFunction with WelchWindowFunction
WRAP_CLASS("itk::WelchWindowedSincInterpolateImageFunction")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageFunction_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})
      FOREACH(r RANGE 4 5)
        WRAP_TEMPLATE("${ITKM_I${t}${d}}R${r}" "${ITKT_I${t}${d}},${r}")
      ENDFOREACH(r)
    ENDFOREACH(t)
  ENDFOREACH(d)

END_WRAP_CLASS()
