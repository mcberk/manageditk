using System;
using itk;

using InterpolatorType = itk.itkHammingWindowedSincInterpolateImageFunction;
using RadiusType = itk.itkRadius;

namespace itk.Examples.Interpolators
{
/// <summary>
/// This example shows how to use an itkInterpolateImageFunction to
/// sample an image at a given physical location.
/// </summary>
static class Linear1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Read an explicitly typed image
            itkImageBase image = itkImage_F2.New();
            image.Read(args[0]);

            // Create the interpolator
            RadiusType radius = new RadiusType(4);
            InterpolatorType interp = InterpolatorType.New(image, radius);
            interp.SetInputImage(image);
            
            // Sample the image at a given physical location
            itkPoint point = new itkPoint(127.5, 127.5);
            itkPixel pixel = interp.Evaluate(point);
            Console.WriteLine(point.ToString() + "=" + pixel.ToString());

            // Clean up
            image.Dispose();
            interp.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    } // end main
} // end class
} // end namespace