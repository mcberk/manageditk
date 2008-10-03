WRAP_CLASS("itk::VectorIndexSelectionCastImageFilter")

  # Wrap VectorImages types
  UNIQUE(to_types "UC;${WRAP_ITK_SCALAR_NO_BOOL}")
  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${to_types})
      WRAP_TEMPLATE("${ITKM_IVI${t}${d}}${ITKM_I${t}${d}}" "${ITKT_IVI${t}${d}},${ITKT_I${t}${d}}")
    ENDFOREACH(t)
  ENDFOREACH(d)

  # Wrap RGB image types
  IF(WRAP_rgb_unsigned_short AND WRAP_unsigned_short)
    WRAP_IMAGE_FILTER_TYPES(RGBUS US)
  ENDIF(WRAP_rgb_unsigned_short AND WRAP_unsigned_short)
  IF(WRAP_rgb_unsigned_char AND WRAP_unsigned_char)
    WRAP_IMAGE_FILTER_TYPES(RGBUC UC)
  ENDIF(WRAP_rgb_unsigned_char AND WRAP_unsigned_char)

  # Wrap RGBA image types
  # NOTE: There is currently no NumericTrait support for RGBA pixels.
  #       Including the below lines causes compile errors.
  #IF(WRAP_rgba_unsigned_short AND WRAP_unsigned_short)
  #  WRAP_IMAGE_FILTER_TYPES(RGBAUS US)
  #ENDIF(WRAP_rgba_unsigned_short AND WRAP_unsigned_short)
  #IF(WRAP_rgba_unsigned_char AND WRAP_unsigned_char)
  #  WRAP_IMAGE_FILTER_TYPES(RGBAUC UC)
  #ENDIF(WRAP_rgba_unsigned_char AND WRAP_unsigned_char)

  # Wrap Vector image types
  IF(WRAP_vector)
  UNIQUE(to_types "UC;${WRAP_ITK_SCALAR_NO_BOOL}")
  FOREACH(t ${to_types})
    WRAP_IMAGE_FILTER_TYPES(V${t} ${t})
  ENDFOREACH(t)
  ENDIF(WRAP_vector)

  # Wrap CovariantVector image types
  IF(WRAP_vector)
  UNIQUE(to_types "UC;${WRAP_ITK_SCALAR_NO_BOOL}")
  FOREACH(t ${to_types})
    WRAP_IMAGE_FILTER_TYPES(CV${t} ${t})
  ENDFOREACH(t)
  ENDIF(WRAP_vector)

  BEGIN_MANAGED_PROPERTY("Index" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the element index to select.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned int")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetIndex();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetIndex( value );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
