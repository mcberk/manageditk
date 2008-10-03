using System;
using itk;

namespace itk.Examples.Meshes
{
/// <summary>
/// This example shows how to convert a triangle mesh to a binary image.
/// </summary>
static class TriangleMesh1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Setup typedefs
            itkPixelType pixel = itkPixelType.D;
            itkDimension dim = new itkDimension(3);
            itkMeshTraits traits = itkMeshTraits.Static();

            // Create mesh
            itkMesh mesh = itkMesh.New(pixel, dim, traits);
            itkRegularSphereMeshSource source = 
                itkRegularSphereMeshSource.New(mesh);
            source.Center = new itkPoint(32.0, 32.0, 32.0);
            source.Scale = new itkVector(32.0, 32.0, 32.0);
            source.Resolution = 4;
            source.Update();
            source.GetOutput(mesh);

            // Convert mesh to image
            itkImageBase output = itkImage.New(itkPixelType.UC, dim.Dimension);
            itkTriangleMeshToBinaryImageFilter filter = 
                itkTriangleMeshToBinaryImageFilter.New(mesh, output);
            filter.SetInput(mesh);
            filter.Tolerance = 0.001;
            filter.Size = new itkSize(100, 100, 100);
            filter.Update();
            filter.GetOutput(output);
            output.Write(args[0]);

            // Cleanup
            filter.Dispose();
            output.Dispose();
            mesh.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    } // end main
} // end class
} // end namespace