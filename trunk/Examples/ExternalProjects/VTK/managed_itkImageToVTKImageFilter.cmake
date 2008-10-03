# Begin the wrapping
WRAP_CLASS("itk::ImageToVTKImageFilter")

  # Setup VTK includes and targets
  INCLUDE_DIRECTORIES( BEFORE ${ITK_SOURCE_DIR}/Applications/Auxiliary/vtk )
  SET( WRAPPER_LINK_LIBRARIES vtkCommon vtkImaging vtkFiltering )
  WRAP_USE_NAMESPACE_WRAPPER( vtkCommonDotNet )
  WRAP_USE_NAMESPACE_WRAPPER( vtkFilteringDotNet )

  # Wrap as ProcessObject
  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedProcessObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedProcessObject_WRAPPER.cxx.in)

  WRAP_IMAGE_FILTER_USIGN_INT(1)
  WRAP_IMAGE_FILTER_SIGN_INT(1)
  WRAP_IMAGE_FILTER_REAL(1)

  # Emit method
  BEGIN_MANAGED_METHOD("SetInput")
    SET(MANAGED_METHOD_SUMMARY         "Set the input as an ITK image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itk::itkDataObject^ input")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->SetInput( (NativeType::InputImageType*)input->NativePointer.ToPointer() );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput( input );")
  END_MANAGED_METHOD()

  # Emit method
  BEGIN_MANAGED_METHOD("GetOutput")
    SET(MANAGED_METHOD_SUMMARY         "Get the output in the form of a vtkImageData.")
    SET(MANAGED_METHOD_RETURN_TYPE     "vtk::vtkImageData^")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "return gcnew vtk::vtkImageData( IntPtr((vtkImageData*)this->m_PointerToNative->GetOutput()), false );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "return iInstance->GetOutput( );")
  END_MANAGED_METHOD()

  # Emit method
  BEGIN_MANAGED_METHOD("GetOutputAsIntPtr")
    SET(MANAGED_METHOD_SUMMARY         "Get the output in the form of an IntPtr to vtkImageData.")
    SET(MANAGED_METHOD_RETURN_TYPE     "IntPtr")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "return IntPtr( this->m_PointerToNative->GetOutput() );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "return iInstance->GetOutputAsIntPtr( );")
  END_MANAGED_METHOD()

# End the wrapping
END_WRAP_CLASS()