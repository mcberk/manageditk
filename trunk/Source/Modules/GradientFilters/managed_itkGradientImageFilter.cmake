WRAP_CLASS("itk::GradientImageFilter")

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})

      IF(WRAP_float AND WRAP_covariant_vector)
        WRAP_TEMPLATE("${ITKM_I${t}${d}}${ITKM_F}${ITKM_F}" "${ITKT_I${t}${d}},${ITKT_F},${ITKT_F}")
      ENDIF(WRAP_float AND WRAP_covariant_vector)
    
      IF(WRAP_double AND WRAP_covariant_vector)
        WRAP_TEMPLATE("${ITKM_I${t}${d}}${ITKM_D}${ITKM_D}" "${ITKT_I${t}${d}},${ITKT_D},${ITKT_D}")
      ENDIF(WRAP_double AND WRAP_covariant_vector)

    ENDFOREACH(t)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("UseImageSpacing" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the filter should use the image spacing.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetUseImageSpacing();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetUseImageSpacing( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
