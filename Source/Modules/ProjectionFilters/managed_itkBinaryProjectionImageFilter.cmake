WRAP_CLASS("itk::BinaryProjectionImageFilter")
  WRAP_IMAGE_FILTER_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("ProjectionDimension" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the direction in which to accumulate the data. It must be set before calling Update() on the filter. Defaults to the last dimension.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetProjectionDimension();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetProjectionDimension( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("ForegroundValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value in the image to consider as 'on'. Defaults to maximum value of PixelType.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputPixelType>( m_PointerToNative->GetForegroundValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetForegroundValue( itk::ManagedTypes::ToNativePixel<NativeType::InputPixelType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("BackgroundValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value used as 'off'. Defaults to NumericTraits<PixelType>::NonpositiveMin().")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetBackgroundValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetBackgroundValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
