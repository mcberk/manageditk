/*=============================================================================

  Project:   SharpImage
  Module:    ConfigureProject/Program.cs
  Language:  C#
  Author:    Dan Mueller
  Date:      $Date: 2008-04-15 20:48:33 +0200 (Tue, 15 Apr 2008) $
  Revision:  $Revision: 10 $

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

namespace ConfigureProject
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                // args[0] = Full solution path
                // args[1] = Replacement0 (eg. Release:ExceptionHandling="FALSE":ExceptionHandling="2")
                // args[2] = Replacement1 (eg. Debug:BasicRuntimeChecks="3":BasicRuntimeChecks="0")
                if (args.Length <= 1)
                {
                    Console.WriteLine("Usage: AbsoluteSolutionPath Replacement0 [Replacement1] [Replacement2] [...]");
                    return;
                }

                // Get replacements from command line
                string pathSolution = args[0];
                List<string> replacements = new List<string>();
                
                for (int i=1; i<args.Length; i++)
                    replacements.Add(args[i]);

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
                        Console.WriteLine("Configuring " + Path.GetFileName(pathProject));
                        ApplyReplacementsInProject(pathProject, replacements);
                    }
                }

                Console.WriteLine("Done.");
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.ToString());
            }
        }

        public static void ApplyReplacementsInProject(string pathProject, List<string> replacements)
        {
            bool isInConfiguration = false;
            string currentConfigurationName = string.Empty;
            
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
                string lineProjectFinal = lineProject;

                if (lineProject.Contains("<Configuration") &&
                    !lineProject.Contains("<Configurations>"))
                    isInConfiguration = true;
                else if (lineProject.Contains("</Configuration>"))
                {
                    isInConfiguration = false;
                    currentConfigurationName = string.Empty;
                }
                else if (isInConfiguration && 
                         currentConfigurationName == string.Empty &&
                         lineProject.Contains("Name="))
                {
                    currentConfigurationName = lineProject;
                    currentConfigurationName = currentConfigurationName.Replace("Name=", "");
                    currentConfigurationName = currentConfigurationName.Trim('\t', '"', ' ');
                }

                if (isInConfiguration && 
                    currentConfigurationName != string.Empty)
                {
                    foreach (string replacement in replacements)
                    {
                        // Get the replacement info
                        string[] replacementInfo = replacement.Split('|');
                        if (replacementInfo.Length != 3)
                            throw new ApplicationException("Invalid replacement information: " + replacement);

                        if (currentConfigurationName.StartsWith(replacementInfo[0]))
                        {
                            // We are in the desired configuration
                            lineProjectFinal = lineProjectFinal.Replace(replacementInfo[1], replacementInfo[2]);
                        }
                    }
                }

                // Write the final line
                writer.WriteLine(lineProjectFinal);
            }

            // Clean up
            writer.Flush();
            writer.Close();
            Console.WriteLine("Done.");
        }
    }
}
