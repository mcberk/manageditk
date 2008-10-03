WRAP_CLASS("itk::GrayscaleGrindPeakImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("FullyConnected" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFullyConnected();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFullyConnected(value);")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
