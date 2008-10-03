WRAP_CLASS("itk::LocalMaximaImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("FullyConnected" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the connectivity used by the algorithm. FullyConnected=False means face connectivity and FullyConnected=True means face+edge+vertex connectivity. The default is FullyConnected=False.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFullyConnected();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFullyConnected( value );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("ForegroundValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value in the output image to consider as 'foreground'. The default is the maximum value of PixelType.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputImagePixelType>( m_PointerToNative->GetForegroundValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetForegroundValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputImagePixelType>( value ) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("BackgroundValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value in the output image to consider as 'background'. The default is the non-positive minimum value of PixelType.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputImagePixelType>( m_PointerToNative->GetBackgroundValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetBackgroundValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputImagePixelType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
