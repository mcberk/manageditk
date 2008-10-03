namespace itk.Examples.Images
{
    partial class FormBitmap1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureImage = new System.Windows.Forms.PictureBox();
            this.lblPictureBox = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.pictureImage)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureImage
            // 
            this.pictureImage.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pictureImage.Location = new System.Drawing.Point(0, 16);
            this.pictureImage.Name = "pictureImage";
            this.pictureImage.Size = new System.Drawing.Size(377, 329);
            this.pictureImage.TabIndex = 4;
            this.pictureImage.TabStop = false;
            // 
            // lblPictureBox
            // 
            this.lblPictureBox.AutoSize = true;
            this.lblPictureBox.Dock = System.Windows.Forms.DockStyle.Top;
            this.lblPictureBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblPictureBox.Location = new System.Drawing.Point(0, 0);
            this.lblPictureBox.Name = "lblPictureBox";
            this.lblPictureBox.Size = new System.Drawing.Size(90, 16);
            this.lblPictureBox.TabIndex = 5;
            this.lblPictureBox.Text = "Picture Box:";
            // 
            // FormBitmap1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(377, 345);
            this.Controls.Add(this.pictureImage);
            this.Controls.Add(this.lblPictureBox);
            this.Name = "FormBitmap1";
            this.Text = "itk.Examples.Images.FormBitmap1";
            ((System.ComponentModel.ISupportInitialize)(this.pictureImage)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureImage;
        private System.Windows.Forms.Label lblPictureBox;

    }
}