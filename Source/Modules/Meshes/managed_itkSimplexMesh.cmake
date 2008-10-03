WRAP_CLASS("itk::SimplexMesh")

  WRAP_INCLUDE_TYPE("itkDefaultStaticMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkDefaultDynamicMeshTraits.h")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMesh_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMesh_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SM")

  FOREACH(d "3")
    FOREACH(t ${WRAP_ITK_MESH_PIXELS})
      WRAP_TEMPLATE("${t}${d}S"
        "${ITKT_${t}},${d},itk::DefaultStaticMeshTraits< ${ITKT_${t}},${d},${d},${ITKT_${t}} >")
      WRAP_TEMPLATE("${t}${d}D"
        "${ITKT_${t}},${d},itk::DefaultDynamicMeshTraits< ${ITKT_${t}},${d},${d},${ITKT_${t}} >")
    ENDFOREACH(t)
  ENDFOREACH(d)

END_WRAP_CLASS()
