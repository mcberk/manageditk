WRAP_CLASS("itk::SimplexMeshAdaptTopologyFilter")

  WRAP_INCLUDE_TYPE("itkDefaultStaticMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkDefaultDynamicMeshTraits.h")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshToMeshFilter_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshToMeshFilter_WRAPPER.cxx.in)

  FOREACH(d "3")
    FOREACH(m ${WRAP_ITK_MESH_PIXELS})
      WRAP_TEMPLATE("${ITKM_SM${m}${d}S}${ITKM_SM${m}${d}S}"  "${ITKT_SM${m}${d}S},${ITKT_SM${m}${d}S}")
      WRAP_TEMPLATE("${ITKM_SM${m}${d}D}${ITKM_SM${m}${d}D}"  "${ITKT_SM${m}${d}D},${ITKT_SM${m}${d}D}")
    ENDFOREACH(m)
  ENDFOREACH(d)
  
  BEGIN_MANAGED_PROPERTY("Threshold" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the threshold value to control how many cells will be manipulated.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetThreshold();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetThreshold( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("SelectionMethod" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the criteria for cell refinement selection.")
    SET(MANAGED_PROPERTY_TYPE      "int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetSelectionMethod();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSelectionMethod( value );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("ModifiedCount" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the number of cells modified.")
    SET(MANAGED_PROPERTY_TYPE      "int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetModifiedCount();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
