WRAP_CLASS("itk::ConfidenceConnectedImageFilter")
  
  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  BEGIN_MANAGED_METHOD("AddSeed")
    SET(MANAGED_METHOD_SUMMARY         "Add a seed.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkIndex^ seed")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->AddSeed( itk::ManagedTypes::ToNativeIndex<NativeType::InputImageType::ImageDimension>(seed) );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->AddSeed( seed );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("ClearSeeds")
    SET(MANAGED_METHOD_SUMMARY         "Clear the seeds.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->ClearSeeds();")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->ClearSeeds();")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_PROPERTY("Multiplier" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the multiplier to define the confidence interval. Multiplier can be anything greater than zero. A typical value is 2.5.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMultiplier();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMultiplier( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("NumberOfIterations" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of iterations.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfIterations();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfIterations( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("ReplaceValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value to replace thresholded pixels.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputImageType::PixelType>( m_PointerToNative->GetReplaceValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetReplaceValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputImageType::PixelType>( value ) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("InitialNeighborhoodRadius" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the radius of the neighborhood over which the statistics are evaluated.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetInitialNeighborhoodRadius();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInitialNeighborhoodRadius( value );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Mean" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the mean of the pixels accepted in the output region. This property is only valid after the filter has been exectued, ie. after calling Update().")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetMean() );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Variance" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the variance of the pixels accepted in the output region. This property is only valid after the filter has been exectued, ie. after calling Update().")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return static_cast<double>( m_PointerToNative->GetVariance() );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
