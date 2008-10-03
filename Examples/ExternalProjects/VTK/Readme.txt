This external project creates wrappers around the itkImageToVTKImageFilter
an itkVTKImageToImageFilter classes. This external project is especially
designed for interoperability with vtkdotnet (a wrapper around VTK for .NET).
     http://vtkdotnet.sourceforge.net/

To build this external project, follow these steps:
  0. Ensure the ITK applications have been installed in the Applications folder
  1. Follow the steps described in the article for building ManagedITK
     (By the end of this step you should have built ITK and ManagedITK)
  2. Download and build the vtkdotnet source code (VTK-5.0.1-wrap-1.1-src)
  3. Configure the ManagedITK VTK external project using CMake
  4. Specify the ManagedITK_DIR and VTK_DIR options as the build folders
  5. Generate the external project
  6. Build the project
  
NOTE: It is important the ManagedITK VTK project is built against the
same version of VTK which was used to generate the vtkdotnet assemblies.
Using a different version will result in strange runtime issues.