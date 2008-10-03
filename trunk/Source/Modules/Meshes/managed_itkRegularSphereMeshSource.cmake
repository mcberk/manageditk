WRAP_CLASS("itk::RegularSphereMeshSource")

  WRAP_INCLUDE_TYPE("itkDefaultStaticMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkDefaultDynamicMeshTraits.h")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshSource_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMeshSource_WRAPPER.cxx.in)

  FOREACH(d "3")
    FOREACH(t ${WRAP_ITK_MESH_PIXELS})
      WRAP_TEMPLATE("${ITKM_M${t}${d}S}"  "${ITKT_M${t}${d}S}")
      WRAP_TEMPLATE("${ITKM_M${t}${d}D}"  "${ITKT_M${t}${d}D}")
    ENDFOREACH(t)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("Resolution" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the resolution level to be used for generating cells in the Sphere. High values of this parameter will produce sphere with more triangles.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetResolution();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetResolution( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Center" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the center of the output sphere.")
    SET(MANAGED_PROPERTY_TYPE      "itkPoint^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPoint<NativeType::OutputMeshType::PointDimension>( m_PointerToNative->GetCenter() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetCenter( itk::ManagedTypes::ToNativePoint<NativeType::OutputMeshType::PointDimension>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Scale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set scales of the Sphere. This is a vector of values that can actually be used for generating ellipsoids aligned with the coordinate axis.")
    SET(MANAGED_PROPERTY_TYPE      "itkVector^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedVector<NativeType::OutputMeshType::PointDimension>( m_PointerToNative->GetScale() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetScale( itk::ManagedTypes::ToNativeVector<NativeType::OutputMeshType::PointDimension>(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
