using System;
using itk;

namespace itk.Examples.Images
{
/// <summary>
/// This example shows how to read and write an image. The image type is
/// determined at run-time from the command line.
/// </summary>
static class ReadWrite1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // One of the benefits of ManagedITK is the ability to easily
            // choose the image type at run-time, rather than compile-time.

            // Use the image type from the command line to create an image
            itkImageBase image = itkImage.New(args[0]);

            // Read the image from disk
            image.Read(args[1]);

            // Display some image information
            Console.WriteLine(String.Format("Name={0}",image.Name));
            Console.WriteLine(String.Format("PixelType={0}",image.PixelType));
            Console.WriteLine(String.Format("Dimension={0}",image.Dimension));
            Console.WriteLine(String.Format("Size={0}",image.Size));
            Console.WriteLine(String.Format("Spacing={0}",image.Spacing));
            Console.WriteLine(String.Format("Origin={0}",image.Origin));
            Console.WriteLine(String.Format("Buffer={0}",image.Buffer));

            // Write the image to disk
            image.Write(args[2]);

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