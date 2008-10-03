WRAP_CLASS("itk::PermuteAxesImageFilter")

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)
  
  BEGIN_MANAGED_METHOD("SetOrder")
    SET(MANAGED_METHOD_SUMMARY         "Set the permutation order.  The elements of order must be a rearrangement of the numbers from 0 to ImageDimension-1.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "... array<unsigned int>^ order")
    SET(MANAGED_METHOD_TYPE_BODY       "m_PointerToNative->SetOrder( itk::ManagedTypes::ToNativeFixedArray<unsigned int, NativeType::InputImageType::ImageDimension>(order) );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetOrder(order);")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
