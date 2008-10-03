using System;
using itk;

namespace itk.Examples.Images
{
/// <summary>
/// This example shows how to allocate the memory for an image, and fill
/// the image with a given pixel value.
/// </summary>
static class Allocate1
{
    [STAThread]
    static void Main()
    {
        try
        {
            // In native ITK, images are templated over the pixel type
            // and number of dimensions. Templates are not supported by
            // the CLR, so therefore the creation of images with
            // ManagedITK is somewhat different. The wrapping process
            // creates two types of images: a number of explicit types
            // for various template combinations, and a wrapper type.
            // In this example we use an explicit type.

            // Create an image using an explicit type
            // Note: "UC2" stands for itk::Image< unsigned char, 2 >.
            itkImageBase image = itkImage_UC2.New();

            // Create some image information
            itkSize size = new itkSize(128, 128);
            itkSpacing spacing = new itkSpacing(1.0, 1.0);
            itkIndex index = new itkIndex(0, 0);
            itkPoint origin = new itkPoint(0.0, 0.0);
            itkImageRegion region = new itkImageRegion(size, index);

            // Set the information
            // Note: we must call SetRegions() *before* calling Allocate().
            image.SetRegions(region);
            image.Allocate();
            image.Spacing = spacing;
            image.Origin = origin;

            // Fill the image with gray (ie. 128)
            image.FillBuffer(128);

            // Test a pixel value
            itkPixel pixel = image.GetPixel(index);

            // Display some image information
            Console.WriteLine(String.Format("Image{0}={1}",index, pixel));
            Console.WriteLine(String.Format("PixelType={0}",image.PixelType));
            Console.WriteLine(String.Format("Dimension={0}",image.Dimension));
            Console.WriteLine(String.Format("Size={0}",image.Size));
            Console.WriteLine(String.Format("Spacing={0}",image.Spacing));
            Console.WriteLine(String.Format("Origin={0}",image.Origin));
            Console.WriteLine("======================================");
            Console.WriteLine("Image.ToString():");
            Console.WriteLine(image);

            // Dispose of the image
            // Note: the image will be automatically disposed when it goes
            // out of scope, however it is good practice to dispose of
            // objects when they are no longer required.
            image.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    } // end main
} // end class
} // end namespace