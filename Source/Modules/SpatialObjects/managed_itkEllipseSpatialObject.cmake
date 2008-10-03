WRAP_CLASS("itk::EllipseSpatialObject")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SO")

  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}" "${d}")
  ENDFOREACH(d)

  BEGIN_MANAGED_METHOD("SetRadius")
    SET(MANAGED_METHOD_SUMMARY         "Set all radii to the same radius value. Each radius is half the length of one axis of the ellipse.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "double radius")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetRadius( radius );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetRadius( radius );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_PROPERTY("Radius" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set array of radius values.")
    SET(MANAGED_PROPERTY_TYPE      "array<double>^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedFixedArray<double, NativeType::NumberOfDimension>( m_PointerToNative->GetRadius() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetRadius( itk::ManagedTypes::ToNativeFixedArray<double, NativeType::NumberOfDimension>(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
