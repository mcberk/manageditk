WRAP_CLASS("itk::ConstantPadImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)
  WRAP_IMAGE_FILTER_VECTOR(2)
  WRAP_IMAGE_FILTER_BOOL(2)

  SET(getbody "")
  SET(getbody "${getbody}array<unsigned long>^ managedArray = gcnew array<unsigned long>( NativeType::ImageDimension );\n")
  SET(getbody "${getbody}const unsigned long* nativeArray = m_PointerToNative->GetPadLowerBound();\n")
  SET(getbody "${getbody}\t\tfor ( unsigned int i=0; i<NativeType::ImageDimension; i++ ) \n")
  SET(getbody "${getbody}\t\t\tmanagedArray[i] = nativeArray[i];\n")
  SET(getbody "${getbody}\t\treturn managedArray;")

  SET(setbody "")
  SET(setbody "${setbody}unsigned long nativeArray[NativeType::ImageDimension];\n")
  SET(setbody "${setbody}\t\tfor (unsigned int i=0; i<NativeType::ImageDimension; i++) \n")
  SET(setbody "${setbody}\t\t\tnativeArray[i] = value[i];\n")
  SET(setbody "${setbody}\t\tm_PointerToNative->SetPadLowerBound( nativeArray );")

  BEGIN_MANAGED_PROPERTY("PadLowerBound" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the padding to apply to the output image lower bound.")
    SET(MANAGED_PROPERTY_TYPE      "array<unsigned long>^")
    SET(MANAGED_PROPERTY_GET_BODY  "${getbody}")
    SET(MANAGED_PROPERTY_SET_BODY  "${setbody}")
  END_MANAGED_PROPERTY()

  SET(getbody "")
  SET(getbody "${getbody}array<unsigned long>^ managedArray = gcnew array<unsigned long>( NativeType::ImageDimension );\n")
  SET(getbody "${getbody}const unsigned long* nativeArray = m_PointerToNative->GetPadUpperBound();\n")
  SET(getbody "${getbody}\t\tfor ( unsigned int i=0; i<NativeType::ImageDimension; i++ ) \n")
  SET(getbody "${getbody}\t\t\tmanagedArray[i] = nativeArray[i];\n")
  SET(getbody "${getbody}\t\treturn managedArray;")

  SET(setbody "")
  SET(setbody "${setbody}unsigned long nativeArray[NativeType::ImageDimension];\n")
  SET(setbody "${setbody}\t\tfor (unsigned int i=0; i<NativeType::ImageDimension; i++) \n")
  SET(setbody "${setbody}\t\t\tnativeArray[i] = value[i];\n")
  SET(setbody "${setbody}\t\tm_PointerToNative->SetPadUpperBound( nativeArray );")

  BEGIN_MANAGED_PROPERTY("PadUpperBound" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the padding to apply to the output image upper bound.")
    SET(MANAGED_PROPERTY_TYPE      "array<unsigned long>^")
    SET(MANAGED_PROPERTY_GET_BODY  "${getbody}")
    SET(MANAGED_PROPERTY_SET_BODY  "${setbody}")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("Constant" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the pixel value used to pad the image.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputImagePixelType>( m_PointerToNative->GetConstant() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetConstant( itk::ManagedTypes::ToNativePixel<NativeType::OutputImagePixelType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
