/*=============================================================================

  Project:   SharpImage
  Module:    RemoveFileConfiguration/Program.cs
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
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace RemoveFileConfiguration
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                // args[0] = Full solution path
                // args[1] = FileToRemoveConfigurations (eg. CMakeLists.txt)
                if (args.Length <= 1)
                {
                    Console.WriteLine("Usage: AbsoluteSolutionPath FileToRemoveConfigurations");
                    return;
                }

                // Get replacements from command line
                string pathSolution = args[0];
                string fileToRemoveConfigs = args[1];

                // Open solution for reading and get text
                Console.WriteLine("Reading solution: " + pathSolution);
                string bodySolution = File.ReadAllText(pathSolution);
                bodySolution = bodySolution.Replace("\r\n", "\r");
                string[] linesSolution = bodySolution.Split('\r');

                // Do for each project in solution
                foreach (string lineSolution in linesSolution)
                {
                    if (lineSolution.StartsWith("Project("))
                    {
                        //Get project path
                        string[] linesProject = lineSolution.Split(',');
                        string pathProject = linesProject[1].Trim(' ', '"', '.', '\\', '/');
                        pathProject = Path.Combine(Path.GetDirectoryName(pathSolution), pathProject);
                        Console.WriteLine("Removing configurations for " + Path.GetFileName(pathProject));
                        RemoveFileConfiguration(pathProject, fileToRemoveConfigs);
                    }
                }

                Console.WriteLine("Done.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        public static void RemoveFileConfiguration(string pathProject, string fileToRemoveConfigs)
        {
            bool isInFile = false;
            bool isInFileConfiguration = false;
            bool writeLine = true;
            
            // Check that the project exists
            if (!File.Exists(pathProject))
            {
                Console.WriteLine("Skipping " + Path.GetFileName(pathProject) + " because the path does not exist...");
                return;
            }

            // Open project for reading and get text
            string bodyProject = File.ReadAllText(pathProject);
            bodyProject = bodyProject.Replace("\r\n", "\r");
            string[] linesProject = bodyProject.Split('\r');

            // Open project for writing
            StreamWriter writer = new StreamWriter(pathProject);
                
            // Output the adjusted/configured project
            foreach (string lineProject in linesProject)
            {
                if (lineProject.Contains("Path") &&
                    lineProject.Contains(fileToRemoveConfigs))
                    isInFile = true;
                else if (isInFile &&
                         lineProject.Contains("</File>"))
                    isInFile = false;
                else if (isInFile && !isInFileConfiguration &&
                         lineProject.Contains("<FileConfiguration"))
                    isInFileConfiguration = true;
                else if (isInFile && isInFileConfiguration &&
                    lineProject.Contains("</FileConfiguration>"))
                {
                    isInFileConfiguration = false;
                    writeLine = false;
                }

                // Write the line
                if (!isInFileConfiguration && writeLine)
                    writer.WriteLine(lineProject);
                writeLine = true;
            }

            // Clean up
            writer.Flush();
            writer.Close();
            Console.WriteLine("Done.");
        }
    }
}
