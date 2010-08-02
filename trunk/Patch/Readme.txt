This folder contains a number of patches which must be applied to successfully build
some parts of ManagedITK.

INSTRUCTIONS:
1. Download the patch program from http://gnuwin32.sourceforge.net/ (click Packages, then Patch)
2. Add patch to your PATH environment variable (eg. PATH=%PATH%;C:/Utils/GnuWin32/bin)
3. Apply each patch in this directory to your ITK source

Example:
cd D:\ManagedITK\Patch
patch D:\InsightToolkit-3.20.0\Code\Common\itkShapedNeighborhoodIterator.h < itkShapedNeighborhoodIterator.h.patch
patch D:\InsightToolkit-3.20.0\Code\Common\itkConstShapedNeighborhoodIterator.h < itkConstShapedNeighborhoodIterator.h.patch
patch D:\InsightToolkit-3.20.0\Code\Common\itkVersorTransform.txx < itkVersorTransform.txx.patch

NOTE:
These patches were generated using the "diff --text" command.
