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

            // 青ブラシ
            this.mainControl.CreateSolidColorBrush("cornflower blue", Color.CornflowerBlue);

            // フォント設定
            var format = this.mainControl.CreateTextFormat("text format");
            format.FontFamilyName = "yu gothic ui";
            format.FontWeight = DWriteFontWeight.DWRITE_FONT_WEIGHT_REGULAR;
            format.FontStyle = DWriteFontStyle.DWRITE_FONT_STYLE_NORMAL;
            format.FontSize = 14;

            // 背景ブラシ作成
            using (var bmp = new Bitmap(10, 10)) {
                using (var g = Graphics.FromImage(bmp)) {
                    g.Clear(Color.White);
                    g.DrawLine(Pens.WhiteSmoke, 0, 0, 10, 0);
                    g.DrawLine(Pens.WhiteSmoke, 0, 0, 0, 10);
                }
                this.mainControl.CreateBitmapBrush("grid pattern", (Bitmap)bmp.Clone());
            }

            var strokeStyleSolidMiter = this.mainControl.CreateStrokeStyle("strokeStyleSolidMiter");
            strokeStyleSolidMiter.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiter.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiter.Properties.dashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiter.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleSolidMiter.Properties.miterLimit = 2;
            strokeStyleSolidMiter.Properties.dashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidMiter.Properties.dashOffset = 0;

            var strokeStyleSolidBevel = this.mainControl.CreateStrokeStyle("strokeStyleSolidBevel");
            strokeStyleSolidBevel.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidBevel.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidBevel.Properties.dashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidBevel.Properties.lineJoin = LineJoin.LINE_JOIN_BEVEL;
            strokeStyleSolidBevel.Properties.miterLimit = 2;
            strokeStyleSolidBevel.Properties.dashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidBevel.Properties.dashOffset = 0;

            var strokeStyleSolidMiterOrBevel = this.mainControl.CreateStrokeStyle("strokeStyleSolidMiterOrBevel");
            strokeStyleSolidMiterOrBevel.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiterOrBevel.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiterOrBevel.Properties.dashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidMiterOrBevel.Properties.lineJoin = LineJoin.LINE_JOIN_MITER_OR_BEVEL;
            strokeStyleSolidMiterOrBevel.Properties.miterLimit = 2;
            strokeStyleSolidMiterOrBevel.Properties.dashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidMiterOrBevel.Properties.dashOffset = 0;

            var strokeStyleSolidRoundwRoundCap = this.mainControl.CreateStrokeStyle("strokeStyleSolidRoundwRoundCap");
            strokeStyleSolidRoundwRoundCap.Properties.startCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleSolidRoundwRoundCap.Properties.endCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleSolidRoundwRoundCap.Properties.dashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwRoundCap.Properties.lineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwRoundCap.Properties.miterLimit = 2;
            strokeStyleSolidRoundwRoundCap.Properties.dashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwRoundCap.Properties.dashOffset = 0;

            var strokeStyleSolidRoundwFlatCap = this.mainControl.CreateStrokeStyle("strokeStyleSolidRoundwFlatCap");
            strokeStyleSolidRoundwFlatCap.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwFlatCap.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwFlatCap.Properties.dashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwFlatCap.Properties.lineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwFlatCap.Properties.miterLimit = 2;
            strokeStyleSolidRoundwFlatCap.Properties.dashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwFlatCap.Properties.dashOffset = 0;

            var strokeStyleSolidRoundwSquareCap = this.mainControl.CreateStrokeStyle("strokeStyleSolidRoundwSquareCap");
            strokeStyleSolidRoundwSquareCap.Properties.startCap = CapStyle.CAP_STYLE_SQUARE;
            strokeStyleSolidRoundwSquareCap.Properties.endCap = CapStyle.CAP_STYLE_SQUARE;
            strokeStyleSolidRoundwSquareCap.Properties.dashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwSquareCap.Properties.lineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwSquareCap.Properties.miterLimit = 2;
            strokeStyleSolidRoundwSquareCap.Properties.dashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwSquareCap.Properties.dashOffset = 0;

            //if (SUCCEEDED(hr))
            //{
            //    hr = m_pD2DFactory->CreateStrokeStyle(
            //        D2D1::StrokeStyleProperties(
            //            D2D1_CAP_STYLE_TRIANGLE,
            //            D2D1_CAP_STYLE_TRIANGLE,
            //            D2D1_CAP_STYLE_FLAT,
            //            D2D1_LINE_JOIN_ROUND,
            //            2.0f,
            //            D2D1_DASH_STYLE_SOLID,
            //            0.0f),
            //        NULL,
            //        0,
            //        &m_pStrokeStyleSolidRoundwTriangleCap
            //        );
            //}
            var strokeStyleSolidRoundwTriangleCap = this.mainControl.CreateStrokeStyle("strokeStyleSolidRoundwTriangleCap");
            strokeStyleSolidRoundwTriangleCap.Properties.startCap = CapStyle.CAP_STYLE_TRIANGLE;
            strokeStyleSolidRoundwTriangleCap.Properties.endCap = CapStyle.CAP_STYLE_TRIANGLE;
            strokeStyleSolidRoundwTriangleCap.Properties.dashCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleSolidRoundwTriangleCap.Properties.lineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleSolidRoundwTriangleCap.Properties.miterLimit = 2;
            strokeStyleSolidRoundwTriangleCap.Properties.dashStyle = DashStyle.DASH_STYLE_SOLID;
            strokeStyleSolidRoundwTriangleCap.Properties.dashOffset = 0;

            var strokeStyleDash = this.mainControl.CreateStrokeStyle("strokeStyleDash");
            strokeStyleDash.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDash.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDash.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleDash.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleDash.Properties.miterLimit = 10;
            strokeStyleDash.Properties.dashStyle = DashStyle.DASH_STYLE_DASH;
            strokeStyleDash.Properties.dashOffset = 0;

            var strokeStyleDot = this.mainControl.CreateStrokeStyle("strokeStyleDot");
            strokeStyleDot.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDot.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDot.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleDot.Properties.lineJoin = LineJoin.LINE_JOIN_ROUND;
            strokeStyleDot.Properties.miterLimit = 10;
            strokeStyleDot.Properties.dashStyle = DashStyle.DASH_STYLE_DOT;
            strokeStyleDot.Properties.dashOffset = 0;

            var strokeStyleDashDot = this.mainControl.CreateStrokeStyle("strokeStyleDashDot");
            strokeStyleDashDot.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDot.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDot.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleDashDot.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleDashDot.Properties.miterLimit = 10;
            strokeStyleDashDot.Properties.dashStyle = DashStyle.DASH_STYLE_DASH_DOT;
            strokeStyleDashDot.Properties.dashOffset = 0;

            var strokeStyleDashDotDot = this.mainControl.CreateStrokeStyle("strokeStyleDashDotDot");
            strokeStyleDashDotDot.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDotDot.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleDashDotDot.Properties.dashCap = CapStyle.CAP_STYLE_SQUARE;
            strokeStyleDashDotDot.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleDashDotDot.Properties.miterLimit = 10;
            strokeStyleDashDotDot.Properties.dashStyle = DashStyle.DASH_STYLE_DASH_DOT_DOT;
            strokeStyleDashDotDot.Properties.dashOffset = 0;

            // 点線パターン
            var dashes = new float[] { 1.0f, 2.0f, 2.0f, 3.0f, 2.0f, 2.0f };
            var strokeStyleCustomOffsetZero = this.mainControl.CreateStrokeStyle("strokeStyleCustomOffsetZero");
            strokeStyleCustomOffsetZero.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetZero.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetZero.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetZero.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetZero.Properties.miterLimit = 10;
            strokeStyleCustomOffsetZero.Properties.dashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetZero.Properties.dashOffset = 0;
            strokeStyleCustomOffsetZero.DashesAddRange(dashes);

            var strokeStyleCustomOffsetNegOne = this.mainControl.CreateStrokeStyle("strokeStyleCustomOffsetNegOne");
            strokeStyleCustomOffsetNegOne.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegOne.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegOne.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetNegOne.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetNegOne.Properties.miterLimit = 10;
            strokeStyleCustomOffsetNegOne.Properties.dashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetNegOne.Properties.dashOffset = -1;
            strokeStyleCustomOffsetNegOne.DashesAddRange(dashes);

            var strokeStyleCustomOffsetNegTwo = this.mainControl.CreateStrokeStyle("strokeStyleCustomOffsetNegTwo");
            strokeStyleCustomOffsetNegTwo.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegTwo.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetNegTwo.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetNegTwo.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetNegTwo.Properties.miterLimit = 10;
            strokeStyleCustomOffsetNegTwo.Properties.dashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetNegTwo.Properties.dashOffset = -2;
            strokeStyleCustomOffsetNegTwo.DashesAddRange(dashes);

            var strokeStyleCustomOffsetPosOne = this.mainControl.CreateStrokeStyle("strokeStyleCustomOffsetPosOne");
            strokeStyleCustomOffsetPosOne.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosOne.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosOne.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetPosOne.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetPosOne.Properties.miterLimit = 10;
            strokeStyleCustomOffsetPosOne.Properties.dashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetPosOne.Properties.dashOffset = 1;
            strokeStyleCustomOffsetPosOne.DashesAddRange(dashes);

            var strokeStyleCustomOffsetPosTwo = this.mainControl.CreateStrokeStyle("strokeStyleCustomOffsetPosTwo");
            strokeStyleCustomOffsetPosTwo.Properties.startCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosTwo.Properties.endCap = CapStyle.CAP_STYLE_FLAT;
            strokeStyleCustomOffsetPosTwo.Properties.dashCap = CapStyle.CAP_STYLE_ROUND;
            strokeStyleCustomOffsetPosTwo.Properties.lineJoin = LineJoin.LINE_JOIN_MITER;
            strokeStyleCustomOffsetPosTwo.Properties.miterLimit = 10;
            strokeStyleCustomOffsetPosTwo.Properties.dashStyle = DashStyle.DASH_STYLE_CUSTOM;
            strokeStyleCustomOffsetPosTwo.Properties.dashOffset = 2;
            strokeStyleCustomOffsetPosTwo.DashesAddRange(dashes);

            var pathGeometry = this.mainControl.CreatePathGeometry("path geometry");
            using (var sink = pathGeometry.CreateGeometrySink())
            {
                sink.SetFillMode(FillMode.FILL_MODE_WINDING);
                sink.BeginFigure(new PointF(17, 17), FigureBegin.FIGURE_BEGIN_HOLLOW);
                sink.AddLine(45, 85);
                sink.AddLine(85, 45);
                sink.AddLine(85, 125);
                sink.AddLine(165, 17);
                sink.EndFigure(FigureEnd.FIGURE_END_OPEN);
            }
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            // 背景クリア
            e.RenderTarget.Clear(Color.White);

            // 背景描画
            e.RenderTarget.FillRectangle(new RectangleF(0, 0, this.mainControl.Width, this.mainControl.Height), e.Resources["grid pattern"]);

            // Line Join Styles
            e.RenderTarget.SetTransform(10, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidMiter"]);
            e.RenderTarget.DrawText("Miter Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(10, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidBevel"]);
            e.RenderTarget.DrawText("Bevel Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(230, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwRoundCap"]);
            e.RenderTarget.DrawText("Round Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(230, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidMiterOrBevel"]);
            e.RenderTarget.DrawText("Miter or Bevel Line Join", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            // Cap Styles
            e.RenderTarget.SetTransform(480, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwRoundCap"]);
            e.RenderTarget.DrawText("Round Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(700, 20);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwFlatCap"]);
            e.RenderTarget.DrawText("Flat Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(480, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwSquareCap"]);
            e.RenderTarget.DrawText("Square Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            e.RenderTarget.SetTransform(700, 210);
            e.RenderTarget.DrawRectangle(new RectangleF(0.0f, 0.0f, 180.0f, 150.0f), e.Resources["brush"], 1);
            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 16, e.Resources["strokeStyleSolidRoundwTriangleCap"]);
            e.RenderTarget.DrawText("Triangle Caps", e.Resources["text format"], new RectangleF(2, 150, 215, 215), e.Resources["brush"]);

            // Dash Styles
            e.RenderTarget.SetTransform(Matrix.Translation(10, 405));
            e.RenderTarget.DrawLine(new PointF(0, 10), new PointF(200, 10), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleSolidMiter"]);
            e.RenderTarget.DrawText("Dash Style -- Solid", e.Resources["text format"], new RectangleF(0, 20, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 70), new PointF(200, 70), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDash"]);
            e.RenderTarget.DrawText("Dash Style -- Dash", e.Resources["text format"], new RectangleF(0, 80, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 130), new PointF(200, 130), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDot"]);
            e.RenderTarget.DrawText("Dash Style -- Dot", e.Resources["text format"], new RectangleF(0, 140, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 190), new PointF(200, 190), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDashDot"]);
            e.RenderTarget.DrawText("Dash Style -- Dash Dot", e.Resources["text format"], new RectangleF(0, 200, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 250), new PointF(200, 250), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleDashDotDot"]);
            e.RenderTarget.DrawText("Dash Style -- Dash Dot Dot", e.Resources["text format"], new RectangleF(0, 260, 200, 315), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 310), new PointF(200, 310), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetZero"]);
            e.RenderTarget.DrawText("Dash Style -- Custom", e.Resources["text format"], new RectangleF(0, 320, 200, 315), e.Resources["brush"]);

            // Dash Offsets
            e.RenderTarget.SetTransform(Matrix.Translation(300, 405));
            e.RenderTarget.DrawLine(new PointF(0, 10), new PointF(200, 10), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetNegTwo"]);
            e.RenderTarget.DrawText("-2", e.Resources["text format"], new RectangleF(0, 20, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 70), new PointF(200, 70), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetNegOne"]);
            e.RenderTarget.DrawText("-1", e.Resources["text format"], new RectangleF(0, 80, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 130), new PointF(200, 130), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetZero"]);
            e.RenderTarget.DrawText("-0", e.Resources["text format"], new RectangleF(0, 140, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 190), new PointF(200, 190), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetPosOne"]);
            e.RenderTarget.DrawText("1", e.Resources["text format"], new RectangleF(0, 200, 200, 295), e.Resources["brush"]);

            e.RenderTarget.DrawLine(new PointF(0, 250), new PointF(200, 250), e.Resources["cornflower blue"],
                                    10, e.Resources["strokeStyleCustomOffsetPosTwo"]);
            e.RenderTarget.DrawText("2", e.Resources["text format"], new RectangleF(0, 260, 200, 295), e.Resources["brush"]);
        }
    }
}
