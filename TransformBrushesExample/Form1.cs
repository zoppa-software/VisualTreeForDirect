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
            // 黒ブラシ
            this.mainControl.CreateSolidColorBrush("brush", Color.Black);

            // 画像ブラシ
            using (var bmp = new Bitmap("..\\..\\leaf_sample.jpg")) {
                this.mainControl.CreateBitmapBrush("bitmap", (Bitmap)bmp.Clone());
            }
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            var rcBrushRect = new RectangleF(5, 0, 150, 150);
            var rcTransformedBrushRect = new RectangleF(100, 100, 100, 100);

            // 背景塗りつぶし
            e.RenderTarget.Clear(Color.White);

            // オリジナル画像
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmap"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["brush"], 1);

            // 部分描画
            e.RenderTarget.FillRectangle(rcTransformedBrushRect, e.Resources["bitmap"]);

            // 部分を移動して描画
            e.Resources["bitmap"].SetTransform(Matrix.Translation(50, 50));
            e.RenderTarget.FillRectangle(rcTransformedBrushRect, e.Resources["bitmap"]);
            e.RenderTarget.DrawRectangle(rcTransformedBrushRect, e.Resources["brush"], 1);
        }
    }
}
