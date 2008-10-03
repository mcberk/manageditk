http://code.google.com/p/manageditk/
Dan Mueller
dan [dot] muel [at] gmail [dot] com
October 2008


== Description ==
ManagedITK generates wrappers around ITK for .NET languages.
These wrappers can be used with any CLR language, including C#,
VB.NET, IronPython, and others. ManagedITK is useful for a number
of reasons, including the ability to rapidly create graphical user
interfaces using Windows Forms (also known as System.Windows.Forms).

See Copyright.txt for copyright details.

See ChangeLog.txt for list of changes.

The Article folder contains the original Insight Journal article. This
article provides a good starting point for building and using ManagedITK.
http://insight-journal.org/browse/publication/151

The Example folder contains a number of example projects. The ManagedITK
assembly paths are hard-coded into the *.csproj files, and may need to be
manually edited to compile the examples.

The Images folder contains a number of example images used in the article
and examples.

The Patch folder contains instructions and files to patch ITK.

The Source folder contains the source files for generating the ManagedITK
assemblies.

The Utilities folder contains some utilities required to build ManagedITK.


== Build Instructions ==

1. Download Source
Source files can be downloaded from: http://code.google.com/p/manageditk/

2. Unzip Source (if required)
Unzip the source to a folder, such as C:/Insight-Toolkit/Wrapping/ManagedITK.

3. Patch ITK
Follow the instructions in the Patch folder to patch your ITK source to fix
bugs caused by the Visual Studio compiler. Hopefully these patches will be
included in the ITK CVS source in the near future.

4. Configure and Build ITK
Configure (with CMake) and build ITK 3.2.0 or greater with ITK_USE_REVIEW =ON.

5. Configure ManagedITK
Open CMake and set the source-code to the folder containing the unzipped source
and the build path to the desired location (as of v3.2.0.2 ManagedITK supports
both in-source and out-of-source builds). Click the Configure button and select
"Visual Studio 8 2005" Set the ITK_DIR, MANAGED_ITK_ASSEMLY_PREFIX, and WRAP_*
variables as desired. Click the OK button to finish the configuration.

6. Convert to Managed Projects
BEFORE opening the projects, run the FinishCMake.bat file located in the build folder.
Because CMake does not support managed projects, this batch file is required to convert
the generated vcproj files into managed projects.

7. Open Solution
Open the ManagedITK.sln solution file. If you have a multi-core processor, set the parallel
project build option as desired. To configure this feature, go to Tools > Options > Projects
and Solutions > Build and Run and type the maximum number of parallel builds in the text box.

8. Build Projects
Build all the projects by right-clicking ALL BUILD and selecting Build. The ALL BUILD
project automatically builds all the projects taking care of dependencies.