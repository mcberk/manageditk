WRAP_NON_TEMPLATE_CLASS("itk::QuaternionRigidTransformGradientDescentOptimizer")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSingleValuedNonLinearOptimizer_TYPE.cxx.in)

  SET(body "")
  SET(body "${body}///<summary>A managed enumerated type for the stop condition.</summary>\n")
  SET(body "${body}\tenum class StopConditionEnum\n")
  SET(body "${body}\t{\n")
  SET(body "${body}\t\tMaximumNumberOfIterations,\n")
  SET(body "${body}\t\tMetricError\n")
  SET(body "${body}\t};\n")
  SET(MANAGED_EXTRA_TYPE_CONFIG ${body})

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
  
  BEGIN_MANAGED_PROPERTY("LearningRate" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the learning rate.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLearningRate( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetLearningRate();")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("NumberOfIterations" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of iterations.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfIterations( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfIterations();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("CurrentIteration" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the number of elapsed iterations.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetCurrentIteration();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("StopCondition" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the stop condition.")
    SET(MANAGED_PROPERTY_TYPE      "StopConditionEnum")
    SET(MANAGED_PROPERTY_GET_BODY  "return (StopConditionEnum)m_PointerToNative->GetStopCondition();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("GetValue")
    SET(MANAGED_METHOD_INTERFACE       OFF)
    SET(MANAGED_METHOD_SUMMARY         "Get the current value.")
    SET(MANAGED_METHOD_RETURN_TYPE     "double")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "return m_PointerToNative->GetValue();")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("AdvanceOneStep")
    SET(MANAGED_METHOD_INTERFACE       OFF)
    SET(MANAGED_METHOD_SUMMARY         "Advance one step following the gradient direction.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->AdvanceOneStep( );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("StopOptimization")
    SET(MANAGED_METHOD_INTERFACE       OFF)
    SET(MANAGED_METHOD_SUMMARY         "Stop the optimization algorithm.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->StopOptimization( );")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("ResumeOptimization")
    SET(MANAGED_METHOD_INTERFACE       OFF)
    SET(MANAGED_METHOD_SUMMARY         "Resume previously stopped optimization with current parameters.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->ResumeOptimization( );")
  END_MANAGED_METHOD()

END_WRAP_NON_TEMPLATE_CLASS()
