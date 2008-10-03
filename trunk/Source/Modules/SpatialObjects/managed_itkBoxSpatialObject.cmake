WRAP_CLASS("itk::BoxSpatialObject")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SO")

  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}" "${d}")
  ENDFOREACH(d)
  
  BEGIN_MANAGED_PROPERTY("Size" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the size of the box spatial object.")
    SET(MANAGED_PROPERTY_TYPE      "array<double>^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedFixedArray<double, NativeType::PointType::PointDimension>( m_PointerToNative->GetSize() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSize( itk::ManagedTypes::ToNativeFixedArray<double, NativeType::PointType::PointDimension>(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
