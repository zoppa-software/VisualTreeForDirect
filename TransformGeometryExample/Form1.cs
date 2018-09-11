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

            // ジオメトリ
            var pathGeometry = this.mainControl.CreatePathGeometry("path geometry");
            using (var sink = pathGeometry.CreateGeometrySink())
            {
                sink.SetFillMode(FillMode.FILL_MODE_WINDING);
                sink.BeginFigure(new PointF(0, 0), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddLine(new PointF(200, 0));
                sink.AddBezier(new PointF(150, 50), new PointF(150, 150), new PointF(200, 200));
                sink.AddLine(new PointF(0, 200));
                sink.AddBezier(new PointF(50, 150), new PointF(50, 50), new PointF(0, 0));
                sink.EndFigure(FigureEnd.FIGURE_END_CLOSED);
            }

            // 変形ジオメトリ
            var transGeometry = this.mainControl.CreateTransformedGeometry("trans geometry",
                                        pathGeometry, Matrix.Rotation(45, new PointF(100, 100)));

            // グラデーションブラシ
            var lgBrush = this.mainControl.CreateLinearGradientBrush("LGBrush");
            lgBrush.AddGradientStop(Color.FromArgb(64, 0, 255, 255), 0);
            lgBrush.AddGradientStop(Color.FromArgb(255, 0, 0, 255), 1);
            lgBrush.Propertes.StartPoint = new PointF(100, 0);
            lgBrush.Propertes.EndPoint = new PointF(100, 200);
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            e.RenderTarget.Clear(Color.White);
            e.RenderTarget.SetTransform(20, 20);

            e.RenderTarget.DrawGeometry(e.Resources["path geometry"], e.Resources["brush"], 10);
            e.RenderTarget.FillGeometry(e.Resources["path geometry"], e.Resources["LGBrush"]);

            var sz = Matrix.Scale(0.5f, 0.5f);
            var tn = Matrix.Translation(this.Width / 2 - 50.0f, this.Height / 2 - 50.0f);
            e.RenderTarget.SetTransform(sz * tn);

            e.RenderTarget.FillGeometry(e.Resources["path geometry"], e.Resources["LGBrush"]);
            e.RenderTarget.FillGeometry(e.Resources["trans geometry"], e.Resources["LGBrush"]);
        }
    }
}
