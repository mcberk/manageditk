WRAP_CLASS("itk::SimilarityIndexImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  WRAP_IMAGE_FILTER_BOOL(2)

  BEGIN_MANAGED_PROPERTY("SimilarityIndex" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the computed similarity index (based on kappa statistic, similar to Dice coefficient).")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetSimilarityIndex();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
