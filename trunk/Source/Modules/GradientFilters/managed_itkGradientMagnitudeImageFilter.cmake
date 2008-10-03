WRAP_CLASS("itk::GradientMagnitudeImageFilter")
  
  WRAP_IMAGE_FILTER_SCALAR(2)
  
  BEGIN_MANAGED_PROPERTY("UseImageSpacing" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the filter should use the image spacing.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetUseImageSpacing();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetUseImageSpacing( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
