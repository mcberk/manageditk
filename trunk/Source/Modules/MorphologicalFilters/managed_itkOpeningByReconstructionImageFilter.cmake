WRAP_CLASS("itk::OpeningByReconstructionImageFilter")

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

  BEGIN_MANAGED_PROPERTY("FullyConnected" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set whether the connected components are defined strictly by face connectivity or by face+edge+vertex connectivity. Default is FullyConnectedOff. For objects that are 1 pixel wide, use FullyConnectedOn.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetFullyConnected();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetFullyConnected(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("PreserveIntensities" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set whether the original intensities of the image retained for those pixels unaffected by the opening by reconstrcution. If Off, the output pixel contrast will be reduced.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetPreserveIntensities();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetPreserveIntensities(value);")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
