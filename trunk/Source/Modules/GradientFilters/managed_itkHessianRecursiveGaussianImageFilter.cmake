WRAP_CLASS("itk::HessianRecursiveGaussianImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)

  BEGIN_MANAGED_PROPERTY("Sigma" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the Gaussian variance (measured in the units of image spacing).")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSigma( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("NormalizeAcrossScale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set if the Gaussian normalization factor should be used.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNormalizeAcrossScale( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNormalizeAcrossScale( );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
