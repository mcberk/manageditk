# Begin the wrapping
WRAP_CLASS("itk::Hessian3DToVesselnessMeasureImageFilter")

  # Wrap the class for SCALAR types
  FOREACH(t ${WRAP_ITK_SCALAR})
    WRAP_TEMPLATE("${ITKM_${t}}" "${ITKT_${t}}")
  ENDFOREACH(t)

  # Wrap property
  BEGIN_MANAGED_PROPERTY("Alpha1" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the alpha1 value (see Sato paper for details).")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetAlpha1( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetAlpha1( );")
  END_MANAGED_PROPERTY()

  # Wrap another property
  BEGIN_MANAGED_PROPERTY("Alpha2" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the alpha2 value (see Sato paper for details).")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetAlpha2( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetAlpha2( );")
  END_MANAGED_PROPERTY()

# End the wrapping
END_WRAP_CLASS()