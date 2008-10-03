WRAP_CLASS("itk::AddImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(3)
  WRAP_IMAGE_FILTER_SIGN_INT(3)
  WRAP_IMAGE_FILTER_REAL(3)
  
  BEGIN_MANAGED_METHOD("SetInput1")
    SET(MANAGED_METHOD_SUMMARY         "Set Input1 image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkDataObject^ input")
    SET(MANAGED_METHOD_TYPE_BODY       "\n\t\tINativePointer^ inputPtr = safe_cast<INativePointer^>(input);\n\t\tthis->m_PointerToNative->SetInput(0, reinterpret_cast<NativeType::Input1ImageType*>(inputPtr->NativePointer.ToPointer()));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput1(input);")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("SetInput2")
    SET(MANAGED_METHOD_SUMMARY         "Set Input2 image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkDataObject^ input")
    SET(MANAGED_METHOD_TYPE_BODY       "\n\t\tINativePointer^ inputPtr = safe_cast<INativePointer^>(input);\n\t\tthis->m_PointerToNative->SetInput(1, reinterpret_cast<NativeType::Input2ImageType*>(inputPtr->NativePointer.ToPointer()));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput2(input);")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("SetInput1")
    SET(MANAGED_METHOD_SUMMARY         "Set Input1 image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "IntPtr inputPtr")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->SetInput(0, (NativeType::Input1ImageType*)inputPtr.ToPointer());")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput1(inputPtr);")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("SetInput2")
    SET(MANAGED_METHOD_SUMMARY         "Set Input2 image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "IntPtr inputPtr")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->SetInput(1, (NativeType::Input2ImageType*)inputPtr.ToPointer());")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput2(inputPtr);")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_PROPERTY("CanRunInPlace" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get if the filter can run in place. To do so, the filter's first input and output must have the same dimension and pixel type. This property can be used in conjunction with InPlace to determine whether a particular use of the filter is really running in place. Some filters may be able to optimize their operation if the InPlace is true and CanRunInPlace is true.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->CanRunInPlace();")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("InPlace" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set if the filter will run in place. In place operation can be turned on and off. This only has an effect when the input and output image type match.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetInPlace();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetInPlace( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
