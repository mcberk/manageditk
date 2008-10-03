WRAP_CLASS("itk::TileImageFilter")

  FOREACH(d1 ${WRAP_ITK_DIMS})
    FOREACH(d2 ${WRAP_ITK_DIMS})
      IF("${d1}" LESS "${d2}" OR "${d1}" EQUAL "${d2}")
        UNIQUE (types "${WRAP_ITK_SCALAR}")
        FOREACH(t ${types})
          WRAP_TEMPLATE("${ITKM_I${t}${d1}}${ITKM_I${t}${d2}}"
                        "${ITKT_I${t}${d1}},${ITKT_I${t}${d2}}")
        ENDFOREACH(t)
      ENDIF("${d1}" LESS "${d2}" OR "${d1}" EQUAL "${d2}")
    ENDFOREACH(d2)
  ENDFOREACH(d1)

  BEGIN_MANAGED_PROPERTY("Layout" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the layout of the tiles. If the last Layout value is 0, the filter will compute a value that will accomodate all of the images. To create a volume from a series of inputs specify a layout of 1,1,0.")
    SET(MANAGED_PROPERTY_TYPE      "array<unsigned int>^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedFixedArray<unsigned int, NativeType::OutputImageDimension>( m_PointerToNative->GetLayout() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetLayout( itk::ManagedTypes::ToNativeFixedArray<unsigned int, NativeType::OutputImageDimension>(value) );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("DefaultPixelValue" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get/set the pixel value for locations that are not covered by an input image. The default default pixel value is zero.")
    SET(MANAGED_PROPERTY_TYPE      "itkPixel^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedPixel<NativeType::OutputPixelType>( m_PointerToNative->GetDefaultPixelValue() );")
    SET(MANAGED_PROPERTY_SET_BODY  "m_PointerToNative->SetDefaultPixelValue( itk::ManagedTypes::ToNativePixel<NativeType::OutputPixelType>( value ) );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
