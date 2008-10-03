WRAP_CLASS("itk::BinaryMask3DMeshSource")

  WRAP_INCLUDE_TYPE("itkDefaultStaticMeshTraits.h")
  WRAP_INCLUDE_TYPE("itkDefaultDynamicMeshTraits.h")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToMeshFilter_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToMeshFilter_WRAPPER.cxx.in)

  FOREACH(d "3")
    FOREACH(m ${WRAP_ITK_MESH_PIXELS})
      FOREACH(i ${WRAP_ITK_SCALAR})
        WRAP_TEMPLATE("${ITKM_I${i}${d}}${ITKM_M${m}${d}S}"  "${ITKT_I${i}${d}},${ITKT_M${m}${d}S}")
        WRAP_TEMPLATE("${ITKM_I${i}${d}}${ITKM_M${m}${d}D}"  "${ITKT_I${i}${d}},${ITKT_M${m}${d}D}")
      ENDFOREACH(i)
    ENDFOREACH(m)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("ObjectValue" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the object value of the mask to convert to a mesh.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputPixelType>( m_PointerToNative->GetObjectValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetObjectValue( itk::ManagedTypes::ToNativePixel<NativeType::InputPixelType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("NumberOfNodes" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the number of nodes/points in the resultant mesh.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfNodes();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("NumberOfCells" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the number of cells in the resultant mesh.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfCells();")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
