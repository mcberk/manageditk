WRAP_CLASS("itk::MeanReciprocalSquareDifferenceImageToImageMetric")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_USIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_SIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_REAL(2 2+)
  
  BEGIN_MANAGED_PROPERTY("Lambda" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the Lambda value. This factor regulates the capture radius of this metric.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLambda( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetLambda();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Delta" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the Delta value. This value is used as the differential in the computation of the metric derivative using the finite differences method.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetDelta( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetDelta();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
