using System;
using itk;

namespace itk.Examples.Images
{
/// <summary>
/// This example shows how to read image information without actually
/// creating an image.
/// </summary>
static class ReadInformation1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // The itkImageBase.ReadInformation() method can be used to
            // "sniff" out the image information stored in the file.

            // Read the image file information
            itkImageInformation info = itkImageBase.ReadInformation(args[0]);
            
            // Display the IO information
            Console.WriteLine("Information --------------------------");
            Console.WriteLine(String.Format("PixelType={0}",info.PixelType));
            Console.WriteLine(String.Format("Dimension={0}",info.Dimension));
            Console.WriteLine(String.Format("Size={0}",info.Size));
            Console.WriteLine(String.Format("Spacing={0}",info.Spacing));
            Console.WriteLine(String.Format("Origin={0}",info.Origin));

            // Use file information to create and read an image
            itkImageBase image = itkImage.New(info.PixelType, info.Dimension);
            image.Read(args[0]);

            // Display some image information
            Console.WriteLine("Image --------------------------------");
            Console.WriteLine(String.Format("Name={0}",image.Name));
            Console.WriteLine(String.Format("PixelType={0}",image.PixelType));
            Console.WriteLine(String.Format("Dimension={0}",image.Dimension));
            Console.WriteLine(String.Format("Size={0}",image.Size));
            Console.WriteLine(String.Format("Spacing={0}",image.Spacing));
            Console.WriteLine(String.Format("Origin={0}",image.Origin));
            Console.WriteLine(String.Format("Buffer={0}",image.Buffer));

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