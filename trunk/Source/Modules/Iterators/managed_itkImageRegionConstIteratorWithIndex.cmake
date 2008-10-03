WRAP_CLASS("itk::ImageRegionConstIteratorWithIndex")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIteratorWithIndex_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIteratorWithIndex_WRAPPER.cxx.in)
  SET(MANAGED_SUBCLASS itk::itkImageConstIteratorWithIndex)

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)
  WRAP_IMAGE_FILTER_BOOL(1)

  BEGIN_MANAGED_CONSTRUCTOR()
    SET(MANAGED_CONSTRUCTOR_SUMMARY       "Constructor taking image and region.")
    SET(MANAGED_CONSTRUCTOR_PARAMS        "itk::itkImageBase^ image, itk::itkImageRegion^ region")
    SET(MANAGED_CONSTRUCTOR_TYPE_BODY     "this->Initialise();\n\t\tthis->m_PointerToNative = new NativeType( (NativeType::ImageType*)image->NativePointer.ToPointer(), itk::ManagedTypes::ToNativeImageRegion<NativeType::ImageDimension>(region) );")
    SET(MANAGED_CONSTRUCTOR_WRAPPER_BODY  "this->m_MangledTypeString = image->MangledTypeString;\n\t\tarray<Object^>^ args = {image, region};\n\t\tthis->CreateInstance( args );")
  END_MANAGED_CONSTRUCTOR()

END_WRAP_CLASS()
