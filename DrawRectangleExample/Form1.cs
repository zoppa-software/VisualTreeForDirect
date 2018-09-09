using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
            this.mainControl.CreateSolidColorBrush("lightSlateGrayBrush", Color.LightSlateGray);
            this.mainControl.CreateSolidColorBrush("cornflowerBlueBrush", Color.CornflowerBlue);
        }

        private void mainControl_VisualRenderEvent(object sender, VisualTree.VisualRenderEventArgs e)
        {
            e.RenderTarget.Clear(Color.White);

            for (int x = 0; x < this.mainControl.Width; x += 10)
            {
                e.RenderTarget.DrawLine(new PointF(x, 0),
                                        new PointF(x, this.mainControl.Height),
                                        e.Resources["lightSlateGrayBrush"], 0.5f);
            }

            for (int y = 0; y < this.mainControl.Height; y += 10)
            {
                e.RenderTarget.DrawLine(new PointF(0, y),
                                        new PointF(this.mainControl.Width, y),
                                        e.Resources["cornflowerBlueBrush"], 0.5f);
            }

            // 二つの四角
            var rectangle1 = new RectangleF(this.mainControl.Width / 2 - 50.0f,
                                            this.mainControl.Height / 2 - 50.0f,
                                            100.0f,
                                            100.0f);

            var rectangle2 = new RectangleF(this.mainControl.Width / 2 - 100.0f,
                                            this.mainControl.Height / 2 - 100.0f,
                                            200.0f,
                                            200.0f);

            e.RenderTarget.FillRectangle(rectangle1, e.Resources["lightSlateGrayBrush"]);
            e.RenderTarget.DrawRectangle(rectangle2, e.Resources["cornflowerBlueBrush"], 1);
        }
    }
}
