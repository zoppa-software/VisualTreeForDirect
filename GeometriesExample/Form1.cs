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
            this.mainControl.CreateSolidColorBrush("brush", Color.Black);

            // ビットマップブラシ
            using (var bmp = new Bitmap(16, 16)) {
                using (var g = Graphics.FromImage(bmp)) {
                    g.Clear(Color.White);
                    g.DrawLine(Pens.LightGray, 8, 0, 8, 16);
                    g.DrawLine(Pens.LightGray, 0, 8, 16, 8);
                }
                this.mainControl.CreateBitmapBrush("bitmap", (Bitmap)bmp.Clone());
            }

            // グラデーション
            var grad = this.mainControl.CreateRadialGradientBrush("grad");
            grad.AddGradientStop(Color.Gold, 0);
            grad.AddGradientStop(Color.Orange, 0.85f);
            grad.AddGradientStop(Color.OrangeRed, 1);
            grad.Propertes.Center = new PointF(330, 330);
            grad.Propertes.GradientOriginOffset = new PointF(140, 140);
            grad.Propertes.RadiusX = 140;
            grad.Propertes.RadiusY = 140;

            // 左の山
            var leftMon = this.mainControl.CreatePathGeometry("left mountain");
            using (var sink = leftMon.CreateGeometrySink())
            {
                sink.SetFillMode(VisualResourceOfPathGeometry.FILL_MODE.FILL_MODE_WINDING);
                sink.BeginFigure(new PointF(346, 255), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_FILLED);
                var points = new PointF[] {
                    new PointF(267, 177),
                    new PointF(236, 192),
                    new PointF(212, 160),
                    new PointF(156, 255),
                    new PointF(346, 255),
                };
                sink.AddLines(points);
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_CLOSED);
            }

            // 右の山
            var rightMon = this.mainControl.CreatePathGeometry("right mountain");
            using (var sink = rightMon.CreateGeometrySink())
            {
                sink.SetFillMode(VisualResourceOfPathGeometry.FILL_MODE.FILL_MODE_WINDING);
                sink.BeginFigure(new PointF(575, 263), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_FILLED);
                var points = new PointF[] {
                    new PointF(481, 146),
                    new PointF(449, 181),
                    new PointF(433, 159),
                    new PointF(401, 214),
                    new PointF(381, 199),
                    new PointF(323, 263),
                    new PointF(575, 263),
                };
                sink.AddLines(points);
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_CLOSED);
            }

            var sun = this.mainControl.CreatePathGeometry("sun geometry");
            using (var sink = sun.CreateGeometrySink())
            {
                sink.BeginFigure(new PointF(270, 255), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_FILLED);
                sink.AddArc(new VisualResourceOfPathGeometry.ArcSegment(new PointF(440, 255),
                                                                        new SizeF(85, 85),
                                                                        0,
                                                                        VisualResourceOfPathGeometry.SWEEP_DIRECTION.SWEEP_DIRECTION_CLOCKWISE,
                                                                        VisualResourceOfPathGeometry.ARC_SIZE.ARC_SIZE_SMALL));
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_OPEN);

                sink.BeginFigure(new PointF(299, 182), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_HOLLOW);
                sink.AddBeziers(new VisualResourceOfPathGeometry.BezierSegment[] {
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(299, 182), new PointF(294, 176), new PointF(285, 178)),
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(276, 179), new PointF(272, 173), new PointF(272, 173)),
                });
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_OPEN);

                sink.BeginFigure(new PointF(354, 156), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_HOLLOW);
                sink.AddBeziers(new VisualResourceOfPathGeometry.BezierSegment[] {
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(354, 156), new PointF(358, 149), new PointF(354, 142)),
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(349, 134), new PointF(354, 127), new PointF(354, 127)),
                });
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_OPEN);

                sink.BeginFigure(new PointF(322, 164), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_HOLLOW);
                sink.AddBeziers(new VisualResourceOfPathGeometry.BezierSegment[] {
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(322, 164), new PointF(322, 156), new PointF(314, 152)),
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(306, 149), new PointF(305, 141), new PointF(305, 141)),
                });
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_OPEN);

                sink.BeginFigure(new PointF(385, 164), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_HOLLOW);
                sink.AddBeziers(new VisualResourceOfPathGeometry.BezierSegment[] {
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(385, 164), new PointF(392, 161), new PointF(394, 152)),
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(395, 144), new PointF(402, 141), new PointF(402, 142)),
                });
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_OPEN);

                sink.BeginFigure(new PointF(408, 182), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_HOLLOW);
                sink.AddBeziers(new VisualResourceOfPathGeometry.BezierSegment[] {
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(408, 182), new PointF(416, 184), new PointF(422, 178)),
                    new VisualResourceOfPathGeometry.BezierSegment(new PointF(428, 171), new PointF(435, 173), new PointF(435, 173)),
                });
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_OPEN);
            }

            var river = this.mainControl.CreatePathGeometry("river geometry");
            using (var sink = river.CreateGeometrySink())
            {
                sink.SetFillMode(VisualResourceOfPathGeometry.FILL_MODE.FILL_MODE_WINDING);
                sink.BeginFigure(new PointF(183, 392), VisualResourceOfPathGeometry.FIGURE_BEGIN.FIGURE_BEGIN_FILLED);
                sink.AddBezier(new PointF(238, 284), new PointF(472, 345), new PointF(356, 303));
                sink.AddBezier(new PointF(237, 261), new PointF(333, 256), new PointF(333, 256));
                sink.AddBezier(new PointF(335, 257), new PointF(241, 261), new PointF(411, 306));
                sink.AddBezier(new PointF(574, 350), new PointF(288, 324), new PointF(296, 392));
                sink.EndFigure(VisualResourceOfPathGeometry.FIGURE_END.FIGURE_END_CLOSED);
            }
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            e.RenderTarget.Clear(Color.White);

            e.RenderTarget.FillRectangle(this.ClientRectangle, e.Resources["bitmap"]);

            e.RenderTarget.FillGeometry(e.Resources["sun geometry"], e.Resources["grad"]);

            e.Resources["brush"].SetColor(Color.Black);
            e.RenderTarget.DrawGeometry(e.Resources["sun geometry"], e.Resources["brush"], 1.0f);

            // 左の山
            e.Resources["brush"].SetColor(Color.OliveDrab);
            e.RenderTarget.FillGeometry(e.Resources["left mountain"], e.Resources["brush"]);
            e.Resources["brush"].SetColor(Color.Black);
            e.RenderTarget.DrawGeometry(e.Resources["left mountain"], e.Resources["brush"], 1.0f);

            // 川
            e.Resources["brush"].SetColor(Color.LightSkyBlue);
            e.RenderTarget.FillGeometry(e.Resources["river geometry"], e.Resources["brush"]);
            e.Resources["brush"].SetColor(Color.Black);
            e.RenderTarget.DrawGeometry(e.Resources["river geometry"], e.Resources["brush"], 1.0f);

            // 右の山
            e.Resources["brush"].SetColor(Color.YellowGreen);
            e.RenderTarget.FillGeometry(e.Resources["right mountain"], e.Resources["brush"]);
            e.Resources["brush"].SetColor(Color.Black);
            e.RenderTarget.DrawGeometry(e.Resources["right mountain"], e.Resources["brush"], 1.0f);
        }
    }
}
