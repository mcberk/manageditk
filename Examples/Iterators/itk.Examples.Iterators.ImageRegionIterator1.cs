using System;
using itk;

namespace itk.Examples.Iterators
{
/// <summary>
/// This example shows how to use an ImageRegionIterator to iterate over
/// the each pixel in an image.
/// </summary>
static class ImageRegionIterator1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Read an explicitly typed image
            itkImageBase input = itkImage_UC2.New();
            input.Read(args[0]);

            // Allocate an empty output image
            itkImageBase output = itkImage_UC2.New();
            itkImageRegion region = input.LargestPossibleRegion;
            output.SetRegions(region);
            output.Allocate();
            output.FillBuffer(0);
            output.Spacing = input.Spacing;
            output.Origin = input.Origin;

            // Create iterators to walk the input and output images
            itkImageRegionConstIterator_IUC2 inputIt;
            itkImageRegionIterator_IUC2 outputIt;
            inputIt = new itkImageRegionConstIterator_IUC2(input, region);
            outputIt = new itkImageRegionIterator_IUC2(output, region);

            // Walk the images using the iterators
            foreach (itkPixel pixel in inputIt)
            {
                outputIt.Set(pixel);
                outputIt++;
            }

            // Write the output image
            output.Write(args[1]);

            // Dispose of the images
            input.Dispose();
            output.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    } // end main
} // end class
} // end namespace