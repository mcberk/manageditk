using System;
using System.IO;
using itk;

using ImageType = itk.itkImage_UC2;
using InterpolatorType = itk.itkLinearInterpolateImageFunction_IUC2D;
using TransformType = itk.itkTranslationTransform_D2;
using ResampleType = itk.itkResampleImageFilter_IUC2IUC2;
using MetricType = itk.itkMeanSquaresImageToImageMetric_IUC2IUC2;
using OptimizerType = itk.itkRegularStepGradientDescentOptimizer;
using RegistrationType = itk.itkImageRegistrationMethod_IUC2IUC2;

namespace itk.Examples.Registration
{
/// <summary>
/// This example shows how to use the Registration assembly.
/// </summary>
static class Rigid2d1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Read the fixed image from the command line
            itkImageBase imageFixed = ImageType.New();
            imageFixed.Read(args[0]);

            // Create a moving image
            itkImageBase imageMoving = itkImage.New(imageFixed);

            // Create the interpolator
            InterpolatorType interpolator = InterpolatorType.New();

            // Create the transform
            TransformType transform = TransformType.New();
            transform.Translate(new itkVector(7.5, 12.0));
            Console.WriteLine("START: " + transform.Parameters.ToString());

            // Make the moving image by resampling the fixed image
            // with known parameters
            ResampleType filterResample = ResampleType.New();
            filterResample.SetInput(imageFixed);
            filterResample.SetInterpolator(interpolator);
            filterResample.SetTransform(transform);
            filterResample.OutputSize = imageFixed.Size;
            filterResample.OutputSpacing = imageFixed.Spacing;
            filterResample.Update();
            filterResample.GetOutput(imageMoving);
            imageMoving.DisconnectPipeline();
            imageFixed.DisconnectPipeline();

            // Write out the fixed and moving images
            imageFixed.Write(AddSuffixToFileName(args[0], "_FIXED"));
            imageMoving.Write(AddSuffixToFileName(args[0], "_MOVING"));

            // Reset the transform initial parameters
            transform.Translate(new itkVector(0.0, 0.0));

            // Create metric
            MetricType metric = MetricType.New();
            
            // Create optimiser
            OptimizerType optimizer = OptimizerType.New();
            optimizer.Iteration += new itkEventHandler(optimizer_Iteration);
            optimizer.MaximumStepLength = 4.00;
            optimizer.MinimumStepLength = 0.01;
            optimizer.NumberOfIterations = 200;

            // Create registration method
            RegistrationType registration = RegistrationType.New();
            registration.SetFixedImage(imageFixed);
            registration.SetMovingImage(imageMoving);
            registration.SetTransform(transform);
            registration.SetInterpolator(interpolator);
            registration.SetMetric(metric);
            registration.SetOptimizer(optimizer);
            registration.InitialTransformParameters = transform.Parameters;
            registration.StartRegistration();

            // Rotate the moving image with the found parameters
            filterResample.SetInput(imageMoving);
            filterResample.SetInterpolator(interpolator);
            filterResample.SetTransform(transform);
            filterResample.OutputSize = imageMoving.Size;
            filterResample.OutputSpacing = imageMoving.Spacing;
            filterResample.Update();
            filterResample.GetOutput(imageMoving);
            imageMoving.DisconnectPipeline();

            // Write out the results
            Console.WriteLine("END:   " + transform.Parameters.ToString());
            imageMoving.Write(AddSuffixToFileName(args[0], "_REGISTERED"));
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    }

    static void optimizer_Iteration(itkObject sender, itkEventArgs e)
    {
        OptimizerType optimizer = sender as OptimizerType;
        String message = "{0}:   {1}";
        String iteration = optimizer.CurrentIteration.ToString("000");
        String position = optimizer.CurrentPosition.ToString();
        Console.WriteLine(String.Format(message, iteration, position));
    }

    static String AddSuffixToFileName(String inputFileName, String suffix)
    {
        String directory = Path.GetDirectoryName(inputFileName);
        String filename = Path.GetFileNameWithoutExtension(inputFileName);
        String ext = Path.GetExtension(inputFileName);
        return Path.Combine(directory, filename + suffix + ext);
    }

} // end class
} // end namespace