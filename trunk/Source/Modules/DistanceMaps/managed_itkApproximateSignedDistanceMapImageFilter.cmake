WRAP_CLASS("itk::ApproximateSignedDistanceMapImageFilter")

  # WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("OutsideValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the intensity value representing non-objects objects in the mask.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetOutsideValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOutsideValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("InsideValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the intensity value representing the interior of objects in the mask.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetInsideValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInsideValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
