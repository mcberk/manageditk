using System;
using itk;

using PixelType     = itk.itkPixelType;
using ImageType     = itk.itkImageBase;
using WatershedType = itk.itkWatershedImageFilter;
using RelabelType   = itk.itkRelabelComponentImageFilter;

namespace itk.Examples.Segmentation
{
/// <summary>
/// This example shows how to use the itkWatershedImageFilter.
/// It also shows how to use a filter as input into another filter.
/// </summary>
static class Watershed1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Create the input and label images
            ImageType input = itkImage.New(args[0]);
            input.Read(args[1]);
            ImageType label = itkImage.New(PixelType.UL, input.Dimension);

            // Watershed
            WatershedType filterWatershed = WatershedType.New( input );
            filterWatershed.SetInput( input );
            filterWatershed.Threshold = Double.Parse(args[2]);
            filterWatershed.Level = Double.Parse(args[3]);
            filterWatershed.Update();

            // Relabel
            RelabelType filterRelabel = RelabelType.New( label, label );
            filterRelabel.SetInput( filterWatershed.GetOutput() );
            filterRelabel.Update();
            filterRelabel.GetOutput( label );
            input.DisconnectPipeline();
            label.DisconnectPipeline();

            // Write the label image to disk
            label.Write(args[4]);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    } // end main
} // end class
} // end namespace