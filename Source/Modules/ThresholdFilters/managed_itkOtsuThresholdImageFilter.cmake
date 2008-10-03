WRAP_CLASS("itk::OtsuThresholdImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("OutsideValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the 'outside' value.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetOutsideValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOutsideValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("InsideValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the 'inside' value.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetInsideValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInsideValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("NumberOfHistogramBins" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of histogram bins. The default is 128.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfHistogramBins();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfHistogramBins( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Threshold" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the computed threshold.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputPixelType>( m_PointerToNative->GetThreshold() );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
