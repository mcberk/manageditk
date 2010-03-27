using System;
using System.IO;
using itk;

using ImageType = itk.itkImage_F2;
using OutputImageType = itk.itkImage_UC2;
using RegionType = itk.itkImageRegion;
using ParametersType = itk.itkArray<double>;
using TransformType = itk.itkTranslationTransform_D2;
using OptimizerType = itk.itkGradientDescentOptimizer;
using InterpolatorType = itk.itkLinearInterpolateImageFunction_IF2D;
using ResampleType = itk.itkResampleImageFilter_IF2IF2;
using MetricType = itk.itkMutualInformationImageToImageMetric_IF2IF2;
using RegistrationType = itk.itkImageRegistrationMethod_IF2IF2;
using NormalizeFilterType = itk.itkNormalizeImageFilter_IF2IF2;
using GaussianFilterType = itk.itkDiscreteGaussianImageFilter_IF2IF2;
using ResampleFilterType = itk.itkResampleImageFilter_IF2IF2;
using CastFilterType = itk.itkCastImageFilter;
using CheckerBoardType = itk.itkCheckerBoardImageFilter_IF2;

namespace itk.Examples.Registration
{
/// <summary>
/// This example shows how to implement the ITK example "ImageRegistration2".
/// </summary>
static class ImageRegistration2
{
    [STAThread]
    static void Main(string[] args) {
        try {
            // Get input parameters
            if (args.Length < 3) {
                Console.WriteLine("Missing Parameters");
                Console.Write("Usage: " + Environment.GetCommandLineArgs()[0] + " ");
                Console.Write("fixedImageFile movingImageFile ");
                Console.Write("outputImagefile ");
                Console.WriteLine("[checkerBoardBefore] [checkerBoardAfter]");
                return;
            }

            // Create components
            TransformType transform = TransformType.New();
            OptimizerType optimizer = OptimizerType.New();
            InterpolatorType interpolator = InterpolatorType.New();
            MetricType metric = MetricType.New();
            RegistrationType registration = RegistrationType.New();
            registration.SetOptimizer(optimizer);
            registration.SetTransform(transform);
            registration.SetInterpolator(interpolator);
            registration.SetMetric(metric);

            // Set metric parameters
            metric.FixedImageStandardDeviation = 0.4;
            metric.MovingImageStandardDeviation = 0.4;

            // Read input images
            ImageType fixedImage = ImageType.New();
            fixedImage.Read(args[0]);
            ImageType movingImage = ImageType.New();
            movingImage.Read(args[1]);

            // Normailize
            NormalizeFilterType fixedNormalizer = NormalizeFilterType.New();
            NormalizeFilterType movingNormalizer = NormalizeFilterType.New();
            GaussianFilterType fixedSmoother = GaussianFilterType.New();
            GaussianFilterType movingSmoother = GaussianFilterType.New();
            fixedSmoother.Variance = new double[] { 2.0, 2.0 };
            movingSmoother.Variance = new double[] { 2.0, 2.0 };

            // Setup pipeline
            fixedNormalizer.SetInput(fixedImage);
            movingNormalizer.SetInput(movingImage);
            fixedSmoother.SetInput(fixedNormalizer.GetOutput());
            movingSmoother.SetInput(movingNormalizer.GetOutput());
            ImageType fixedSmootherOutput = ImageType.New();
            fixedSmoother.GetOutput(fixedSmootherOutput);
            ImageType movingSmootherOutput = ImageType.New();
            movingSmoother.GetOutput(movingSmootherOutput);
            registration.SetFixedImage(fixedSmootherOutput);
            registration.SetMovingImage(movingSmootherOutput);

            // Set requested region
            fixedNormalizer.Update();
            ImageType fixedNormalizerOutput = ImageType.New();
            fixedNormalizer.GetOutput(fixedNormalizerOutput);
            RegionType fixedImageRegion = fixedNormalizerOutput.BufferedRegion;
            fixedImage.RequestedRegion = fixedImageRegion;
            //registration.FixedImageRegion = fixedImageRegion

            // Set initial parameters
            ParametersType initialParameters =
                new ParametersType(transform.NumberOfParameters);
            initialParameters[0] = 0.0;
            initialParameters[1] = 0.0;
            registration.InitialTransformParameters = initialParameters;

            // Set metric sampling
            int numberOfPixels = fixedImageRegion.Size[0] * fixedImageRegion.Size[1];
            int numberOfSamples = (int)((double)numberOfPixels * 0.01);
            metric.NumberOfSpatialSamples = (uint)numberOfSamples;

            // Setup optimizer
            optimizer.LearningRate = 15.0;
            optimizer.NumberOfIterations = 200;
            optimizer.Maximize = true;

            // Listen for iteration events
            optimizer.Iteration += OnOptimizerIterationEvent;

            // Start registration
            registration.StartRegistration();
            Console.WriteLine(optimizer.StopCondition);

            // Get results
            ParametersType finalParameters = registration.LastTransformParameters;
            double TranslationAlongX = finalParameters[0];
            double TranslationAlongY = finalParameters[1];
            uint numberOfIterations = optimizer.NumberOfIterations;
            double bestValue = optimizer.GetValue();

            // Print results
            Console.WriteLine("Result=");
            Console.WriteLine(String.Format(" Translation X = {0}", TranslationAlongX));
            Console.WriteLine(String.Format(" Translation Y = {0}", TranslationAlongY));
            Console.WriteLine(String.Format(" Iterations    = {0}", numberOfIterations));
            Console.WriteLine(String.Format(" Metric value  = {0}", bestValue));
            Console.WriteLine(String.Format(" Numb. Samples = {0}", numberOfSamples));

            // Setup resample filter
            TransformType finalTransform = TransformType.New();
            finalTransform.Parameters = finalParameters;
            //finalTransform.FixedParameters = transform.FixedParameters;
            ResampleFilterType resample = ResampleFilterType.New();
            resample.SetTransform(finalTransform);
            resample.SetInput(movingImage);
            resample.OutputSize = fixedImage.LargestPossibleRegion.Size;
            resample.OutputSpacing = fixedImage.Spacing;
            resample.OutputOrigin = fixedImage.Origin;
            resample.DefaultPixelValue = 100;

            // Write resampled output
            OutputImageType output = OutputImageType.New();
            CastFilterType caster = CastFilterType.New(movingImage, output);
            caster.SetInput(resample.GetOutput());
            caster.Update();
            caster.GetOutput(output);
            output.Write(args[2]);

            // Generate checkerboards before registration
            CheckerBoardType checker = CheckerBoardType.New();
            checker.SetInput1(fixedImage);
            checker.SetInput2(movingImage);
            checker.Update();
            ImageType checkerOut = ImageType.New();
            checker.GetOutput(checkerOut);
            caster.SetInput(checkerOut);
            caster.Update();
            caster.GetOutput(output);
            if (args.Length < 4) {
                output.Write(args[3]);
            }

            // Generate checkerboards after registration
            checker.SetInput1(fixedImage);
            checker.SetInput2(resample.GetOutput());
            checker.Update();
            checker.GetOutput(checkerOut);
            caster.SetInput(checkerOut);
            caster.Update();
            caster.GetOutput(output);
            if (args.Length < 5) {
                output.Write(args[4]);
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    }

    static void OnOptimizerIterationEvent(itkObject sender, itkEventArgs e)
    {
        OptimizerType optimizer = sender as OptimizerType;
        String message = "{0}:   {1}";
        String iteration = optimizer.CurrentIteration.ToString("000");
        String position = optimizer.CurrentPosition.ToString();
        Console.WriteLine(String.Format(message, iteration, position));
    }

} // end class
} // end namespace