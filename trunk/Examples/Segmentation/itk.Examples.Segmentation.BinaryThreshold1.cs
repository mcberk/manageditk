using System;
using System.Drawing;
using System.Windows.Forms;

namespace itk.Examples.Segmentation
{
/// <summary>
/// This example shows how to use the itkBinaryThresholdImageFilter.
/// In addition is shows how to use System.Windows.Forms to monitor
/// a filter.
/// </summary>
static class BinaryThreshold1
{
    [STAThread]
    static void Main(String[] args)
    {
        try
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new FormBinaryThreshold1());
        }
        catch (Exception ex)
        {
            String text = ex.ToString();
            String caption = "An unexpected error occured";
            MessageBox.Show(text, caption, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    }// end main
} // end class
} // end namespace