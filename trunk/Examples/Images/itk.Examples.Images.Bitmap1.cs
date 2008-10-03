using System;
using System.Drawing;
using System.Windows.Forms;

namespace itk.Examples.Images
{
/// <summary>
/// This example shows how to use ManagedITK with System.Drawing.Bitmap.
/// </summary>
static class Bitmap1
{
    [STAThread]
    static void Main(string[] args)
    {
        try
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new FormBitmap1(args[0]));
        }
        catch (Exception ex)
        {
            String text = ex.ToString();
            String caption = "An unexpected error occured";
            MessageBox.Show(text, caption, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }
    } // end main
} // end class
} // end namespace