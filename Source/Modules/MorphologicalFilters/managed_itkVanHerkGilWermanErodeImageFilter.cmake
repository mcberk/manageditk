WRAP_CLASS("itk::VanHerkGilWermanErodeImageFilter")

  WRAP_INCLUDE_TYPE("itkFlatStructuringElement.h")
  
  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR})
      WRAP_TEMPLATE("${ITKM_I${t}${d}}"
                    "${ITKT_I${t}${d}},${ITKT_FSE${d}}")
    ENDFOREACH(t)
  ENDFOREACH(d)
  
  BEGIN_MANAGED_PROPERTY("Kernel" SET)
    SET(MANAGED_PROPERTY_SUMMARY   "Set the structuring element.")
    SET(MANAGED_PROPERTY_TYPE      "itkFlatStructuringElement^")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetKernel( *((NativeType::KernelType*)value->NativePointer.ToPointer()) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Boundary" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the boundary.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputImagePixelType>( m_PointerToNative->GetBoundary() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetBoundary( itk::ManagedTypes::ToNativePixel<NativeType::InputImagePixelType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
