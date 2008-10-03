WRAP_NON_TEMPLATE_CLASS("itk::LBFGSOptimizer")

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

  BEGIN_MANAGED_PROPERTY("Trace" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the optimizer trace flag. If set to true, the optimizer prints out information every iteration.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetTrace( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetTrace();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("MaximumNumberOfFunctionEvaluations" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the maximum number of function evaluations allowed.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMaximumNumberOfFunctionEvaluations( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMaximumNumberOfFunctionEvaluations();")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("GradientConvergenceTolerance" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the gradient convergence tolerance. This is a positive real number that determines the accuracy with which the solution is to be found. The optimization terminates when: ||G|| < value max(1,||X||) where ||.|| denotes the Euclidean norm.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetGradientConvergenceTolerance( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetGradientConvergenceTolerance();")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("LineSearchAccuracy" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the line search accuracy. This is a positive real number with a default value of 0.9, which controls the accuracy of the line search. If the function and gradient evalutions are inexpensive with respect to the cost of the iterations it may be advantageous to set the value to a small value (say 0.1).")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLineSearchAccuracy( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetLineSearchAccuracy();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("DefaultStepLength" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the default step size. This is a positive real number with a default value of 1.0 which determines the stpe size in the line search.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetDefaultStepLength( value );")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetDefaultStepLength();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("GetValue")
    SET(MANAGED_METHOD_INTERFACE       OFF)
    SET(MANAGED_METHOD_SUMMARY         "Get the current value.")
    SET(MANAGED_METHOD_RETURN_TYPE     "double")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "return m_PointerToNative->GetValue();")
  END_MANAGED_METHOD()

END_WRAP_NON_TEMPLATE_CLASS()
