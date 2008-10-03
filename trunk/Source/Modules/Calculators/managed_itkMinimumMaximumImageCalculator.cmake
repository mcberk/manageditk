WRAP_CLASS("itk::MinimumMaximumImageCalculator")

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)
  WRAP_IMAGE_FILTER("UL" 1)

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedCalculator_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedCalculator_WRAPPER.cxx.in)

  BEGIN_MANAGED_METHOD("ComputeMinimum")
    SET(MANAGED_METHOD_SUMMARY         "Only compute the minimum value.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->ComputeMinimum();")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->ComputeMinimum();")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("ComputeMaximum")
    SET(MANAGED_METHOD_SUMMARY         "Only compute the maximum value.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->ComputeMaximum();")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->ComputeMaximum();")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_PROPERTY("Region" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the region over which the values will be computed.")
    SET(MANAGED_PROPERTY_TYPE      "itkImageRegion^")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetRegion( itk::ManagedTypes::ToNativeImageRegion<NativeType::ImageType::ImageDimension>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Minimum" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Gets the minimum intensity value found in the image. NOTE: Only valid after calling Compute() or ComputeMinimum().")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::PixelType>( m_PointerToNative->GetMinimum() );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Maximum" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Gets the maximum intensity value found in the image. NOTE: Only valid after calling Compute() or ComputeMaximum().")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::PixelType>( m_PointerToNative->GetMaximum() );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()

