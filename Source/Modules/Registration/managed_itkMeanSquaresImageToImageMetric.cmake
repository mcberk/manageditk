WRAP_CLASS("itk::MeanSquaresImageToImageMetric")

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedImageToImageMetric_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_USIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_SIGN_INT(2 2+)
  WRAP_IMAGE_FILTER_REAL(2 2+)

END_WRAP_CLASS()
