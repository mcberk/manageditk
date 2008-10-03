This folder contains a number of patches which must be applied to successfully build
some parts of ManagedITK.

INSTRUCTIONS:
1. Download the patch program from http://gnuwin32.sourceforge.net/ (click Packages, then Patch)
2. Add patch to your PATH environment variable (eg. PATH=%PATH%;C:/Utils/GnuWin32/bin)
3. Apply each patch in this directory to your ITK source

Example:
cd C:\ManagedITK\Patch
patch C:\ITK\Code\Common\itkShapedNeighborhoodIterator.h < itkShapedNeighborhoodIterator.h.patch
patch C:\ITK\Code\Common\itkConstShapedNeighborhoodIterator.h < itkConstShapedNeighborhoodIterator.h.patch
