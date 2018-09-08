using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using VisualTree;

namespace GeometriesExample
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void mainControl_VisualInitialResourceEvent(object sender, EventArgs e)
        {
            // ビットマップ
            using (var bmp = new Bitmap("..\\..\\fish.png"))
            {
                this.mainControl.CreateBitmapBrush("bitmap", (Bitmap)bmp.Clone());
            }
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            // 背景色を塗りつぶす
            e.RenderTarget.Clear(Color.White);

            var rcBrushRect = new RectangleF(0, 0, 378, 284);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmap"]);

            e.RenderTarget.SetTransform(420, 0);
            e.RenderTarget.PushAxisAlignedClip(new RectangleF(100, 20, 100, 100), AntialiasMode.ANTIALIAS_MODE_PER_PRIMITIVE);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmap"]);
            e.RenderTarget.PopAxisAlignedClip();
        }
    }
}
