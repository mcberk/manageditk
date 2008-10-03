WRAP_CLASS("itk::MatchCardinalityImageToImageMetric")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_USIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_SIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_REAL(2 2+)
  
  BEGIN_MANAGED_PROPERTY("MeasureMatches" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set whether this metric measures pixel matches or pixel mismatches. Note the GetValue() returns the number of matches (or mismatches) normalized by the number of pixels considered. In other words, the metric measures the percentage of pixel matches or mismatches. The default is to measure matches (MeasureMatches = true).")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMeasureMatches( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMeasureMatches();")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("NumberOfThreads" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of threads to create when executing..")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfThreads( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfThreads();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
