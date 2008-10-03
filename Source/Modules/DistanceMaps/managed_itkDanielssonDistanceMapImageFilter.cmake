WRAP_CLASS("itk::DanielssonDistanceMapImageFilter")
  
  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("SquaredDistance" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the distance should be squared.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetSquaredDistance();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSquaredDistance(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("UseImageSpacing" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if image spacing should be used in computing distances.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetUseImageSpacing();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetUseImageSpacing(value);")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("InputIsBinary" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the input is binary. If this variable is set, each nonzero pixel in the input image will be given a unique numeric code to be used by the Voronoi partition.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetInputIsBinary();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInputIsBinary(value);")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()

