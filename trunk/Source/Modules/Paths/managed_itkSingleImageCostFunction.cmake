WRAP_CLASS("itk::SingleImageCostFunction")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSingleValuedCostFunction_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSingleValuedCostFunction_WRAPPER.cxx.in)

  # WRAP_IMAGE_FILTER_USIGN_INT(1)
  # WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)
  
  BEGIN_MANAGED_METHOD("Initialize")
    SET(MANAGED_METHOD_SUMMARY         "Initialize the cost function.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "return m_PointerToNative->Initialize();")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("SetImage")
    SET(MANAGED_METHOD_SUMMARY         "Set the underlying image representing the cost function.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkImageBase^ image")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetImage( (NativeType::ImageType*)image->NativePointer.ToPointer() );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetImage( image );")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("GetImage")
    SET(MANAGED_METHOD_SUMMARY         "Get the underlying image representing the cost function..")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkImageBase^ image")
    SET(MANAGED_METHOD_TYPE_BODY       "image->NativePointer = IntPtr((NativeType::ImageType*)m_PointerToNative->GetImage( ));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->GetImage( image );")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
