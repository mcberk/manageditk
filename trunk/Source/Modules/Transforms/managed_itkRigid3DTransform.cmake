WRAP_CLASS("itk::Rigid3DTransform")

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

END_WRAP_CLASS()
