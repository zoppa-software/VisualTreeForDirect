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
            this.mainControl.CreateSolidColorBrush("black", Color.Black);

            using (var bmp = new Bitmap("..\\..\\fish.png"))
            {
                var original = this.mainControl.CreateBitmapBrush("original", (Bitmap)bmp.Clone());
                original.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                original.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                original.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;

                this.mainControl.CreateBitmap("fish bitmap", (Bitmap)bmp.Clone());
            }

            using (var bmp = new Bitmap("..\\..\\mask.png"))
            {
                var mask = this.mainControl.CreateBitmapBrush("mask", (Bitmap)bmp.Clone());
                mask.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                mask.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                mask.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;

                this.mainControl.CreateBitmap("mask bitmap", (Bitmap)bmp.Clone());
            }
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            var rcBrushRect = new RectangleF(0, 0, 205, 141);

            // 背景色塗り潰し
            e.RenderTarget.Clear(Color.White);

            // オリジナルビットマップ
            e.RenderTarget.SetTransform(5, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["original"]);

            // マスクビットマップ
            e.RenderTarget.SetTransform(255, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["mask"]);

            // 重ね合わせ
            e.RenderTarget.SetTransform(500, 5);
            e.RenderTarget.SetAntialiasMode(AntialiasMode.ANTIALIAS_MODE_ALIASED);

            e.RenderTarget.FillOpacityMask(e.Resources["mask bitmap"],
                                           e.Resources["original"],
                                           OpacityMaskContent.OPACITY_MASK_CONTENT_GRAPHICS,
                                           rcBrushRect);

            e.RenderTarget.SetAntialiasMode(AntialiasMode.ANTIALIAS_MODE_PER_PRIMITIVE);
        }
    }
}
