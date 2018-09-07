#include "stdafx.h"
#include "VisualRenderTarget.h"

namespace VisualTree
{
    //-----------------------------------------------------------------------------
    // ”wŒiFƒNƒŠƒA
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::Clear(Color color)
    {
        D2D1::ColorF clr = D2D1::ColorF(color.R / 255.0f,
            color.G / 255.0f,
            color.B / 255.0f,
            color.A / 255.0f);
        this->renderTarget->Clear(clr);
    }

    void VisualRenderTarget::Clear(int red, int green, int blue, int alpha)
    {
        D2D1::ColorF clr = D2D1::ColorF(red / 255.0f,
            green / 255.0f,
            blue / 255.0f,
            alpha / 255.0f);
        this->renderTarget->Clear(clr);
    }

    //-----------------------------------------------------------------------------
    // •`‰æAPI
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(rect.Left, rect.Top), rect.Width, rect.Height);
            this->renderTarget->DrawEllipse(ellipse, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth)
    {
        this->renderTarget->DrawGeometry((ID2D1Geometry*)geometry->GetInstance(), (ID2D1Brush*)brush->GetInstance(), strokeWidth);
    }
        //this->renderTarget->DrawGlyphRun;
    void VisualRenderTarget::DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_POINT_2F pos1 = D2D1::Point2F(startPt.X, startPt.Y);
            D2D1_POINT_2F pos2 = D2D1::Point2F(endPt.X, endPt.Y);
            this->renderTarget->DrawLine(pos1, pos2, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }
        //this->renderTarget->DrawRectangle;
        //this->renderTarget->DrawRoundedRectangle;
        //this->renderTarget->DrawText;
        //this->renderTarget->DrawTextLayout;
        //this->renderTarget->FillRoundedRectangle;
        //this->renderTarget->FillEllipse;
    void VisualRenderTarget::FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush)
    {
        if (brush != nullptr && geometry->GetInstance() != NULL) {
            this->renderTarget->FillGeometry((ID2D1Geometry*)geometry->GetInstance(), (ID2D1Brush*)brush->GetInstance());
        }
    }
        //this->renderTarget->FillMesh;
        //this->renderTarget->FillOpacityMask;

    void VisualRenderTarget::FillRectangle(System::Drawing::Rectangle ^ rectangle, VisualResourceEntity ^ brush)
    {
        if (brush != nullptr) {
            D2D1_RECT_F rec = D2D1::RectF((float)rectangle->Left,
                                          (float)rectangle->Top,
                                          (float)rectangle->Right,
                                          (float)rectangle->Bottom);
            this->renderTarget->FillRectangle(rec, (ID2D1Brush*)brush->GetInstance());
        }
    }

        //this->renderTarget->FillRoundedRectangle;
        //this->renderTarget->SetAntialiasMode;
}