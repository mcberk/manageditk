WRAP_CLASS("itk::KappaStatisticImageToImageMetric")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_USIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_SIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_REAL(2 2+)
  
  BEGIN_MANAGED_PROPERTY("Complement" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set whether this metric returns 2*|A&B|/(|A|+|B|) (ComplementOff, the default) or 1.0 - 2*|A&B|/(|A|+|B|) (ComplementOn). When using an optimizer that minimizes metric values use ComplementOn().")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetComplement( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetComplement();")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("ForegroundValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the foreground value. The default value is 255.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetForegroundValue( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetForegroundValue();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
