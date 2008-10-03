WRAP_CLASS("itk::ImageSpatialObject")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SO")

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(type ${WRAP_ITK_SCALAR})
      WRAP_TEMPLATE("${d}${ITKM_${type}}"  "${d},${ITKT_${type}}")
    ENDFOREACH(type)
  ENDFOREACH(d)

  BEGIN_MANAGED_METHOD("SetImage")
    SET(MANAGED_METHOD_SUMMARY         "Set the image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkImageBase^ image")
    SET(MANAGED_METHOD_TYPE_BODY       "\n\t\tINativePointer^ imagePtr = safe_cast<INativePointer^>(image);\n\t\tthis->m_PointerToNative->SetImage(reinterpret_cast<NativeType::ImageType*>(imagePtr->NativePointer.ToPointer()));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetImage(image);")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("GetImage")
    SET(MANAGED_METHOD_SUMMARY         "Get the image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkImageBase^ image")
    SET(MANAGED_METHOD_TYPE_BODY       "image->NativePointer = IntPtr((NativeType::ImageType*)m_PointerToNative->GetImage( ));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->GetImage( image );")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
