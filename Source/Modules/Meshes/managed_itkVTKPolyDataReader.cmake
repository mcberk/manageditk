WRAP_CLASS("itk::VTKPolyDataReader")

  WRAP_INCLUDE_TYPE("itkDefaultStaticMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkDefaultDynamicMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkSimplexMesh.h")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshSource_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshSource_WRAPPER.cxx.in)

  FOREACH(d "3")
    FOREACH(t ${WRAP_ITK_MESH_PIXELS})
      WRAP_TEMPLATE("${ITKM_M${t}${d}S}"  "${ITKT_M${t}${d}S}")
      WRAP_TEMPLATE("${ITKM_M${t}${d}D}"  "${ITKT_M${t}${d}D}")
      WRAP_TEMPLATE("${ITKM_SM${t}${d}S}"  "${ITKT_SM${t}${d}S}")
      WRAP_TEMPLATE("${ITKM_SM${t}${d}D}"  "${ITKT_SM${t}${d}D}")
    ENDFOREACH(t)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("FileName" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the name of the file to be read.")
    SET(MANAGED_PROPERTY_TYPE      "String^")
    SET(MANAGED_PROPERTY_GET_BODY  "return gcnew String( m_PointerToNative->GetFileName() );")
    SET(MANAGED_PROPERTY_SET_BODY  "std::string stdvalue; ManagedTypes::ToNativeString( value, stdvalue ); m_PointerToNative->SetFileName( stdvalue.c_str() );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
