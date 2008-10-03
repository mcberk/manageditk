WRAP_CLASS("itk::MedianImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("Radius" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the radius of the neighbour to evaluate the median.")
    SET(MANAGED_PROPERTY_TYPE      "itkSize^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedSize<NativeType::InputImageType::ImageDimension>(m_PointerToNative->GetRadius());")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetRadius(itk::ManagedTypes::ToNativeSize<NativeType::InputImageType::ImageDimension>(value));")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
