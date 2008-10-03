WRAP_CLASS("itk::VectorCastImageFilter")

  # Create casts between vector types
  UNIQUE(types "${WRAP_ITK_VECTOR}")
  WRAP_IMAGE_FILTER_COMBINATIONS("${types}" "${types}")

END_WRAP_CLASS()

