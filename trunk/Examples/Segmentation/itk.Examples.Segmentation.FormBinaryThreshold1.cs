using System;
using System.IO;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;

using FilterType = itk.itkBinaryThresholdImageFilter;

namespace itk.Examples.Segmentation
{

public partial class FormBinaryThreshold1 : Form
{
    private const string TIMEFORMAT = "h:mm:ss:ff tt";
    private delegate void MessageHandler(String message);
    private delegate void VoidHandler();
    
    public FormBinaryThreshold1()
    {
        InitializeComponent();
    }

    private void menuOpen_Click(object sender, EventArgs e)
    {
        const String allext = "*.mhd;*.png;*.jpg;*.bmp;*.tif;*.vtk";
        
        // Show an open file dialog
        OpenFileDialog ofd = new OpenFileDialog();
        ofd.CheckFileExists = true;
        ofd.CheckPathExists = true;
        ofd.Filter = "Meta Header files (*.mhd)|*.mhd";
        ofd.Filter += "|PNG Image files (*.png)|*.png";
        ofd.Filter += "|JPEG Image files (*.jpg)|*.jpg";
        ofd.Filter += "|BMP Image files (*.bmp)|*.bmp";
        ofd.Filter += "|TIFF Image files (*.tif)|*.tif";
        ofd.Filter += "|VTK Image files (*.vtk)|*.vtk";
        ofd.Filter += "|All Image files (" + allext + ")|" + allext;
        ofd.FilterIndex = 7;
        ofd.Multiselect = false;
        ofd.RestoreDirectory = true;
        ofd.Title = "Select image to process";
        DialogResult result = ofd.ShowDialog(this);

        // Check the user click OK
        if (result != DialogResult.OK)
            return;

        // Start the processing thread
        ParameterizedThreadStart threadStart;
        threadStart = new ParameterizedThreadStart(this.DoWork);
        Thread thread = new Thread(threadStart);
        thread.Start(ofd.FileName);
    }

    private void menuExit_Click(object sender, EventArgs e)
    {
        this.Close();
        Application.Exit();
    }

    private void DoWork(object oInputName)
    {
        try
        {
            // Cast the filename to a string
            String inputName = oInputName as String;

            // Read the image information
            itkImageInformation info = itkImage.ReadInformation(inputName);

            // Ensure the pixel type is a scalar or RGB or RGBA
            if (info.PixelType.IsArray && !info.PixelType.IsColor)
            {
                String message = "The image type is not supported: {0}";
                message = String.Format(message, info.PixelType);
                throw new NotSupportedException(message);
            }

            // Create the input and output types
            itkImageBase input; itkImageBase output;
            input  = itkImage.New(itkPixelType.F,  info.Dimension);
            output = itkImage.New(itkPixelType.UC, info.Dimension);

            // Open the input
            this.WriteLine("Reading " + inputName);
            input.Read(inputName);

            // Apply the filter
            FilterType filter = FilterType.New(input, output);
            filter.Started += new itkEventHandler(FilterStarted);
            filter.Progress += new itkProgressHandler(FilterProgress);
            filter.Ended += new itkEventHandler(FilterEnded);
            filter.SetInput(input);
            filter.LowerThreshold = 100;
            filter.UpperThreshold = 255;
            filter.OutsideValue = 0;
            filter.InsideValue = 255;
            filter.Update();
            filter.GetOutput(output);

            // Clean up
            input.DisconnectPipeline();
            output.DisconnectPipeline();
            filter.Dispose();

            // Construct the output filename
            String outputPath = Path.GetDirectoryName(input.Name);
            String outputFile = Path.GetFileNameWithoutExtension(input.Name);
            if      (output.Dimension == 2) { outputFile += "_OUT.png"; }
            else if (output.Dimension > 2)  { outputFile += "_OUT.mhd"; }
            String outputName = Path.Combine(outputPath, outputFile);

            // Write the output
            this.WriteLine("Writing " + outputName);
            output.Write(outputName);                

            // Finish up
            this.ResetStatusStrip();
            input.Dispose();
            output.Dispose();
        }
        catch (Exception ex)
        {
            this.WriteLine("An unexpected error occured!");
            this.WriteLine(ex.ToString());
        }
    }

    void FilterStarted(itkObject sender, itkEventArgs e)
    {
        // Make thread safe
        if (this.InvokeRequired)
        {
            this.Invoke(new itkEventHandler(this.FilterStarted), sender, e);
            return;
        }
        
        // Show message
        String message = "Started: {0}";
        this.WriteLine(String.Format(message, DateTime.Now.ToString(TIMEFORMAT)));
        this.stripStatusLabel.Text = "Running...";
    }

    void FilterProgress(itkProcessObject sender, itkProgressEventArgs e)
    {
        // Make thread safe
        if (this.InvokeRequired)
        {
            this.Invoke(new itkProgressHandler(this.FilterProgress), 
                        sender, e);
            return;
        }
        
        // Update progress bar
        this.stripProgressBar.Value = e.ProgressAsPercentage;
    }

    void FilterEnded(itkObject sender, itkEventArgs e)
    {
        // Make thread safe
        if (this.InvokeRequired)
        {
            this.Invoke(new itkEventHandler(this.FilterEnded), sender, e);
            return;
        }

        // Show message
        String message = "Ended: {0}";
        this.WriteLine(String.Format(message, DateTime.Now.ToString(TIMEFORMAT)));
    }

    private void WriteLine(String message)
    {
        // Make thread safe
        if (this.InvokeRequired)
        {
            this.Invoke(new MessageHandler(this.WriteLine), message);
            return;
        }
        
        // Show message in text box
        this.textStatus.AppendText(message + Environment.NewLine);
    }

    private void ResetStatusStrip()
    {
        // Make thread safe
        if (this.InvokeRequired)
        {
            this.Invoke(new VoidHandler(this.ResetStatusStrip));
            return;
        }
        
        // Reset the label and progress bar
        this.stripStatusLabel.Text = "Ready";
        this.stripProgressBar.Value = 0;
    }
}// end partial class

}// end namespace