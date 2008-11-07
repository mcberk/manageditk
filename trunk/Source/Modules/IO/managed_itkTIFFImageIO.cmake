WRAP_CLASS("itk::TIFFImageIO")

  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIOBase_WRAPPER.cxx.in)
  SET(WRAP_TEMPLATE_LIST )

  SET(body "")
  SET(body "${body}///<summary>A managed enumerated type for the compression.</summary>\n")
  SET(body "${body}\tpublic enum class CompressionEnum\n")
  SET(body "${body}\t{\n")
  SET(body "${body}\t\tNoCompression,\n")
  SET(body "${body}\t\tPackBits,\n")
  SET(body "${body}\t\tJPEG,\n")
  SET(body "${body}\t\tDeflate,\n")
  SET(body "${body}\t\tLZW\n")
  SET(body "${body}\t};\n")
  SET(MANAGED_EXTRA_TYPE_CONFIG ${body})

  BEGIN_MANAGED_PROPERTY("Compression" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the compression.")
    SET(MANAGED_PROPERTY_TYPE      "CompressionEnum")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetCompression( (int)value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
