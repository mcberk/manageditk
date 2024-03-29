WRAP_CLASS("itk::ImageSeriesReader")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageSource_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageSource_WRAPPER.cxx.in)

  UNIQUE(image_types "UC;${WRAP_ITK_ALL_TYPES}")
  WRAP_IMAGE_FILTER("${image_types}" 1)

  BEGIN_MANAGED_PROPERTY("ReverseOrder" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "ReverseOrderOn changes the order of travesal of the file names from last to first.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetReverseOrder();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetReverseOrder( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("AddFileName")
    SET(MANAGED_METHOD_SUMMARY         "Add a single filename to the list of files. To add a vector of filenames, use the AddFileNames method.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "String^ filename")
    SET(MANAGED_METHOD_TYPE_BODY       "std::string stdfilename; ManagedTypes::ToNativeString( filename, stdfilename ); m_PointerToNative->AddFileName( stdfilename.c_str() );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->AddFileName( filename );")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("SetFileName")
    SET(MANAGED_METHOD_SUMMARY         "Set the first file name to be processed. This deletes previous filenames.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "String^ filename")
    SET(MANAGED_METHOD_TYPE_BODY       "std::string stdfilename; ManagedTypes::ToNativeString( filename, stdfilename ); m_PointerToNative->SetFileName( stdfilename.c_str() );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetFileName( filename );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("SetFileNames")
    SET(MANAGED_METHOD_SUMMARY         "Set the array of strings that contains the file names. Files are processed in sequential order.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "array<System::String^>^ filenames")
    SET(MANAGED_METHOD_TYPE_BODY       "for each (System::String^ filename in filenames){ this->AddFileName( filename ); }")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetFileNames( filenames );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("SetFileNames")
    SET(MANAGED_METHOD_SUMMARY         "Set the path and pattern defining the array of filenames. Example: path=\"C:/temp/\", pattern=\"test_*.png\"")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "String^ path, String^ pattern")
    SET(MANAGED_METHOD_TYPE_BODY       "this->SetFileNames( System::IO::Directory::GetFiles(path, pattern) );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetFileNames( path, pattern );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("SetImageIO")
    SET(MANAGED_METHOD_SUMMARY         "Set the ImageIO helper class. Often this is created via the object factory mechanism that determines whether a particular ImageIO can read a certain file. This method provides a way to get the ImageIO instance that is created. Or you can directly specify the ImageIO to use to read a particular file in case the factory mechanism will not work properly (e.g., unknown or unusual extension).")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkImageIOBase^ imageIO")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->SetImageIO( (ImageIOBase*)imageIO->NativePointer.ToPointer());")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetImageIO(imageIO);")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("GetImageIO")
    SET(MANAGED_METHOD_SUMMARY         "Get the ImageIO helper class. Often this is created via the object factory mechanism that determines whether a particular ImageIO can read a certain file. This method provides a way to get the ImageIO instance that is created. Or you can directly specify the ImageIO to use to read a particular file in case the factory mechanism will not work properly (e.g., unknown or unusual extension).")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkImageIOBase^ imageIO")
    SET(MANAGED_METHOD_TYPE_BODY       "ImageIOBase* nativeImageIO = this->m_PointerToNative->GetImageIO(); imageIO->NativePointer = IntPtr(nativeImageIO);")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->GetImageIO(imageIO);")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("GetImageIO")
    SET(MANAGED_METHOD_SUMMARY         "Get the ImageIO helper class. Often this is created via the object factory mechanism that determines whether a particular ImageIO can read a certain file. This method provides a way to get the ImageIO instance that is created. Or you can directly specify the ImageIO to use to read a particular file in case the factory mechanism will not work properly (e.g., unknown or unusual extension).")
    SET(MANAGED_METHOD_RETURN_TYPE     "IntPtr")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "ImageIOBase* nativeImageIO = this->m_PointerToNative->GetImageIO(); return IntPtr(nativeImageIO);")
    SET(MANAGED_METHOD_WRAPPER_BODY    "return iInstance->GetImageIO();")
  END_MANAGED_METHOD()
  
END_WRAP_CLASS()
