WRAP_NON_TEMPLATE_CLASS("itk::ConjugateGradientOptimizer")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSingleValuedNonLinearOptimizer_TYPE.cxx.in)

  BEGIN_MANAGED_PROPERTY("Maximize" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the optimizer maximizes or minimizes the cost function.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMaximize( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMaximize();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Minimize" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the optimizer maximizes or minimizes the cost function.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMinimize( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMinimize();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("NumberOfIterations" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the number of elapsed iterations.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return (unsigned long)m_PointerToNative->GetNumberOfIterations();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("CurrentIteration" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the number of elapsed iterations.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetCurrentIteration();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("GetValue")
    SET(MANAGED_METHOD_INTERFACE       OFF)
    SET(MANAGED_METHOD_SUMMARY         "Get the current value.")
    SET(MANAGED_METHOD_RETURN_TYPE     "double")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "return m_PointerToNative->GetValue();")
  END_MANAGED_METHOD()

END_WRAP_NON_TEMPLATE_CLASS()
