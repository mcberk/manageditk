WRAP_CLASS("itk::ConnectedComponentImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  IF(NOT WRAP_unsigned_long)
    WRAP_IMAGE_FILTER("UL" 2)
  ENDIF(NOT WRAP_unsigned_long)

  BEGIN_MANAGED_PROPERTY("FullyConnected" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the neighbourhood connectivity for the algorithm. For example: with 2D images, FullyConnected=True means 8-neighbourhood connectivity and FullyConnected=False means 4-neighbourhood connectivity.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFullyConnected();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFullyConnected(value);")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
