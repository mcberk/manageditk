WRAP_CLASS("itk::ConnectedComponentImageFilter")
  # Create wrappers from every selected integral (signed and un) type to every
  # selected unsigned type. Also force ulong output for the watershed filter.
  UNIQUE(to_types "UL;${WRAP_ITK_USIGN_INT}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${WRAP_ITK_INT}" "${to_types}")

  BEGIN_MANAGED_PROPERTY("FullyConnected" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the neighbourhood connectivity for the algorithm. For example: with 2D images, FullyConnected=True means 8-neighbourhood connectivity and FullyConnected=False means 4-neighbourhood connectivity.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFullyConnected();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFullyConnected(value);")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
