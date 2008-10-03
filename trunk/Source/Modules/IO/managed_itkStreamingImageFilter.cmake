WRAP_CLASS("itk::StreamingImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("NumberOfStreamDivisions" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of pieces to divide the input. The upstream pipeline will be executed this many times.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfStreamDivisions();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfStreamDivisions( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
