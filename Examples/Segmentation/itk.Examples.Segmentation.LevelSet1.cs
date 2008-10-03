using System;
using itk;

using LevelSetType = itk.itkCurvesLevelSetImageFilter;

namespace itk.Examples.Segmentation
{
/// <summary>
/// This example shows how to use the Level Set filters.
/// </summary>
static class LevelSet1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Create the initial, feature and output images
            itkPixelType pixeltype = itkPixelType.F;
            uint Dimension = UInt32.Parse(args[0]);
            itkImageBase initial = itkImage.New(pixeltype, Dimension);
            itkImageBase speed = itkImage.New(pixeltype, Dimension);
            itkImageBase output  = itkImage.New(pixeltype, Dimension);
            Console.WriteLine("Reading initial: " + args[1]);
            initial.Read(args[1]);
            Console.WriteLine("Reading speed: " + args[2]);
            speed.Read(args[2]);

            // Level Set
            LevelSetType levelset = LevelSetType.New(initial, speed,
                                                     pixeltype);
            levelset.Started += new itkEventHandler(LevelSetStarted);
            levelset.Iteration += new itkEventHandler(LevelSetIteration);
            levelset.Ended += new itkEventHandler(LevelSetEnded);
            levelset.SetInitialImage(initial);
            levelset.SetFeatureImage(speed);
            levelset.PropagationScaling = 5.0;
            levelset.CurvatureScaling = 3.0;
            levelset.AdvectionScaling = 1.0;
            levelset.MaximumRMSError = 0.01;
            levelset.NumberOfIterations = 600;
            levelset.Update();
            levelset.GetOutput(output);

            // Write the output image to disk
            Console.WriteLine("Writing output: " + args[3]);
            output.Write(args[3]);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    }

    static void LevelSetStarted(itkObject sender, itkEventArgs e)
    {
        String message = "Started: {0}";
        Console.WriteLine(String.Format(message, DateTime.Now));
    }

    static void LevelSetIteration(itkObject sender, itkEventArgs e)
    {
        LevelSetType levelset = sender as LevelSetType;
        UInt32 i = levelset.ElapsedIterations;
        String str = i.ToString("000 ");
        if (i == 1)       Console.Write(str);
        if (i % 100 == 0) Console.WriteLine();
        if (i %  10 == 0) Console.Write(str);
    }

    static void LevelSetEnded(itkObject sender, itkEventArgs e)
    {
        String message = Environment.NewLine + "Ended: {0}";
        Console.WriteLine(String.Format(message, DateTime.Now));
    }
} // end class
} // end namespace