WRAP_CLASS("itk::WatershedImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)

  BEGIN_MANAGED_PROPERTY("Threshold" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the input thresholding parameter. Units are a percentage of the maximum depth in the image.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetThreshold( );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetThreshold( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Level" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the flood level for generating the merge tree from the initial segmentation.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetLevel( );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLevel( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
