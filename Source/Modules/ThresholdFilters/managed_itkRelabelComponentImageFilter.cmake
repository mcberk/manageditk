WRAP_CLASS("itk::RelabelComponentImageFilter")
  WRAP_IMAGE_FILTER_USIGN_INT(2)
  WRAP_IMAGE_FILTER_SIGN_INT(2)
  
  # Wrap from ulong to other integral types, even if ulong isn't wrapped. This
  # is needed to be able to use image from watershed image filter.
  IF(NOT WRAP_unsigned_long)
    WRAP_IMAGE_FILTER_COMBINATIONS("UL" "${WRAP_ITK_INT};UL")
  ENDIF(NOT WRAP_unsigned_long)
  
  BEGIN_MANAGED_PROPERTY("MinimumObjectSize" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the minimum size of objects to keep after the relabel operation.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetMinimumObjectSize();")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetMinimumObjectSize(value);")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("NumberOfObjects" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the final number of relabelled objects (ie. after filtering small objects with MinimumObjectSize). This property is only valid after the filter has been executed.")
    SET(MANAGED_PROPERTY_TYPE      "unsigned long")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetNumberOfObjects();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("GetSizeOfObjectInPixels")
    SET(MANAGED_METHOD_SUMMARY         "Get the size of each object in pixels. This information is only valid after the filter has executed.  Size of the background is not calculated.  Size of object #1 is GetSizeOfObjectsInPixels()[0]. Size of object #2 is GetSizeOfObjectsInPixels()[1]. Etc.")
    SET(MANAGED_METHOD_RETURN_TYPE     "unsigned long")
    SET(MANAGED_METHOD_PARAMS          "unsigned long obj")
    SET(MANAGED_METHOD_TYPE_BODY       "return m_PointerToNative->GetSizeOfObjectInPixels(obj);")
    SET(MANAGED_METHOD_WRAPPER_BODY   "return iInstance->GetSizeOfObjectInPixels(obj);")
  END_MANAGED_METHOD()

  BEGIN_MANAGED_METHOD("GetSizeOfObjectInPhysicalUnits")
    SET(MANAGED_METHOD_SUMMARY         "Get the size of each object in physical space (in units of pixel size). This information is only valid after the filter has executed. Size of the background is not calculated.  Size of object #1 is GetSizeOfObjectsInPhysicalUnits()[0]. Size of object #2 is GetSizeOfObjectsInPhysicalUnits()[1]. Etc.")
    SET(MANAGED_METHOD_RETURN_TYPE     "float")
    SET(MANAGED_METHOD_PARAMS          "unsigned long obj")
    SET(MANAGED_METHOD_TYPE_BODY       "return m_PointerToNative->GetSizeOfObjectInPhysicalUnits(obj);")
    SET(MANAGED_METHOD_WRAPPER_BODY   "return iInstance->GetSizeOfObjectInPhysicalUnits(obj);")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
