WRAP_CLASS("itk::VectorShiftScaleImageFilter")

  # Create casts between vector types
  UNIQUE(types "${WRAP_ITK_FIXED_VECTOR}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${types}" "${types}")
  UNIQUE(types "${WRAP_ITK_COV_VECTOR}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${types}" "${types}")

  BEGIN_MANAGED_PROPERTY("Shift" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the amount to Shift each pixel component. The shift is followed by a Scale.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetShift() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetShift( static_cast<NativeType::RealType>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Scale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the amount to Scale each pixel component. The Scale is applied after the Shift.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetScale() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetScale( static_cast<NativeType::RealType>(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
