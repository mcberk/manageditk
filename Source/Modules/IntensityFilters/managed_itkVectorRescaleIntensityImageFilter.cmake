WRAP_CLASS("itk::VectorRescaleIntensityImageFilter")

  # Create casts between vector types
  UNIQUE(types "${WRAP_ITK_FIXED_VECTOR}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${types}" "${types}")
  UNIQUE(types "${WRAP_ITK_COV_VECTOR}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${types}" "${types}")

  BEGIN_MANAGED_PROPERTY("OutputMaximumMagnitude" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the output maximum magnitude value.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputRealType>( m_PointerToNative->GetOutputMaximumMagnitude() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOutputMaximumMagnitude( itk::ManagedTypes::ToNativePixel<NativeType::OutputRealType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
