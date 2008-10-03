WRAP_CLASS("itk::NiftiImageIO")

  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageIOBase_WRAPPER.cxx.in)
  SET(WRAP_TEMPLATE_LIST )

  BEGIN_MANAGED_PROPERTY("LegacyAnalyze75Mode" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the mode to allow the Nifti filter to read and write to the LegacyAnalyze75 format as interpreted by the nifti library maintainers. This format does not properly respect the file orientation fields. The itkAnalyzeImageIO file reader/writer should be used to match the Analyze75 file definitions as specified by the Mayo Clinic BIR laboratory. By default this is set to false.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetLegacyAnalyze75Mode();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLegacyAnalyze75Mode( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
