WRAP_CLASS("itk::SpatialObjectReader")

  WRAP_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED( "itkManagedSceneSpatialObject.cxx" )
  WRAP_INCLUDE_TYPE_AFTER_PRAGMA_MANAGED( "itkManagedGroupSpatialObject.cxx" )
  WRAP_INCLUDE_WRAPPER( "itkManagedSceneSpatialObject.cxx" )
  WRAP_INCLUDE_WRAPPER( "itkManagedGroupSpatialObject.cxx" )

  SET(MANAGED_TYPE_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedObject_TYPE.cxx.in)
  SET(MANAGED_WRAPPER_TEMPLATE ${MANAGED_ITK_SOURCE_COMMON_PATH}/itkManagedObject_WRAPPER.cxx.in)

  FOREACH(d ${WRAP_ITK_DIMS})
    FOREACH(t ${WRAP_ITK_SCALAR_NO_BOOL})
      WRAP_TEMPLATE("${ITKM_${t}}${d}" "${d},${ITKT_${t}}")
    ENDFOREACH(t)
  ENDFOREACH(d)

  BEGIN_MANAGED_PROPERTY("FileName" GETSET)
    SET(MANAGED_PROPERTY_SUMMARY   "Specify the file to read. This is forwarded to the IO instance.")
    SET(MANAGED_PROPERTY_TYPE      "String^")
    SET(MANAGED_PROPERTY_GET_BODY  "return gcnew String( m_PointerToNative->GetFileName() );")
    SET(MANAGED_PROPERTY_SET_BODY  "std::string stdvalue; ManagedTypes::ToNativeString( value, stdvalue ); m_PointerToNative->SetFileName( stdvalue.c_str() );")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Scene" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the read scene.")
    SET(MANAGED_PROPERTY_TYPE      "itkSceneSpatialObject^")
    SET(MANAGED_PROPERTY_GET_BODY  "itkSceneSpatialObject^ scene = itkSceneSpatialObject::New( NativeType::SpatialObjectType::ObjectDimension ); scene->NativePointer = IntPtr((NativeType::SceneType*)this->m_PointerToNative->GetScene( )); return scene;")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_PROPERTY("Group" GET)
    SET(MANAGED_PROPERTY_SUMMARY   "Get the read group.")
    SET(MANAGED_PROPERTY_TYPE      "itkGroupSpatialObject^")
    SET(MANAGED_PROPERTY_GET_BODY  "itkGroupSpatialObject^ group = itkGroupSpatialObject::New( NativeType::SpatialObjectType::ObjectDimension ); group->NativePointer = IntPtr((NativeType::GroupType*)this->m_PointerToNative->GetGroup( )); return group;")
  END_MANAGED_PROPERTY()

  BEGIN_MANAGED_METHOD("Update")
    SET(MANAGED_METHOD_SUMMARY         "Update the reader object.")
    SET(MANAGED_METHOD_RETURN_TYPE     "void")
    SET(MANAGED_METHOD_PARAMS          "void")
    SET(MANAGED_METHOD_TYPE_BODY       "try{ this->m_PointerToNative->Update( ); } catch ( itk::ExceptionObject& ex ){ throw gcnew itkExceptionObject( ex.GetDescription(), ex.GetLocation(), ex.GetFile(), ex.GetLine() ); }")
    SET(MANAGED_METHOD_WRAPPER_BODY    "iInstance->Update( );")
  END_MANAGED_METHOD()

END_WRAP_CLASS()
