using System;
using itk;

using FilterType = itk.itkSigmoidImageFilter;

namespace itk.Examples.Filters
{
/// <summary>
/// This example shows how to use the itkSigmoidImageFilter.
/// In addition, it introduces how to observe managed ITK events.
/// </summary>
static class Sigmoid1
{
    [STAThread]
    static void Main(String[] args)
    {
        try
        {
            // Create input and output images
            itkImageBase input = itkImage.New(args[0]);
            itkImageBase output = itkImage.New(input);

            // Read the input image
            input.Read(args[1]);

            // Apply the Sigmoid filter
            FilterType filter = FilterType.New(input, output);
            filter.Started += new itkEventHandler(filter_Started);
            filter.Progress += new itkProgressHandler(filter_Progress);
            filter.Ended += new itkEventHandler(filter_Ended);
            filter.SetInput(input);
            filter.GetOutput(output);
            filter.Alpha = Double.Parse(args[2]);
            filter.Beta  = Double.Parse(args[3]);

            // Write the output to disk
            // NOTE: Any upstream filters will be automatically updated
            output.Write(args[4]);

            // Clean up
            filter.Dispose();
            input.Dispose();
            output.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    }

    static void filter_Started(itkObject sender, itkEventArgs e)
    {
        string message = "{0}: Started at {1}";
        itkProcessObject process = sender as itkProcessObject;
        Console.Write(String.Format(message, process.Name, DateTime.Now));
    }

    static void filter_Progress(itkProcessObject sender, itkProgressEventArgs e)
    {
        if (e.ProgressAsPercentage % 10 == 0) Console.WriteLine();
        Console.Write(e.Progress.ToString("000% "));
    }

    static void filter_Ended(itkObject sender, itkEventArgs e)
    {
        string message = Environment.NewLine + "{0}: Ended at {1}";
        Console.WriteLine(String.Format(message, (sender as itkProcessObject).Name, DateTime.Now));
    }
} // end class
} // end namespace