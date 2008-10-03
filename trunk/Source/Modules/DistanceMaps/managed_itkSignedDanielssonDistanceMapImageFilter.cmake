WRAP_CLASS("itk::SignedDanielssonDistanceMapImageFilter")

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
  
  BEGIN_MANAGED_PROPERTY("InsideIsPositive" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the inside represents positive values in the signed distance map. By convention ON pixels are treated as inside pixels.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetInsideIsPositive();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInsideIsPositive(value);")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
