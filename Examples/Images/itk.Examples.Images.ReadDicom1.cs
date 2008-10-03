using System;
using itk;

namespace itk.Examples.Images
{
/// <summary>
/// This example shows how to read an image from a DICOM directory.
/// </summary>
static class ReadDicom1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Create an explicit image type
            itkImageBase image = itkImage_SS3.New();

            // Read the DICOM image from the given directory  
            image.ReadDicomDirectory(args[0]);

            // Display some image information
            Console.WriteLine(String.Format("Name={0}",image.Name));
            Console.WriteLine(String.Format("PixelType={0}",image.PixelType));
            Console.WriteLine(String.Format("Dimension={0}",image.Dimension));
            Console.WriteLine(String.Format("Size={0}",image.Size));
            Console.WriteLine(String.Format("Spacing={0}",image.Spacing));
            Console.WriteLine(String.Format("Origin={0}",image.Origin));
            Console.WriteLine(String.Format("Buffer={0}",image.Buffer));

            // Write the image to disk
            image.Write(args[1]);

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