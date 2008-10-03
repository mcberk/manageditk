WRAP_CLASS("itk::ScaleShiftImageFilter")

  # Create rescale filters from every scalar type to every scalar type.
  # Force UC and UL types.
  UNIQUE(to_types "UC;${WRAP_ITK_SCALAR}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${WRAP_ITK_SCALAR};UL" "${to_types}")
  
  BEGIN_MANAGED_PROPERTY("Shift" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the amount to Shift each pixel. The Shift is applied before the Scale.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetShift() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetShift( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Scale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the amount to Scale each pixel. The Scale is followed by the Shift.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetScale() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetScale( value );")
  END_MANAGED_PROPERTY()

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
