WRAP_CLASS("itk::VersorRigid3DTransform")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMatrixOffsetTransform_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedMatrixOffsetTransform_WRAPPER.cxx.in)

  WRAP_TEMPLATE("${ITKM_D}3" "${ITKT_D}")

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

  BEGIN_MANAGED_PROPERTY("Rotation" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the rotation part of the transform (using a versor).")
    SET(MANAGED_PROPERTY_TYPE      "itkVersor^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedVersor( m_PointerToNative->GetVersor() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetRotation( itk::ManagedTypes::ToNativeVersor(value) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
