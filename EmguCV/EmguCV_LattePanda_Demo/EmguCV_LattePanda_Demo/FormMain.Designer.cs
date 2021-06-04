namespace EmguCV_LattePanda_Demo
{
    partial class MainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.StartCAM1 = new System.Windows.Forms.Button();
            this.StopCAM1 = new System.Windows.Forms.Button();
            this.MsgLabel1 = new System.Windows.Forms.Label();
            this.CAM1_ImageBox = new Emgu.CV.UI.ImageBox();
            this.StopCAM2 = new System.Windows.Forms.Button();
            this.StartCAM2 = new System.Windows.Forms.Button();
            this.CAM2_ImageBox = new Emgu.CV.UI.ImageBox();
            this.MsgLabel2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.CAM1_ImageBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.CAM2_ImageBox)).BeginInit();
            this.SuspendLayout();
            // 
            // StartCAM1
            // 
            this.StartCAM1.Location = new System.Drawing.Point(13, 13);
            this.StartCAM1.Name = "StartCAM1";
            this.StartCAM1.Size = new System.Drawing.Size(94, 23);
            this.StartCAM1.TabIndex = 0;
            this.StartCAM1.Text = "开启预览CAM1";
            this.StartCAM1.UseVisualStyleBackColor = true;
            this.StartCAM1.Click += new System.EventHandler(this.StartCAM1_Click);
            // 
            // StopCAM1
            // 
            this.StopCAM1.Location = new System.Drawing.Point(130, 13);
            this.StopCAM1.Name = "StopCAM1";
            this.StopCAM1.Size = new System.Drawing.Size(92, 23);
            this.StopCAM1.TabIndex = 1;
            this.StopCAM1.Text = "关闭预览CAM1";
            this.StopCAM1.UseVisualStyleBackColor = true;
            this.StopCAM1.Click += new System.EventHandler(this.StopCAM1_Click);
            // 
            // MsgLabel1
            // 
            this.MsgLabel1.AutoSize = true;
            this.MsgLabel1.Location = new System.Drawing.Point(12, 39);
            this.MsgLabel1.Name = "MsgLabel1";
            this.MsgLabel1.Size = new System.Drawing.Size(59, 12);
            this.MsgLabel1.TabIndex = 2;
            this.MsgLabel1.Text = "MsgLabel1";
            // 
            // CAM1_ImageBox
            // 
            this.CAM1_ImageBox.Location = new System.Drawing.Point(13, 54);
            this.CAM1_ImageBox.Name = "CAM1_ImageBox";
            this.CAM1_ImageBox.Size = new System.Drawing.Size(361, 272);
            this.CAM1_ImageBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.CAM1_ImageBox.TabIndex = 2;
            this.CAM1_ImageBox.TabStop = false;
            // 
            // StopCAM2
            // 
            this.StopCAM2.Location = new System.Drawing.Point(518, 13);
            this.StopCAM2.Name = "StopCAM2";
            this.StopCAM2.Size = new System.Drawing.Size(91, 23);
            this.StopCAM2.TabIndex = 4;
            this.StopCAM2.Text = "关闭预览CAM2";
            this.StopCAM2.UseVisualStyleBackColor = true;
            this.StopCAM2.Click += new System.EventHandler(this.StopCAM2_Click);
            // 
            // StartCAM2
            // 
            this.StartCAM2.Location = new System.Drawing.Point(398, 13);
            this.StartCAM2.Name = "StartCAM2";
            this.StartCAM2.Size = new System.Drawing.Size(87, 23);
            this.StartCAM2.TabIndex = 3;
            this.StartCAM2.Text = "开启预览CAM2";
            this.StartCAM2.UseVisualStyleBackColor = true;
            this.StartCAM2.Click += new System.EventHandler(this.StartCAM2_Click);
            // 
            // CAM2_ImageBox
            // 
            this.CAM2_ImageBox.Location = new System.Drawing.Point(399, 54);
            this.CAM2_ImageBox.Name = "CAM2_ImageBox";
            this.CAM2_ImageBox.Size = new System.Drawing.Size(359, 272);
            this.CAM2_ImageBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.CAM2_ImageBox.TabIndex = 7;
            this.CAM2_ImageBox.TabStop = false;
            // 
            // MsgLabel2
            // 
            this.MsgLabel2.AutoSize = true;
            this.MsgLabel2.Location = new System.Drawing.Point(397, 39);
            this.MsgLabel2.Name = "MsgLabel2";
            this.MsgLabel2.Size = new System.Drawing.Size(59, 12);
            this.MsgLabel2.TabIndex = 8;
            this.MsgLabel2.Text = "MsgLabel2";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(779, 555);
            this.Controls.Add(this.MsgLabel2);
            this.Controls.Add(this.CAM2_ImageBox);
            this.Controls.Add(this.StopCAM2);
            this.Controls.Add(this.StartCAM2);
            this.Controls.Add(this.CAM1_ImageBox);
            this.Controls.Add(this.MsgLabel1);
            this.Controls.Add(this.StopCAM1);
            this.Controls.Add(this.StartCAM1);
            this.Name = "MainForm";
            this.Text = "网联车控制系统";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.CAM1_ImageBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.CAM2_ImageBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button StartCAM1;
        private System.Windows.Forms.Button StopCAM1;
        private System.Windows.Forms.Label MsgLabel1;
        private Emgu.CV.UI.ImageBox CAM1_ImageBox;
        private System.Windows.Forms.Button StopCAM2;
        private System.Windows.Forms.Button StartCAM2;
        private Emgu.CV.UI.ImageBox CAM2_ImageBox;
        private System.Windows.Forms.Label MsgLabel2;
    }
}

