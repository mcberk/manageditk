WRAP_CLASS("itk::DerivativeImageFilter")

  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("UseImageSpacing" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if image spacing should be used by the filter.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetUseImageSpacing();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetUseImageSpacing(value);")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Order" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the order of the derivative.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOrder( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetOrder( );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Direction" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the direction the derivative is computed.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetDirection( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetDirection( );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
