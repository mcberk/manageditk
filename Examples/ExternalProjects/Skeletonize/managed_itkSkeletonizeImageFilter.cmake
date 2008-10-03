# Begin the wrapping
WRAP_CLASS("itk::SkeletonizeImageFilter")

  # Wrap the class for INT and REAL types
  WRAP_IMAGE_FILTER_INT(2)
  WRAP_IMAGE_FILTER_REAL(2)

  # Create a method body
  SET(body "")
  SET(body "${body}m_PointerToNative->SetOrderingImage( ")
  SET(body "${body}(NativeType::OrderingImageType*)image->NativePointer.ToPointer()")
  SET(body "${body} );")

  # Emit a managed method
  BEGIN_MANAGED_METHOD("SetOrderingImage")
    SET(MANAGED_METHOD_SUMMARY      "Set the ordering (ie. distance) image.")
    SET(MANAGED_METHOD_RETURN_TYPE  "void")
    SET(MANAGED_METHOD_PARAMS       "itkImageBase^ image")
    SET(MANAGED_METHOD_TYPE_BODY    "${body}")
    SET(MANAGED_METHOD_WRAPPER_BODY "iInstance->SetOrderingImage( image );")
  END_MANAGED_METHOD()

  # Create a method body
  SET(body "")
  SET(body "${body}m_PointerToNative->SetOrderingImage( ")
  SET(body "${body}(NativeType::OrderingImageType*)imgPtr.ToPointer()")
  SET(body "${body} );")

  # Emit a managed method
  BEGIN_MANAGED_METHOD("SetOrderingImage")
    SET(MANAGED_METHOD_SUMMARY      "Set the ordering (ie. distance) image.")
    SET(MANAGED_METHOD_RETURN_TYPE  "void")
    SET(MANAGED_METHOD_PARAMS       "IntPtr imgPtr")
    SET(MANAGED_METHOD_TYPE_BODY    "${body}")
    SET(MANAGED_METHOD_WRAPPER_BODY "iInstance->SetOrderingImage( imgPtr );")
  END_MANAGED_METHOD()

# End the wrapping
END_WRAP_CLASS()