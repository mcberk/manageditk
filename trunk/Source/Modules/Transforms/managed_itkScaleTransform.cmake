WRAP_CLASS("itk::ScaleTransform")

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
  
  BEGIN_MANAGED_PROPERTY("Scale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the scaling factors for each dimension.")
    SET(MANAGED_PROPERTY_TYPE      "array<double>^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedFixedArray< double, NativeType::SpaceDimension >( m_PointerToNative->GetScale() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetScale( itk::ManagedTypes::ToNativeFixedArray< double, NativeType::SpaceDimension >(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()


WRAP_CLASS("itk::ScaleLogarithmicTransform")

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

  BEGIN_MANAGED_PROPERTY("Scale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the scaling factors for each dimension.")
    SET(MANAGED_PROPERTY_TYPE      "array<double>^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedFixedArray< double, NativeType::SpaceDimension >( m_PointerToNative->GetScale() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetScale( itk::ManagedTypes::ToNativeFixedArray< double, NativeType::SpaceDimension >(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
