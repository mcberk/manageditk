WRAP_CLASS("itk::MeshSpatialObject")

  WRAP_INCLUDE_TYPE("itkDefaultStaticMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkDefaultDynamicMeshTraits.h")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SO")

  FOREACH(d "3")
    FOREACH(m ${WRAP_ITK_MESH_PIXELS})
        WRAP_TEMPLATE("${ITKM_M${m}${d}S}"  "${ITKT_M${m}${d}S}")
        WRAP_TEMPLATE("${ITKM_M${m}${d}D}"  "${ITKT_M${m}${d}D}")
    ENDFOREACH(m)
  ENDFOREACH(d)

  BEGIN_MANAGED_METHOD("SetMesh")
    SET(MANAGED_METHOD_SUMMARY         "Set the mesh.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkMeshBase^ mesh")
    SET(MANAGED_METHOD_TYPE_BODY       "\n\t\tINativePointer^ meshPtr = safe_cast<INativePointer^>(mesh);\n\t\tthis->m_PointerToNative->SetMesh(reinterpret_cast<NativeType::MeshType*>(meshPtr->NativePointer.ToPointer()));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetMesh(mesh);")
  END_MANAGED_METHOD()
  
  BEGIN_MANAGED_METHOD("GetMesh")
    SET(MANAGED_METHOD_SUMMARY         "Get the mesh.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkMeshBase^ mesh")
    SET(MANAGED_METHOD_TYPE_BODY       "mesh->NativePointer = IntPtr((NativeType::MeshType*)m_PointerToNative->GetMesh( ));")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->GetMesh( mesh );")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
