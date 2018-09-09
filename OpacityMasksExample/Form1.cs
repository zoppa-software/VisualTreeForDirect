﻿using System;
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
            // 矩形ジオメトリを作成
            this.mainControl.CreateRectangleGeometry("rectGeo", new RectangleF(0, 0, 148, 148));

            this.mainControl.CreateSolidColorBrush("blackBrush", Color.Black);

            using (var bmp = new Bitmap("..\\..\\s1.png")) {
                var linearFadeFlowersBitmap = this.mainControl.CreateBitmapBrush("linearFadeFlowersBitmap", (Bitmap)bmp.Clone());
                linearFadeFlowersBitmap.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                linearFadeFlowersBitmap.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                linearFadeFlowersBitmap.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            }

            using (var bmp = new Bitmap("..\\..\\s2.png")) {
                var radialFadeFlowersBitmapBrush = this.mainControl.CreateBitmapBrush("radialFadeFlowersBitmapBrush", (Bitmap)bmp.Clone());
                radialFadeFlowersBitmapBrush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                radialFadeFlowersBitmapBrush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                radialFadeFlowersBitmapBrush.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            }

            using (var bmp = new Bitmap("..\\..\\s3.png")) {
                var fernBitmapBrush = this.mainControl.CreateBitmapBrush("fernBitmapBrush", (Bitmap)bmp.Clone());
                fernBitmapBrush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                fernBitmapBrush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                fernBitmapBrush.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            }

            using (var bmp = new Bitmap("..\\..\\s3_mask.png")) {
                this.mainControl.CreateBitmap("bitmapMask", (Bitmap)bmp.Clone());

                var bitmapMaskBrush = this.mainControl.CreateBitmapBrush("bitmapMaskBrush", (Bitmap)bmp.Clone());
                bitmapMaskBrush.Properties.ExtendModeX = ExtendModeParameter.EXTEND_MODE_CLAMP;
                bitmapMaskBrush.Properties.ExtendModeY = ExtendModeParameter.EXTEND_MODE_CLAMP;
                bitmapMaskBrush.Properties.InterpolationMode = BitmapInterpolationMode.BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR;
            }

            var linearGradientBrush = this.mainControl.CreateLinearGradientBrush("linearGradientBrush");
            linearGradientBrush.Propertes.StartPoint = new PointF(0, 0);
            linearGradientBrush.Propertes.EndPoint = new PointF(150, 150);
            linearGradientBrush.AddGradientStop(Color.Black, 0);
            linearGradientBrush.AddGradientStop(Color.FromArgb(0, 255, 255, 255), 1);

            var radialGradientBrush = this.mainControl.CreateRadialGradientBrush("radialGradientBrush");
            radialGradientBrush.Propertes.Center = new PointF(75, 75);
            radialGradientBrush.Propertes.GradientOriginOffset = new PointF(0, 0);
            radialGradientBrush.Propertes.RadiusX = 75;
            radialGradientBrush.Propertes.RadiusY = 75;
            radialGradientBrush.AddGradientStop(Color.Black, 0);
            radialGradientBrush.AddGradientStop(Color.FromArgb(0, 255, 255, 255), 1);
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            e.RenderTarget.Clear(Color.White);

            // ブラシ塗りつぶし矩形領域
            var rcBrushRect = new RectangleF(0, 0, 148, 148);

            //-------------------------
            // リニアグラデーション
            e.RenderTarget.SetTransform(5, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["linearFadeFlowersBitmap"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            e.RenderTarget.SetTransform(205, 5);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["linearGradientBrush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            // 不透明マスクとして線形グラデーションブラシを使用
            e.RenderTarget.SetTransform(405, 5);
            e.RenderTarget.FillGeometry(e.Resources["rectGeo"], e.Resources["linearFadeFlowersBitmap"], e.Resources["linearGradientBrush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            //-------------------------
            // ラジアルグラデーション
            e.RenderTarget.SetTransform(5, 205);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["radialFadeFlowersBitmapBrush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            e.RenderTarget.SetTransform(205, 205);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["radialGradientBrush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            // 不透明マスクとして放射グラデーションブラシを使用
            e.RenderTarget.SetTransform(405, 205);
            e.RenderTarget.FillGeometry(e.Resources["rectGeo"], e.Resources["radialFadeFlowersBitmapBrush"], e.Resources["radialGradientBrush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            //-------------------------
            // ビットマップマスク
            e.RenderTarget.SetTransform(5, 405);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["fernBitmapBrush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            e.RenderTarget.SetTransform(205, 405);
            e.RenderTarget.FillRectangle(rcBrushRect, e.Resources["bitmapMaskBrush"]);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);

            // 不透明マスクとしてビットマップブラシを使用
            e.RenderTarget.SetTransform(405, 405);
            e.RenderTarget.SetAntialiasMode(AntialiasMode.ANTIALIAS_MODE_ALIASED);
            e.RenderTarget.FillOpacityMask(e.Resources["bitmapMask"],
                                           e.Resources["fernBitmapBrush"],
                                           OpacityMaskContent.OPACITY_MASK_CONTENT_GRAPHICS,
                                           rcBrushRect);
            e.RenderTarget.SetAntialiasMode(AntialiasMode.ANTIALIAS_MODE_PER_PRIMITIVE);
            e.RenderTarget.DrawRectangle(rcBrushRect, e.Resources["blackBrush"], 1);
        }
    }
}
