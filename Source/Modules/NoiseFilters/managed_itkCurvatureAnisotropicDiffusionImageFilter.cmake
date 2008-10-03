WRAP_CLASS("itk::CurvatureAnisotropicDiffusionImageFilter")

  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_PROPERTY("TimeStep" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the time step for each iteration.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetTimeStep();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetTimeStep(value);")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("NumberOfIterations" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of iterations for which the filter will run.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfIterations();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfIterations(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("ConductanceParameter" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the conductance parameter governing sensitivity of the conductance equation.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetConductanceParameter();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetConductanceParameter(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("ConductanceScalingUpdateInterval" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the interval at which a new scaling for the conductance term is calculated.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetConductanceScalingUpdateInterval();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetConductanceScalingUpdateInterval(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("FixedAverageGradientMagnitude" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value for the average gradient magnitude of the image at each iteration.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFixedAverageGradientMagnitude();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetConductanceScalingParameter(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("ConductanceScalingParameter" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the conductance scaling value. WARNING: I think this value is not used, and will have no effect on the output. TODO: Investigate.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetConductanceScalingParameter();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetConductanceScalingParameter(value);")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()

