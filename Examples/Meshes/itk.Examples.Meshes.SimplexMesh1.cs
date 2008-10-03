using System;
using System.IO;
using itk;

namespace itk.Examples.Meshes
{
/// <summary>
/// This example shows how to use simplex meshes.
/// itk.Examples.Meshes.SimplexMesh1 blob1-gradient.mhd out.mhd
/// </summary>
static class SimplexMesh1
{
      static void Main(string[] args)
      {
          try
          {
              // Setup typedefs
              itkPixelType pixel = itkPixelType.D;
              itkDimension dim = new itkDimension(3);
              itkMeshTraits traits = itkMeshTraits.Static();

              // Compute gradient
              Console.WriteLine("Reading gradient: " + args[0]);
              itkImageBase gradient = itkImage_CVD33.New();
              gradient.Read(args[0]);

              // Create initial mesh
              Console.WriteLine("Creating initial mesh");
              itkMesh meshIn = itkMesh.New(pixel, dim, traits);
              itkRegularSphereMeshSource source = itkRegularSphereMeshSource.New(meshIn);
              source.Center = new itkPoint(20.0, 20.0, 20.0);
              source.Scale = new itkVector(5.0, 5.0, 5.0);
              source.Resolution = 4;
              source.Update();
              source.GetOutput(meshIn);
              meshIn.DisconnectPipeline();

              // Convert triangle mesh to simplex mesh
              Console.WriteLine("Converting triangle mesh to simplex mesh");
              itkSimplexMesh simplexIn = itkSimplexMesh.New(pixel, dim, traits);
              itkTriangleMeshToSimplexMeshFilter convertToSimplex =
                  itkTriangleMeshToSimplexMeshFilter.New(meshIn, simplexIn);
              convertToSimplex.SetInput(meshIn);
              convertToSimplex.Update();
              convertToSimplex.GetOutput(simplexIn);
              simplexIn.DisconnectPipeline();

              // Deform the simplex mesh
              Console.WriteLine("Deforming simplex mesh");
              itkSimplexMesh simplexOut = itkSimplexMesh.New(pixel, dim, traits);
              itkDeformableSimplexMesh3DBalloonForceFilter deform =
                  itkDeformableSimplexMesh3DBalloonForceFilter.New(simplexIn, simplexOut);
              deform.Alpha = 0.8;   // Internal force scaling
              deform.Beta = 0.8;    // External force scaling
              deform.Gamma = 0.1;   // Reference metric scaling
              deform.Rigidity = 3;  // Mesh smoothness (0=high curvature, 9=smooth)
              deform.Kappa = 0.1;   // Internal balloon force scaling
              deform.Iterations = 200;
              deform.SetGradient(gradient);
              deform.SetInput(simplexIn);
              deform.Progress += new itkProgressHandler(FilterProgress);
              deform.Update();
              deform.GetOutput(simplexOut);
              simplexOut.DisconnectPipeline();
              Console.WriteLine();

              // Convert simplex mesh to triangle mesh
              Console.WriteLine("Converting simplex mesh to triangle mesh");
              itkMesh meshOut = itkMesh.New(pixel, dim, traits);
              itkSimplexMeshToTriangleMeshFilter convertToTriangle =
                  itkSimplexMeshToTriangleMeshFilter.New(simplexOut, meshOut);
              convertToTriangle.SetInput(simplexOut);
              convertToTriangle.Update();
              convertToTriangle.GetOutput(meshOut);
              meshOut.DisconnectPipeline();

              // Convert mesh to image
              Console.WriteLine("Converting mesh to image: " + Path.GetFileName(args[1]));
              itkImageBase output = itkImage_UC3.New();
              itkTriangleMeshToBinaryImageFilter filter =
                  itkTriangleMeshToBinaryImageFilter.New(meshOut, output);
              filter.SetInput(meshOut);
              filter.Tolerance = 0.001;
              filter.Size = gradient.Size;
              filter.Spacing = gradient.Spacing;
              filter.Origin = gradient.Origin;
              filter.GetOutput(output);
              filter.Update();
              output.Write(args[1]);
          }
          catch (Exception ex)
          {
              Console.WriteLine(ex.ToString());
          }
      }

      static int lastprogress = 0;
      static void FilterProgress(itkProcessObject sender, itkProgressEventArgs e)
      {
          if (e.Progress == 0F || e.Progress == 1F) return;
          if (lastprogress >= e.ProgressAsPercentage) return;
          if (e.ProgressAsPercentage % 10 == 0) Console.WriteLine();
          Console.Write(e.Progress.ToString("000% "));
          lastprogress = e.ProgressAsPercentage;
      }
} // end class
} // end namespace