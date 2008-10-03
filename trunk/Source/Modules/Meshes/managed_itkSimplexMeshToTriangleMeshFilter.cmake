WRAP_CLASS("itk::SimplexMeshToTriangleMeshFilter")

  WRAP_INCLUDE_TYPE("itkDefaultStaticMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkDefaultDynamicMeshTraits.h")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshToMeshFilter_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshToMeshFilter_WRAPPER.cxx.in)

  FOREACH(d "3")
    FOREACH(m ${WRAP_ITK_MESH_PIXELS})
      WRAP_TEMPLATE("${ITKM_SM${m}${d}S}${ITKM_M${m}${d}S}"  "${ITKT_SM${m}${d}S},${ITKT_M${m}${d}S}")
      WRAP_TEMPLATE("${ITKM_SM${m}${d}D}${ITKM_M${m}${d}D}"  "${ITKT_SM${m}${d}D},${ITKT_M${m}${d}D}")
    ENDFOREACH(m)
  ENDFOREACH(d)

END_WRAP_CLASS()
