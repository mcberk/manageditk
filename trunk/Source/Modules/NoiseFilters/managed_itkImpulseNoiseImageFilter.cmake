WRAP_CLASS("itk::ImpulseNoiseImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)

  BEGIN_MANAGED_PROPERTY("Probability" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the probability [0,1] that a given voxel will be affected by noise The default is 0.01.")
    SET(MANAGED_PROPERTY_TYPE      "float")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetProbability();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetProbability( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("OutputMinimum" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the output minimum value.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputPixelType>( m_PointerToNative->GetOutputMinimum() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOutputMinimum( itk::ManagedTypes::ToNativePixel<NativeType::InputPixelType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("OutputMaximum" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the output maximum value.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputPixelType>( m_PointerToNative->GetOutputMaximum() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOutputMaximum( itk::ManagedTypes::ToNativePixel<NativeType::InputPixelType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
