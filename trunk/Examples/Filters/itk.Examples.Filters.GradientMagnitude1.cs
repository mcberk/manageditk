using System;
using itk;

using FilterType = itk.itkGradientMagnitudeImageFilter;

namespace itk.Examples.Filters
{
/// <summary>
/// This example shows how to use the itkGradientMagnitudeImageFilter.
/// </summary>
static class GradientMagnitude1
{
    [STAThread]
    static void Main(String[] args)
    {
        try
        {
            // Setup input and output images
            itkImageBase input = itkImage.New(args[0]);
            itkImageBase output = itkImage.New(input);

            // Read the input image
            input.Read(args[1]);

            // Apply the filter
            FilterType filter = FilterType.New(input, output);
            filter.SetInput(input);
            filter.Update();
            filter.GetOutput(output);

            // Write the output to disk
            output.Write(args[2]);

            // Clean up
            filter.Dispose();
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