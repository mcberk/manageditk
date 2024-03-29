WRAP_CLASS("itk::TranslationTransform")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedTransform_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedTransform_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    WRAP_TEMPLATE("${ITKM_D}${d}" "${ITKT_D},${d}")
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("Offset" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the transform offset.")
    SET(MANAGED_PROPERTY_TYPE      "itkVector^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedVector<OutputVectorType::Dimension>( m_PointerToNative->GetOffset() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetOffset( itk::ManagedTypes::ToNativeVector<OutputVectorType::Dimension>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("Translate")
    SET(MANAGED_METHOD_SUMMARY         "This method modifies self to include a translation of the origin. The translation is precomposed with self if pre is true, and postcomposed otherwise.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkVector^ offset, bool pre")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->Translate( itk::ManagedTypes::ToNativeVector<OutputVectorType::Dimension>(offset), pre );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->Translate( offset, pre );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("Translate")
    SET(MANAGED_METHOD_SUMMARY         "This method modifies self to include a translation of the origin. The translation is postcomposed.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itkVector^ offset")
    SET(MANAGED_METHOD_TYPE_BODY       "this->Translate( offset, false );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->Translate( offset, false );")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("SetIdentity")
    SET(MANAGED_METHOD_SUMMARY         "Set the transform to identity.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetIdentity();")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetIdentity();")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
