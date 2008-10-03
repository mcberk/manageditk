WRAP_CLASS("itk::PathToImageFilter")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageSource_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageSource_WRAPPER.cxx.in)

  WRAP_INCLUDE_TYPE("itkPolyLineParametricPath.h")

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})
      WRAP_TEMPLATE("${ITKM_PLPP${d}}${ITKM_I${t}${d}}" "${ITKT_PLPP${d}},${ITKT_I${t}${d}}")
    ENDFOREACH(t)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("Size" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the size of the output image.")
    SET(MANAGED_PROPERTY_TYPE      "itkSize^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedSize<NativeType::OutputImageType::ImageDimension>( m_PointerToNative->GetSize() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSize( itk::ManagedTypes::ToNativeSize<NativeType::OutputImageType::ImageDimension>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Spacing" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the spacing of the output image.")
    SET(MANAGED_PROPERTY_TYPE      "itkSpacing^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedSpacing<NativeType::OutputImageType::ImageDimension>( m_PointerToNative->GetSpacing() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSpacing( itk::ManagedTypes::ToNativeSpacing<NativeType::OutputImageType::ImageDimension>(value).GetDataPointer() );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Origin" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the origin of the output image.")
    SET(MANAGED_PROPERTY_TYPE      "itkPoint^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPoint<NativeType::OutputImageType::ImageDimension>( m_PointerToNative->GetOrigin() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOrigin( itk::ManagedTypes::ToNativePoint<NativeType::OutputImageType::ImageDimension>(value).GetDataPointer() );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("PathValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value for pixels on the path. ")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::ValueType>( m_PointerToNative->GetPathValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetPathValue( itk::ManagedTypes::ToNativePixel<NativeType::ValueType>( value ) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("BackgroundValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value for pixels off the path. ")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::ValueType>( m_PointerToNative->GetBackgroundValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetBackgroundValue( itk::ManagedTypes::ToNativePixel<NativeType::ValueType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_METHOD("SetInput")
    SET(MANAGED_METHOD_SUMMARY         "Set the path input of this process object.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkDataObject^ path")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetInput( (NativeType::InputPathType*)path->NativePointer.ToPointer() );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput( path );")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("SetInput")
    SET(MANAGED_METHOD_SUMMARY         "Set the path input of this process object.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "unsigned int index, itkDataObject^ path")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetInput( index, (NativeType::InputPathType*)path->NativePointer.ToPointer() );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput( index, path );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("GetInput")
    SET(MANAGED_METHOD_SUMMARY         "Get the path input of this process object.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkDataObject^ path")
    SET(MANAGED_METHOD_TYPE_BODY       "path->NativePointer = IntPtr((NativeType::InputPathType*)m_PointerToNative->GetInput( ));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->GetInput( path );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("GetInput")
    SET(MANAGED_METHOD_SUMMARY         "Get the path input of this process object.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "unsigned int index, itkDataObject^ path")
    SET(MANAGED_METHOD_TYPE_BODY       "path->NativePointer = IntPtr((NativeType::InputPathType*)m_PointerToNative->GetInput( index ));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->GetInput( index, path );")
  END_MANAGED_METHOD()


END_WRAP_CLASS()
