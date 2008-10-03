WRAP_CLASS("itk::GradientRecursiveGaussianImageFilter")

  FOREACH(d ${WRAP_ITK_DIMS})
    IF(WRAP_float AND WRAP_covariant_vector)
      WRAP_IMAGE_FILTER_TYPES(F CVF ${d})
    ENDIF(WRAP_float AND WRAP_covariant_vector)

    IF(WRAP_double AND WRAP_covariant_vector)
      WRAP_IMAGE_FILTER_TYPES(D CVD ${d})
    ENDIF(WRAP_double AND WRAP_covariant_vector)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("Sigma" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the Gaussian variance (measured in the units of image spacing).")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSigma( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("NormalizeAcrossScale" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set if the Gaussian normalization factor should be used.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNormalizeAcrossScale( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
