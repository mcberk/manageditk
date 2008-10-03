WRAP_CLASS("itk::AntiAliasBinaryImageFilter")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFiniteDifferenceImageFilter_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFiniteDifferenceImageFilter_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("NumberOfLayers" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of layers to use in the sparse field. Argument is the number of layers on ONE side of the active layer, so the total layers in the sparse field is 2*NumberOfLayers+1.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfLayers();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfLayers(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("IsoSurfaceValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value of the isosurface to use in the input image.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::ValueType>( m_PointerToNative->GetIsoSurfaceValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetIsoSurfaceValue( itk::ManagedTypes::ToNativePixel<NativeType::ValueType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("InterpolateSurfaceLocation" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value of the InterpolateSurfaceLocation flag. This flag tells the solver whether or not to interpolate for the surface location when calculating change at a voxel location. Turned on by default. Some applications may not use this value and can safely turn the flag off.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetInterpolateSurfaceLocation();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInterpolateSurfaceLocation(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("UpperBinaryValue" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the upper binary value in the input image.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::BinaryValueType>( m_PointerToNative->GetUpperBinaryValue() );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("LowerBinaryValue" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the lower binary value in the input image.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::BinaryValueType>( m_PointerToNative->GetLowerBinaryValue() );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
