WRAP_CLASS("itk::BinaryMinMaxCurvatureFlowImageFilter")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFiniteDifferenceImageFilter_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedFiniteDifferenceImageFilter_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_REAL(2)
  
  BEGIN_MANAGED_PROPERTY("TimeStep" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the time step for each iteration.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetTimeStep();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetTimeStep( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("StencilRadius" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the stencil radius.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetStencilRadius();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetStencilRadius( value );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Threshold" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the threshold value.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetThreshold();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetThreshold( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()

