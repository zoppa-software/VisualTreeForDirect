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
            var path = this.mainControl.CreatePathGeometry("path geometry");
            using (var sink = path.CreateGeometrySink()) {
                sink.SetFillMode(FillMode.FILL_MODE_WINDING);
                sink.BeginFigure(new PointF(20, 50), FigureBegin.FIGURE_BEGIN_FILLED);
                sink.AddLine(130, 50);
                sink.AddLine(20, 130);
                sink.AddLine(80, 0);
                sink.AddLine(130, 130);
                sink.EndFigure(FigureEnd.FIGURE_END_CLOSED);
            }

            using (var bmp = new Bitmap("..\\..\\fish.png")) {
                this.mainControl.CreateBitmap("fish bitmap", (Bitmap)bmp.Clone());
            }

            var brush = this.mainControl.CreateSolidColorBrush("brush", Color.Orange);
            brush.SetOpacity((int)(255 * 0.75));
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            e.RenderTarget.Clear(Color.White);

            // レイヤークリップ前
            e.RenderTarget.SetTransform(50, 50);
            e.RenderTarget.DrawBitmap(e.Resources["fish bitmap"], new RectangleF(0, 0, 205, 141));
            e.RenderTarget.FillRectangle(new RectangleF(0, 0, 25, 25), e.Resources["brush"]);
            e.RenderTarget.FillRectangle(new RectangleF(25, 25, 25, 25), e.Resources["brush"]);
            e.RenderTarget.FillRectangle(new RectangleF(50, 50, 25, 25), e.Resources["brush"]);
            e.RenderTarget.FillRectangle(new RectangleF(75, 75, 25, 25), e.Resources["brush"]);
            e.RenderTarget.FillRectangle(new RectangleF(100, 100, 25, 25), e.Resources["brush"]);
            e.RenderTarget.FillRectangle(new RectangleF(125, 125, 25, 25), e.Resources["brush"]);

            // レイヤークリップ後
            e.RenderTarget.SetTransform(350, 50);
            using (var layer = e.RenderTarget.CreateLayer()) {
                layer.Parameters.geometricMask = e.Resources["path geometry"];
                e.RenderTarget.PushLayer(layer);

                e.RenderTarget.DrawBitmap(e.Resources["fish bitmap"], new RectangleF(0, 0, 205, 141));
                e.RenderTarget.FillRectangle(new RectangleF(0, 0, 25, 25), e.Resources["brush"]);
                e.RenderTarget.FillRectangle(new RectangleF(25, 25, 25, 25), e.Resources["brush"]);
                e.RenderTarget.FillRectangle(new RectangleF(50, 50, 25, 25), e.Resources["brush"]);
                e.RenderTarget.FillRectangle(new RectangleF(75, 75, 25, 25), e.Resources["brush"]);
                e.RenderTarget.FillRectangle(new RectangleF(100, 100, 25, 25), e.Resources["brush"]);
                e.RenderTarget.FillRectangle(new RectangleF(125, 125, 25, 25), e.Resources["brush"]);

                e.RenderTarget.PopLayer();
            }
        }
    }
}
