using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using itk;

namespace itk.Examples.Images
{
/// <summary>
/// This example shows how to import an image from a user specified buffer.
/// </summary>
static class Import1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            // Create a managed array to import
            const Int32 Width = 256;
            const Int32 Height = 256;
            List<float> list = new List<float>(Width * Height);
            for (int j = 0; j < Height; j++)
            {
                for (int i = 0; i < Width; i++)
                {
                    if (i == j)
                        list.Add(Convert.ToSingle(i));
                    else
                        list.Add(0.0F);
                }
            }

            // Pin the managed array for use with unmanaged code
            float[] array = list.ToArray();
            GCHandle handle = GCHandle.Alloc(array, GCHandleType.Pinned);

            // Setup for import
            itkImportImageFilter_F2 importer = itkImportImageFilter_F2.New();
            itkSize size = new itkSize(Width, Height);
            itkIndex index = new itkIndex(0, 0);
            importer.Region = new itkImageRegion(size, index);
            importer.Spacing = new itkSpacing(1.0, 1.0);
            importer.Origin = new itkPoint(0.0, 0.0);
            importer.SetImportPointer(handle.AddrOfPinnedObject(), (uint)list.Count, false);

            // Perform import
            itkImageBase output = itkImage_F2.New();
            importer.UpdateLargestPossibleRegion();
            importer.GetOutput(output);
            output.Write(args[0]);

            // Display some image information
            Console.WriteLine(String.Format("{0}", output));

            // Cleanup
            output.Dispose();
            importer.Dispose();
            handle.Free();
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.ToString());
        }
    } // end main
} // end class
} // end namespace