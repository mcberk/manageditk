WRAP_CLASS("itk::ImageRegionIterator")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIterator_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIterator_WRAPPER.cxx.in)
  SET(MANAGED_SUBCLASS itk::itkImageIterator)

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)
  WRAP_IMAGE_FILTER_BOOL(1)

  BEGIN_MANAGED_CONSTRUCTOR()
    SET(MANAGED_CONSTRUCTOR_SUMMARY       "Constructor taking image and region.")
    SET(MANAGED_CONSTRUCTOR_PARAMS        "itk::itkImageBase^ image, itk::itkImageRegion^ region")
    SET(MANAGED_CONSTRUCTOR_TYPE_BODY     "this->Initialise();\n\t\tthis->m_PointerToNative = new NativeType( (NativeType::ImageType*)image->NativePointer.ToPointer(), itk::ManagedTypes::ToNativeImageRegion<NativeType::ImageIteratorDimension>(region) );")
    SET(MANAGED_CONSTRUCTOR_WRAPPER_BODY  "this->m_MangledTypeString = image->MangledTypeString;\n\t\tarray<Object^>^ args = {image, region};\n\t\tthis->CreateInstance( args );")
  END_MANAGED_CONSTRUCTOR()

  BEGIN_MANAGED_METHOD_OVERRIDE("Set")
    SET(MANAGED_METHOD_SUMMARY         "Set the pixel value at the current iterator location.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itk::itkPixel^ value")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->Set( itk::ManagedTypes::ToNativePixel<NativeType::PixelType>(value) );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "this->m_Instance->Set( value );")
  END_MANAGED_METHOD_OVERRIDE()

END_WRAP_CLASS()
