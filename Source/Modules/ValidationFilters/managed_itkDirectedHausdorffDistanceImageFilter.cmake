WRAP_CLASS("itk::DirectedHausdorffDistanceImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  WRAP_IMAGE_FILTER_BOOL(2)

  BEGIN_MANAGED_PROPERTY("DirectedHausdorffDistance" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the computed directed Hausdorff distance.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetDirectedHausdorffDistance();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
