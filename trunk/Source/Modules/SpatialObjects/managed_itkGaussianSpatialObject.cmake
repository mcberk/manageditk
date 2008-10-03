WRAP_CLASS("itk::GaussianSpatialObject")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SO")

  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}" "${d}")
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("Radius" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the radius.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetRadius();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetRadius( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Maximum" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the maximum value of the Gaussian (its value at the origin of the spatial object coordinate system).")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMaximum();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMaximum( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
