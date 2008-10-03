WRAP_CLASS("itk::ImageMomentsCalculator")

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedCalculator_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedCalculator_WRAPPER.cxx.in)

  BEGIN_MANAGED_PROPERTY("TotalMass" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Return the total mass (or zeroth moment) of an image. This property returns the sum of pixel intensities (also known as the zeroth moment or the total mass) of the image whose moments were last computed by this object. NOTE: This property is only valid after calling Compute().")
    SET(MANAGED_PROPERTY_TYPE      "double")
    SET(MANAGED_PROPERTY_GET_BODY  "return m_PointerToNative->GetTotalMass();")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("FirstMoments" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Return first moments about origin, in index coordinates. This property returns the first moments around the origin of the image whose moments were last computed by this object. For simplicity, these moments are computed in index coordinates rather than physical coordinates. NOTE: This property is only valid after calling Compute().")
    SET(MANAGED_PROPERTY_TYPE      "itkVector^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedVector<NativeType::ImageDimension>( m_PointerToNative->GetFirstMoments() );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("SecondMoments" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Return second moments about origin, in index coordinates. This property returns the second moments around the origin of the image whose moments were last computed by this object. For simplicity, these moments are computed in index coordinates rather than physical coordinates. NOTE: This property is only valid after calling Compute().")
    SET(MANAGED_PROPERTY_TYPE      "itkMatrix^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedMatrix<NativeType::ScalarType, NativeType::ImageDimension, NativeType::ImageDimension>( m_PointerToNative->GetSecondMoments() );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("CenterOfGravity" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Return center of gravity, in physical coordinates. This property returns the center of gravity of the image whose moments were last computed by this object. The center of gravity is computed in physical coordinates. NOTE: This property is only valid after calling Compute().")
    SET(MANAGED_PROPERTY_TYPE      "itkVector^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedVector<NativeType::ImageDimension>( m_PointerToNative->GetCenterOfGravity() );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("CentralMoments" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Return second central moments, in physical coordinates. This property returns the central second moments of the image whose moments were last computed by this object. The central moments are computed in physical coordinates. NOTE: This property is only valid after calling Compute().")
    SET(MANAGED_PROPERTY_TYPE      "itkMatrix^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedMatrix<NativeType::ScalarType, NativeType::ImageDimension, NativeType::ImageDimension>( m_PointerToNative->GetCentralMoments() );")
  END_MANAGED_PROPERTY()
  
  BEGIN_MANAGED_PROPERTY("PrincipalMoments" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Return principal moments, in physical coordinates. This property returns the principal moments of the image whose moments were last computed by this object. The moments are returned as a vector, with the principal moments ordered from smallest to largest. The moments are computed in physical coordinates. NOTE: This property is only valid after calling Compute().")
    SET(MANAGED_PROPERTY_TYPE      "itkVector^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedVector<NativeType::ImageDimension>( m_PointerToNative->GetPrincipalMoments() );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("PrincipalAxes" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Return principal axes, in physical coordinates. This property returns the principal axes of the image whose moments were last computed by this object. The moments are returned as an orthogonal matrix, each row of which corresponds to one principal moment. The moments are computed in physical coordinates. NOTE: This property is only valid after calling Compute().")
    SET(MANAGED_PROPERTY_TYPE      "itkMatrix^")
    SET(MANAGED_PROPERTY_GET_BODY  "return itk::ManagedTypes::ToManagedMatrix<NativeType::ScalarType, NativeType::ImageDimension, NativeType::ImageDimension>( m_PointerToNative->GetPrincipalAxes() );")
  END_MANAGED_PROPERTY()

END_WRAP_CLASS()
