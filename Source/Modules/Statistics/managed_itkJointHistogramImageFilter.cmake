# Begin the wrapping
WRAP_CLASS("itk::JointHistogramImageFilter")

  SET(body "")
  SET(body "${body}public enum class HistogramToImageMappingEnum\n")
  SET(body "${body}{\n")
  SET(body "${body}\tIntensity,\n")
  SET(body "${body}\tEntropy,\n")
  SET(body "${body}\tProbability,\n")
  SET(body "${body}\tLogProbability\n")
  SET(body "${body}};\n")
  SET(MANAGED_EXTRA_WRAPPER_CONFIG "${body}")
  
  SET(body "")
  SET(body "${body}private ref class HistogramToImageMappingHelper_${AT}MANGLED_SUFFIX${AT}\n")
  SET(body "${body}{\n")
  SET(body "${body}public:\n")
  SET(body "${body}\tstatic itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::HistogramToImageMappingEnum ToNativeHistogramToImageMapping( itk::HistogramToImageMappingEnum managedName )\n")
  SET(body "${body}\t{\n")
  SET(body "${body}\t\tswitch (managedName)\n")
  SET(body "${body}\t\t{\n")
  SET(body "${body}\t\tcase itk::HistogramToImageMappingEnum::Intensity: return itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::Intensity;\n")
  SET(body "${body}\t\tcase itk::HistogramToImageMappingEnum::Entropy: return itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::Entropy;\n")
  SET(body "${body}\t\tcase itk::HistogramToImageMappingEnum::Probability: return itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::Probability;\n")
  SET(body "${body}\t\tcase itk::HistogramToImageMappingEnum::LogProbability: return itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::LogProbability;\n")
  SET(body "${body}\t\t}\n")
  SET(body "${body}\t\tthrow gcnew NotSupportedException(\"The given mapping is not supported.\");\n")
  SET(body "${body}\t}\n")
  SET(body "${body}\t\n")
  SET(body "${body}\tstatic itk::HistogramToImageMappingEnum ToManagedHistogramToImageMapping( itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::HistogramToImageMappingEnum nativeName )\n")
  SET(body "${body}\t{\n")
  SET(body "${body}\t\tswitch (nativeName)\n")
  SET(body "${body}\t\t{\n")
  SET(body "${body}\t\tcase itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::Intensity: return itk::HistogramToImageMappingEnum::Intensity;\n")
  SET(body "${body}\t\tcase itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::Entropy: return itk::HistogramToImageMappingEnum::Entropy;\n")
  SET(body "${body}\t\tcase itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::Probability: return itk::HistogramToImageMappingEnum::Probability;\n")
  SET(body "${body}\t\tcase itk::JointHistogramImageFilter< ${AT}TEMPLATE_PARAMS${AT} >::LogProbability: return itk::HistogramToImageMappingEnum::LogProbability;\n")
  SET(body "${body}\t\t}\n")
  SET(body "${body}\t\tthrow gcnew NotSupportedException(\"The given mapping is not supported.\");\n")
  SET(body "${body}\t}\n")
  SET(body "${body}};\n")
  SET(MANAGED_EXTRA_TYPE_CONFIG "${body}")

  # Wrap the class for SCALAR types
  FOREACH(d1 ${WRAP_ITK_DIMS})
    SET(d2 2)
      IF("${d1}" GREATER "${d2}" OR "${d1}" EQUAL "${d2}")
        FOREACH(t ${WRAP_ITK_SCALAR})
          WRAP_TEMPLATE("${ITKM_I${t}${d1}}${ITKM_I${t}${d2}}"
                        "${ITKT_I${t}${d1}},${ITKT_I${t}${d2}}")
        ENDFOREACH(t)
      ENDIF("${d1}" GREATER "${d2}" OR "${d1}" EQUAL "${d2}")
  ENDFOREACH(d1)

  BEGIN_MANAGED_PROPERTY("NumberOfBins" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the number of bins in the different directions. This array must be the same length as the number of inputs.")
    SET(MANAGED_PROPERTY_TYPE      "array<unsigned int>^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedCliArray<unsigned int>( m_PointerToNative->GetNumberOfBins() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetNumberOfBins( itk::ManagedTypes::ToNativeArray<unsigned int>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("MarginalScale" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the marginal scale value.")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMarginalScale( );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMarginalScale( value );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Mapping" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the histogram to image mapping type. Valid mappings are: Intensity, Entropy, Probability, and LogProbability.")
    SET(MANAGED_PROPERTY_TYPE      "itk::HistogramToImageMappingEnum")
    SET(MANAGED_PROPERTY_GET_BODY  "return HistogramToImageMappingHelper_${AT}MANGLED_SUFFIX${AT}::ToManagedHistogramToImageMapping( m_PointerToNative->GetMapping() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMapping( HistogramToImageMappingHelper_${AT}MANGLED_SUFFIX${AT}::ToNativeHistogramToImageMapping(value) );")
  END_MANAGED_PROPERTY()

# End the wrapping
END_WRAP_CLASS()