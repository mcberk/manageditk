WRAP_CLASS("itk::ImportImageFilter")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageSource_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageSource_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    UNIQUE (types "${WRAP_ITK_SCALAR}")
      FOREACH(t ${types})
        WRAP_TEMPLATE("${ITKM_${t}}${d}"
                      "${ITKT_${t}},${d}")
      ENDFOREACH(t)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("Region" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the region object that defines the size and starting index for the imported image. This will serve as the LargestPossibleRegion, the BufferedRegion, and the RequestedRegion.")
    SET(MANAGED_PROPERTY_TYPE      "itkImageRegion^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedImageRegion<NativeType::OutputImageType::ImageDimension>( m_PointerToNative->GetRegion() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetRegion( itk::ManagedTypes::ToNativeImageRegion<NativeType::OutputImageType::ImageDimension>(value) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Spacing" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the spacing of the imported image.")
    SET(MANAGED_PROPERTY_TYPE      "itkSpacing^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedSpacing<NativeType::OutputImageType::ImageDimension>( m_PointerToNative->GetSpacing() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSpacing( itk::ManagedTypes::ToNativeSpacing<NativeType::OutputImageType::ImageDimension>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Origin" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the origin of the imported image.")
    SET(MANAGED_PROPERTY_TYPE      "itkPoint^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPoint<NativeType::OutputImageType::ImageDimension>( m_PointerToNative->GetOrigin() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOrigin( itk::ManagedTypes::ToNativePoint<NativeType::OutputImageType::ImageDimension>(value) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_METHOD("SetImportPointer")
    SET(MANAGED_METHOD_SUMMARY         "Set the pointer from which the image data is imported. num is the number of pixels in the block of memory. If letFilterManageMemory is false, then the this filter will not free the memory in its destructor and the application providing the buffer retains the responsibility of freeing the memory for this image data. If letFilterManageMemory is true, then this class will free the memory when this object is destroyed.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "IntPtr ptr, unsigned long num, bool letFilterManageMemory")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->SetImportPointer((NativeType::OutputImagePixelType*)(ptr.ToPointer()), num, letFilterManageMemory);")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetImportPointer(ptr, num, letFilterManageMemory);")
  END_MANAGED_METHOD()
  
END_WRAP_CLASS()
