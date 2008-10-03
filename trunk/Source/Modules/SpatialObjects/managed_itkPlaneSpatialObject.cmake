WRAP_CLASS("itk::PlaneSpatialObject")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SO")

  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}" "${d}")
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("LowerPoint" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set one corner of the plane.")
    SET(MANAGED_PROPERTY_TYPE      "itkPoint^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPoint<NativeType::PointType::PointDimension>( m_PointerToNative->GetLowerPoint() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLowerPoint( itk::ManagedTypes::ToNativePoint<NativeType::PointType::PointDimension>(value) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("UpperPoint" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set another corner of the plane.")
    SET(MANAGED_PROPERTY_TYPE      "itkPoint^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPoint<NativeType::PointType::PointDimension>( m_PointerToNative->GetUpperPoint() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetUpperPoint( itk::ManagedTypes::ToNativePoint<NativeType::PointType::PointDimension>(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
