# Begin the wrapping
WRAP_CLASS("itk::VTKImageToImageFilter")

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
  BEGIN_MANAGED_METHOD("GetOutput")
    SET(MANAGED_METHOD_SUMMARY         "Get the output as an ITK image.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "itk::itkDataObject^ output")
    SET(MANAGED_METHOD_TYPE_BODY       "output->NativePointer = IntPtr((NativeType::OutputImageType*)this->m_PointerToNative->GetOutput());")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->GetOutput( output );")
  END_MANAGED_METHOD()
  
  # Emit method
  BEGIN_MANAGED_METHOD("SetInput")
    SET(MANAGED_METHOD_SUMMARY         "Set the input in the form of a vtkImageData.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "vtk::vtkImageData^ input")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->SetInput( reinterpret_cast<vtkImageData*>(input->GetNativePointer().ToPointer()) );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput( input );")
  END_MANAGED_METHOD()

  # Emit method
  BEGIN_MANAGED_METHOD("SetInput")
    SET(MANAGED_METHOD_SUMMARY         "Set the input as an IntPtr to vtkImageData.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "IntPtr input")
    SET(MANAGED_METHOD_TYPE_BODY       "this->m_PointerToNative->SetInput( reinterpret_cast<vtkImageData*>(input.ToPointer()) );")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->SetInput( input );")
  END_MANAGED_METHOD()


# End the wrapping
END_WRAP_CLASS()