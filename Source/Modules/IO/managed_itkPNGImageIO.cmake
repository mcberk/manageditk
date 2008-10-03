WRAP_CLASS("itk::PNGImageIO")

  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIOBase_WRAPPER.cxx.in)
  SET(WRAP_TEMPLATE_LIST )

  BEGIN_MANAGED_PROPERTY("CompressionLevel" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the level of compression for the output images. 0-9; 0 = none, 9 = maximum.")
    SET(MANAGED_PROPERTY_TYPE      "int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetCompressionLevel();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetCompressionLevel( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
