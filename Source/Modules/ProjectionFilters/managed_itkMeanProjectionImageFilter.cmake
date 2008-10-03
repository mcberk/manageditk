WRAP_CLASS("itk::MeanProjectionImageFilter")
  WRAP_IMAGE_FILTER_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("ProjectionDimension" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the direction in which to accumulate the data. It must be set before calling Update() on the filter. Defaults to the last dimension.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetProjectionDimension();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetProjectionDimension( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
