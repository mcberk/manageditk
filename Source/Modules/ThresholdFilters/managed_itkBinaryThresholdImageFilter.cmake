WRAP_CLASS("itk::BinaryThresholdImageFilter")
  # For all the selected scalar types:
  FOREACH(type ${WRAP_ITK_SCALAR})
    
    # Wrap from that type to itself
    # And wrap from that type to all "smaller" types that are selected.
    # The SMALLER_THAN lists are defined in WrapBasicTypes.cmake. If the list
    # is empty/nonexistant (e.g. in the case of uchar, then WRAP_IMAGE_FILTER_COMBINATIONS
    # will just ignore that).
    UNIQUE(st "${SMALLER_THAN_${type}};UC;${type}")
    WRAP_IMAGE_FILTER_COMBINATIONS("${type}" "${st}")

  ENDFOREACH(type)

  BEGIN_MANAGED_PROPERTY("OutsideValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value for all pixels outside the given range.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetOutsideValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOutsideValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("InsideValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value for all pixels inside the given range.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetInsideValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInsideValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("UpperThreshold" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the upper threshold for segmentation. An exception is thrown if the lower threshold is greater than the upper threshold.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputPixelType>( m_PointerToNative->GetUpperThreshold() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetUpperThreshold( itk::ManagedTypes::ToNativePixel<NativeType::InputPixelType>( value ) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("LowerThreshold" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the lower threshold for segmentation. An exception is thrown if the lower threshold is greater than the upper threshold.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputPixelType>( m_PointerToNative->GetLowerThreshold() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLowerThreshold( itk::ManagedTypes::ToNativePixel<NativeType::InputPixelType>( value ) );")
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
