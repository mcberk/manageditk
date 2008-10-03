using System;
using itk;

namespace itk.Examples.Meshes
{
/// <summary>
/// This example shows how to read and write a mesh using the VTK poly data filters.
/// </summary>
static class ReadWriteMesh1
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

            // Create a mesh
            itkMesh mesh1 = itkMesh.New(pixel, dim, traits);
            itkRegularSphereMeshSource source = itkRegularSphereMeshSource.New(mesh1);
            source.Center = new itkPoint(32.0, 32.0, 32.0);
            source.Scale = new itkVector(32.0, 32.0, 32.0);
            source.Resolution = 5;
            source.Update();
            source.GetOutput(mesh1);

            // Write mesh
            String path = args[0];
            Console.WriteLine("Writing mesh: " + path);
            itkVTKPolyDataWriter writer = itkVTKPolyDataWriter.New(mesh1);
            writer.SetInput(mesh1);
            writer.FileName = path;
            writer.Write();

            // Read mesh
            itkMesh mesh2 = itkMesh.New(pixel, dim, traits);
            Console.WriteLine("Reading mesh: " + path);
            itkVTKPolyDataReader reader = itkVTKPolyDataReader.New(mesh1);
            reader.FileName = path;
            reader.Update();
            reader.GetOutput(mesh2);
            Console.WriteLine(mesh2);

            // Cleanup
            mesh1.Dispose();
            mesh2.Dispose();
            source.Dispose();
            writer.Dispose();
            reader.Dispose();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    } // end main
} // end class
} // end namespace