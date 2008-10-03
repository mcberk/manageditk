WRAP_CLASS("itk::ChamferDistanceTransformImageFilter")

  WRAP_IMAGE_FILTER_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("DistanceFromObject" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the computed distance is from the object.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetDistanceFromObject();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetDistanceFromObject(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("SetWeight")
    SET(MANAGED_METHOD_SUMMARY         "Set the weight for the given dimension.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "unsigned int dim, itkPixel^ weight")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetWeight( dim, itk::ManagedTypes::ToNativePixel<NativeType::OutputImageType::PixelType>( weight ) );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetWeight( dim, weight );")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
