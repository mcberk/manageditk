# Import default references
import System, clr, sys

# Import ITK references
clr.AddReference("ManagedITK.Common")
clr.AddReference("ManagedITK.Filtering.Common")
clr.AddReference("ManagedITK.Filtering.Intensity")
from itk import *

# Create aliases
ImageType = itkImage_F2
GradientFilterType = itkGradientMagnitudeRecursiveGaussianImageFilter
SigmoidFilterType  = itkSigmoidImageFilter
RescaleFilterType  = itkRescaleIntensityImageFilter

# Create the output image
output = ImageType.New( )

# Open input image
image = ImageType.New( )
image.Read( "BrainProtonDensitySlice.png" )

# Gradient Magnitude
filterGrad = GradientFilterType.New( image, image )
filterGrad.SetInput( image )
filterGrad.Sigma = 1.3
filterGrad.NormalizeAcrossScale = False

# Sigmoid
filterSigmoid = SigmoidFilterType.New( image, image )
filterSigmoid.SetInput( filterGrad.GetOutput() )
filterSigmoid.Alpha = -0.3
filterSigmoid.Beta  =  3.0

# Rescale
filterRescale = RescaleFilterType.New( image, image )
filterRescale.SetInput( filterSigmoid.GetOutput() )
filterRescale.OutputMinimum = itkPixel( image.PixelType,  0.0 )
filterRescale.OutputMaximum = itkPixel( image.PixelType,  1.0 )

# Write the output
filterRescale.GetOutput( output )
output.Write( "BrainProtonDensitySlice_SPEED.mhd" )