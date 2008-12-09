WRAP_CLASS("itk::MorphologicalWatershedFromMarkersImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("FullyConnected" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the neighbourhood connectivity for the algorithm. For example: with 2D images, FullyConnected=True means 8-neighbourhood connectivity and FullyConnected=False means 4-neighbourhood connectivity.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFullyConnected();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFullyConnected(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("MarkWatershedLine" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set whether the watershed pixel must be marked or not. Default is true. Set to false to avoid writing watershed pixels, it also decreases algorithm complexity.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMarkWatershedLine( );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMarkWatershedLine( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
