WRAP_CLASS("itk::IdentityTransform")
  
  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedTransform_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedTransform_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${ITKM_D}${d}" "${ITKT_D},${d}")
  ENDFOREACH(d)
  
  BEGIN_MANAGED_METHOD("SetIdentity")
    SET(MANAGED_METHOD_SUMMARY         "Set the transform to identity.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetIdentity();")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetIdentity();")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
