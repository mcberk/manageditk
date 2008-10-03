WRAP_CLASS("itk::ShiftScaleImageFilter")

  # Create rescale filters from every scalar type to every scalar type.
  # Force UC and UL types.
  UNIQUE(to_types "UC;${WRAP_ITK_SCALAR}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${WRAP_ITK_SCALAR};UL" "${to_types}")
  
  BEGIN_MANAGED_PROPERTY("Shift" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the amount to Shift each Pixel. The shift is followed by a Scale.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetShift() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetShift( static_cast<NativeType::RealType>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Scale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the amount to Scale each Pixel. The Scale is applied after the Shift.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetScale() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetScale( static_cast<NativeType::RealType>(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
