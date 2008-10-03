/*=============================================================================
  
  Project:   ManagedITK
  Program:   Insight Segmentation & Registration Toolkit
  Module:    Coverage/Program.cs
  Language:  C#
  Author:    Dan Mueller
  Date:      $Date: 2008-03-09 19:29:02 +0100 (Sun, 09 Mar 2008) $
  Revision:  $Revision: 8 $

  Copyright (c) 2007-2008 Daniel Mueller

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  
=============================================================================*/

using System;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Reflection;
using System.Windows.Forms;

namespace Coverage
{
    class Program
    {
        static void Main(String[] args)
        {
            try
            {
                // Get the assemblies from which to list the coverage
                String pathExecutable = Path.GetDirectoryName(Application.ExecutablePath);
                String[] filesAssemblies = Directory.GetFiles(pathExecutable, "*.dll");

                // Create the output coverage file
                String fileOutput = Path.Combine(pathExecutable, "coverage.txt");
                StreamWriter writerOutput = File.CreateText(fileOutput);

                // Write the header
                Assembly assemblyCommon = Assembly.LoadFile(Path.Combine(pathExecutable, "ManagedITK.Common.dll"));
                const String sep = "========================================";
                String header = "Coverage: ManagedITK {0}: {1}";
                header = sep + Environment.NewLine + header + Environment.NewLine + sep + Environment.NewLine;
                String version = assemblyCommon.GetName().Version.ToString();
                String date = DateTime.Today.ToString("yyyy/MM/dd");
                writerOutput.WriteLine(String.Format(header, version, date));

                // Loop through each file
                foreach (String fileAssembly in filesAssemblies)
                {
                    // Write assembly name
                    String name = Path.GetFileNameWithoutExtension(fileAssembly);
                    writerOutput.WriteLine(name);
                    Console.WriteLine("Processing " + name);

                    // Collate the list of exported types
                    Assembly assembly = Assembly.LoadFile(fileAssembly);
                    List<String> types = new List<String>();
                    foreach (Type type in assembly.GetExportedTypes())
                        if (!type.Name.Contains("_") && type.Name.StartsWith("itk"))
                            types.Add(type.Name);

                    // Sort list
                    types.Sort();

                    // Write list
                    foreach (String type in types)
                        writerOutput.WriteLine("\t" + type);
                    writerOutput.WriteLine("");
                }

                // Write coverage
                writerOutput.Flush();
                writerOutput.Dispose();
                writerOutput = null;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
            }       
        }
    }
}
