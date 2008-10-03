WRAP_CLASS("itk::MetaImageIO")

  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIOBase_WRAPPER.cxx.in)
  SET(WRAP_TEMPLATE_LIST )

  BEGIN_MANAGED_PROPERTY("SubSamplingFactor" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the subsampling factor (in case we want a coarse version of the image). Warning this is only used when streaming is on.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetSubSamplingFactor();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSubSamplingFactor( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("DoublePrecision" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the precision of the MetaImage object.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetDoublePrecision( value );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("DataFileName" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the filename for the Data file. Setting this will make the Writer to use the non-Local mode and save header and data in independent files.")
    SET(MANAGED_PROPERTY_TYPE      "String^")
    SET(MANAGED_PROPERTY_SET_BODY  "std::string stdvalue; ManagedTypes::ToNativeString( value, stdvalue ); m_PointerToNative->SetDataFileName( stdvalue.c_str() );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
