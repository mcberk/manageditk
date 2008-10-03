WRAP_CLASS("itk::SpatialObject")

  ADD_MANAGED_DEPENDENCY(${MANAGED_ITK_ASSEMBLY_PREFIX}.Transforms)

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedSpatialObject_WRAPPER.cxx.in)
  SET(MANGLED_PREFIX "SO")

  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${d}" "${d}")
  ENDFOREACH(d)

#   BEGIN_MANAGED_METHOD("Translate")
#     SET(MANAGED_METHOD_SUMMARY         "This method modifies self to include a translation of the origin. The translation is precomposed with self if pre is true, and postcomposed otherwise.")
#     SET(MANAGED_METHOD_RETURN_TYPE     "void")
#     SET(MANAGED_METHOD_PARAMS          "itkVector^ offset, bool pre")
#     SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->Translate( itk::ManagedTypes::ToNativeVector<OutputVectorType::Dimension>(offset), pre );")
#     SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->Translate( offset, pre );")
#   END_MANAGED_METHOD()

#   BEGIN_MANAGED_PROPERTY("Angle" GETSET)
#     SET(MANAGED_PROPERTY_SUMMARY   "Get/set the angle of rotation in radians.")
#     SET(MANAGED_PROPERTY_TYPE      "double")
#     SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetAngle();")
#     SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetAngle( value );")
#   END_MANAGED_PROPERTY()

END_WRAP_CLASS()
