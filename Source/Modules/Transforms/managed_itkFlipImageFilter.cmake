WRAP_CLASS("itk::FlipImageFilter")

  WRAP_IMAGE_FILTER_SCALAR(1)

  BEGIN_MANAGED_PROPERTY("FlipAboutOrigin" GETSET)
    SET(MANAGED_METHOD_SUMMARY     "Controls how the output origin is computed. If FlipAboutOrigin is 'on', the flip will occur about the origin of the axis; otherwise, the flip will occur about the center of the axis.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFlipAboutOrigin();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFlipAboutOrigin( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("FlipAxes" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the axis to be flipped. The image is flipped along axes for which array[i] is true.")
    SET(MANAGED_PROPERTY_TYPE      "array<bool>^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedFixedArray<bool, NativeType::ImageDimension>( m_PointerToNative->GetFlipAxes() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFlipAxes( itk::ManagedTypes::ToNativeFixedArray<bool, NativeType::ImageDimension>(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
