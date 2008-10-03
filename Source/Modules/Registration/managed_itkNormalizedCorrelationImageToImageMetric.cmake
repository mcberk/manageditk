WRAP_CLASS("itk::NormalizedCorrelationImageToImageMetric")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_USIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_SIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_REAL(2 2+)
  
  BEGIN_MANAGED_PROPERTY("SubtractMean" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the SubtractMean boolean. If true, the sample mean is subtracted from the sample values in the cross-correlation formula and typically results in narrower valleys in the cost fucntion. Default value is false.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSubtractMean( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetSubtractMean();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
