namespace GeometriesExample
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージド リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.mainControl = new VisualTree.VisualTeeControl();
            this.SuspendLayout();
            // 
            // mainControl
            // 
            this.mainControl.Dock = System.Windows.Forms.DockStyle.Fill;
            this.mainControl.Location = new System.Drawing.Point(0, 0);
            this.mainControl.Name = "mainControl";
            this.mainControl.Size = new System.Drawing.Size(539, 507);
            this.mainControl.TabIndex = 0;
            this.mainControl.VisualInitialResourceEvent += new VisualTree.VisualTeeControl.VisualResourceEventHandler(this.mainControl_VisualInitialResourceEvent);
            this.mainControl.VisualRenderEvent += new VisualTree.VisualTeeControl.VisualRenderEventHandler(this.mainControl_VisualRenderEvent);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(539, 507);
            this.Controls.Add(this.mainControl);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private VisualTree.VisualTeeControl mainControl;
    }
}

