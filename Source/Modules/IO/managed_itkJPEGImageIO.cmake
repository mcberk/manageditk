WRAP_CLASS("itk::JPEGImageIO")

  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIOBase_WRAPPER.cxx.in)
  SET(WRAP_TEMPLATE_LIST )

  BEGIN_MANAGED_PROPERTY("Quality" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the level of quality for the output images.")
    SET(MANAGED_PROPERTY_TYPE      "int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetQuality();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetQuality( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Progressive" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the progressive value.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetProgressive();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetProgressive( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
