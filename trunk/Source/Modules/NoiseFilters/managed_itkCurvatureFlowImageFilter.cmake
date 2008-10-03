WRAP_CLASS("itk::CurvatureFlowImageFilter")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFiniteDifferenceImageFilter_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFiniteDifferenceImageFilter_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("TimeStep" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the time step for each iteration.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetTimeStep();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetTimeStep( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
