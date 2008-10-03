using System;
using itk;

using FilterType = itk.itkRescaleIntensityImageFilter;

namespace itk.Examples.Filters
{
/// <summary>
/// This example shows how to the itkRescaleIntensityImageFilter.
/// </summary>
static class RescaleIntensity1
{
    [STAThread]
    static void Main(String[] args)
    {
        try
        {
            // Setup input and output images
            UInt32 dim = UInt32.Parse(args[0]);
            itkImageBase input =  itkImage.New(itkPixelType.F,  dim);
            itkImageBase output = itkImage.New(itkPixelType.UC, dim);

            // Read the input image
            input.Read(args[1]);

            // Apply the Rescale Intensity filter
            FilterType filterRescale = FilterType.New(input, output);
            filterRescale.RemoveAllObservers();
            filterRescale.SetInput(input);
            filterRescale.OutputMinimum = 000.0F;
            filterRescale.OutputMaximum = 255.0F;
            filterRescale.Update();
            filterRescale.GetOutput(output);

            // Write the output to disk
            output.Write(args[2]);

            // Clean up
            filterRescale.Dispose();
            input.Dispose();
            output.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    }
} // end class
} // end namespace