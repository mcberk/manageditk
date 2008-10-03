WRAP_CLASS("itk::GrayscaleMorphologicalOpeningImageFilter")

  WRAP_INCLUDE_TYPE("itkFlatStructuringElement.h")

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})
      WRAP_TEMPLATE("${ITKM_I${t}${d}}${ITKM_I${t}${d}}"
                    "${ITKT_I${t}${d}},${ITKT_I${t}${d}},${ITKT_FSE${d}}")
    ENDFOREACH(t)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("Kernel" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the structuring element.")
    SET(MANAGED_PROPERTY_TYPE      "itkFlatStructuringElement^")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetKernel( *((NativeType::KernelType*)value->NativePointer.ToPointer()) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
