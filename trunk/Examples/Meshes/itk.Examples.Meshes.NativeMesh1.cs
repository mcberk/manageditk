using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using itk;

namespace itk.Examples.Meshes
{
/// <summary>
/// This example shows how to import and export to and from a "native" mesh.
/// </summary>
static class NativeMesh1
{
      static void Main(string[] args)
      {
          try
          {
              // Setup typedefs
              itkPixelType pixel = itkPixelType.D;
              itkDimension dim = new itkDimension(3);
              itkMeshTraits traits = itkMeshTraits.Static();

              // Create a native mesh (ie. a mesh residing "outside" of ITK)
              List<double> points = new List<double>();
              points.Add(0.0); points.Add(0.0); points.Add(0.0);  // Point 0
              points.Add(10.0); points.Add(0.0); points.Add(0.0); // Point 1
              points.Add(5.0); points.Add(10.0); points.Add(0.0); // Point 2
              points.Add(5.0); points.Add(5.0); points.Add(10.0); // Point 3
              List<int> cells = new List<int>();
              cells.Add(0); cells.Add(1); cells.Add(2); // Triangle 0
              cells.Add(0); cells.Add(1); cells.Add(3); // Triangle 1
              cells.Add(1); cells.Add(2); cells.Add(3); // Triangle 2
              cells.Add(2); cells.Add(3); cells.Add(0); // Triangle 3
              
              // Pin managed array to mimic unmanaged memory
              GCHandle handlePoints = GCHandle.Alloc(points.ToArray(), GCHandleType.Pinned);
              GCHandle handleCells = GCHandle.Alloc(cells.ToArray(), GCHandleType.Pinned);

              // Import into ITK mesh
              // NOTE: This will duplicate the points and cells in unmanaged memory
              itkMesh mesh = itkMesh.New(pixel, dim, traits);
              mesh.SetPointsAsArray(
                  (uint)(points.Count / dim.Dimension),
                  handlePoints.AddrOfPinnedObject()
              );
              mesh.SetCellIndicesAsArray(
                  (uint)(cells.Count / 3),
                  itkCellTypeEnum.TriangleCellType,
                  handleCells.AddrOfPinnedObject()
              );

              // Export from ITK mesh to managed values
              itkPoint[] points2 = mesh.GetPointsAsArray();
              itkCell[] cells2 = mesh.GetCellsAsArray();
          }
          catch (Exception ex)
          {
              Console.WriteLine(ex.ToString());
          }
      }
} // end class
} // end namespace