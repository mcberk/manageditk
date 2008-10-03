WRAP_CLASS("itk::NotImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("CanRunInPlace" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get if the filter can run in place. To do so, the filter's first input and output must have the same dimension and pixel type. This property can be used in conjunction with InPlace to determine whether a particular use of the filter is really running in place. Some filters may be able to optimize their operation if the InPlace is true and CanRunInPlace is true.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->CanRunInPlace();")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("InPlace" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the filter will run in place. In place operation can be turned on and off. This only has an effect when the input and output image type match.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetInPlace();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInPlace( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
