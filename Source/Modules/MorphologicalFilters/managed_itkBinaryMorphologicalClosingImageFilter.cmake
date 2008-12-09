WRAP_CLASS("itk::BinaryMorphologicalClosingImageFilter")
  
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

  BEGIN_MANAGED_PROPERTY("ForegroundValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the value considered as foreground.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::InputImageType::PixelType>( m_PointerToNative->GetForegroundValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetForegroundValue( itk::ManagedTypes::ToNativePixel<NativeType::InputImageType::PixelType>( value ) );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("SafeBorder" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set whether a safe border is added to input image to avoid borders effects and removed it once the closing is done.")
    SET(MANAGED_PROPERTY_TYPE      "bool")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetSafeBorder();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetSafeBorder( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
