WRAP_CLASS("itk::GeodesicActiveContourLevelSetImageFilter")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSegmentationLevelSetImageFilter_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSegmentationLevelSetImageFilter_WRAPPER.cxx.in)

  FILTER_DIMS(dims 2+)
  FOREACH(d ${dims})
    FOREACH(t ${WRAP_ITK_REAL})
      WRAP_TEMPLATE("${ITKM_I${t}${d}}${ITKM_I${t}${d}}${ITKM_${t}}" "${ITKT_I${t}${d}},${ITKT_I${t}${d}},${ITKT_${t}}")
    ENDFOREACH(t)
  ENDFOREACH(d)
  
  BEGIN_MANAGED_PROPERTY("DerivativeSigma" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value of sigma used to compute the edge potential map derivatives.")
    SET(MANAGED_PROPERTY_TYPE      "float")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetDerivativeSigma();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetDerivativeSigma( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
