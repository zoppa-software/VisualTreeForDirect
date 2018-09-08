#include "stdafx.h"
#include <vcclr.h>  
#include "VisualRenderTarget.h"

namespace VisualTree
{
    //-----------------------------------------------------------------------------
    // À•W•ÏŠ·
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::SetTransform()
    {
        this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
    }

    void VisualRenderTarget::SetTransform(int offsetX, int offsetY)
    {
        this->renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(D2D1::SizeF((float)offsetX, (float)offsetY)));
    }

    void VisualRenderTarget::PushAxisAlignedClip(RectangleF rect, AntialiasMode mode)
    {
        D2D1_RECT_F rec = D2D1::RectF((float)rect.Left,
                                      (float)rect.Top,
                                      (float)rect.Right,
                                      (float)rect.Bottom);
        this->renderTarget->PushAxisAlignedClip(rec, (D2D1_ANTIALIAS_MODE)mode);
    }

    void VisualRenderTarget::PopAxisAlignedClip()
    {
        this->renderTarget->PopAxisAlignedClip();
    }

    //-----------------------------------------------------------------------------
    // ‡¬Ý’è
    //-----------------------------------------------------------------------------
    void VisualRenderTarget::SetAntialiasMode(AntialiasMode mode)
    {
        this->renderTarget->SetAntialiasMode((D2D1_ANTIALIAS_MODE)mode);
    }

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
            D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(rect.Left, rect.Top),
                                                 rect.Width, rect.Height);
            this->renderTarget->DrawEllipse(ellipse, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellipse = D2D1::Ellipse(D2D1::Point2F(rect.Left, rect.Top),
                                                 rect.Width, rect.Height);
            this->renderTarget->DrawEllipse(ellipse, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

    void VisualRenderTarget::DrawEllipse(Ellipse ellipse, VisualResourceEntity ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellp = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                                              (float)ellipse.RadiusX,
                                              (float)ellipse.RadiusY);
            this->renderTarget->DrawEllipse(ellp, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawEllipse(Ellipse ellipse, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellp = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                                              (float)ellipse.RadiusX,
                                              (float)ellipse.RadiusY);
            this->renderTarget->DrawEllipse(ellp, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

    void VisualRenderTarget::DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth)
    {
        if (geometry != nullptr && brush != nullptr) {
            this->renderTarget->DrawGeometry((ID2D1Geometry*)geometry->GetInstance(), (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle)
    {
        if (geometry != nullptr && brush != nullptr) {
            this->renderTarget->DrawGeometry((ID2D1Geometry*)geometry->GetInstance(), (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
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

    void VisualRenderTarget::DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_POINT_2F pos1 = D2D1::Point2F(startPt.X, startPt.Y);
            D2D1_POINT_2F pos2 = D2D1::Point2F(endPt.X, endPt.Y);
            this->renderTarget->DrawLine(pos1, pos2, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }

        //this->renderTarget->DrawRectangle;
    void VisualRenderTarget::DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush, float strokeWidth)
    {
        if (brush != nullptr) {
            D2D1_RECT_F rec = D2D1::RectF((float)rectangle.Left,
                                          (float)rectangle.Top,
                                          (float)rectangle.Right,
                                          (float)rectangle.Bottom);
            this->renderTarget->DrawRectangle(rec, (ID2D1Brush*)brush->GetInstance(), strokeWidth);
        }
    }

    void VisualRenderTarget::DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle)
    {
        if (brush != nullptr) {
            D2D1_RECT_F rec = D2D1::RectF((float)rectangle.Left,
                                          (float)rectangle.Top,
                                          (float)rectangle.Right,
                                          (float)rectangle.Bottom);
            this->renderTarget->DrawRectangle(rec, (ID2D1Brush*)brush->GetInstance(), strokeWidth, (ID2D1StrokeStyle*)strokeStyle->GetInstance());
        }
    }
        //this->renderTarget->DrawRoundedRectangle;

    void VisualRenderTarget::DrawText(String ^ text, VisualResourceEntity ^ format, RectangleF rect, VisualResourceEntity ^ brush)
    {
        if (format != nullptr && brush != nullptr) {
            pin_ptr<const wchar_t> txt = text != nullptr ? PtrToStringChars(text) : (WCHAR*)NULL;
            D2D1_RECT_F rec = D2D1::RectF(rect.Left, rect.Top, rect.Right, rect.Bottom);

            this->renderTarget->DrawText(txt, text->Length,
                (IDWriteTextFormat*)format->GetWriteInstance(), rec, (ID2D1Brush*)brush->GetInstance());
        }
    }
        //this->renderTarget->DrawTextLayout;
        //this->renderTarget->FillRoundedRectangle;

    void VisualRenderTarget::FillEllipse(Ellipse ellipse, VisualResourceEntity ^ brush)
    {
        if (brush != nullptr) {
            D2D1_ELLIPSE ellp = D2D1::Ellipse(D2D1::Point2F(ellipse.CenterPoint.X, ellipse.CenterPoint.Y),
                                              (float)ellipse.RadiusX,
                                              (float)ellipse.RadiusY);
            this->renderTarget->FillEllipse(ellp, (ID2D1Brush*)brush->GetInstance());
        }
    }

    void VisualRenderTarget::FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush)
    {
        if (brush != nullptr && geometry->GetInstance() != NULL) {
            this->renderTarget->FillGeometry((ID2D1Geometry*)geometry->GetInstance(), (ID2D1Brush*)brush->GetInstance());
        }
    }

    void VisualRenderTarget::FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, VisualResourceEntity ^ opacitybrush)
    {
        if (brush != nullptr && geometry->GetInstance() != NULL) {
            this->renderTarget->FillGeometry((ID2D1Geometry*)geometry->GetInstance(), (ID2D1Brush*)brush->GetInstance(), (ID2D1Brush*)opacitybrush->GetInstance());
        }
    }

        //this->renderTarget->FillMesh;

    void VisualRenderTarget::FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask)
    {
        if (bitmap != nullptr && brush != nullptr) {
            this->renderTarget->FillOpacityMask((ID2D1Bitmap*)bitmap->GetInstance(),
                                                (ID2D1Brush*)brush->GetInstance(),
                                                (D2D1_OPACITY_MASK_CONTENT)opacityMask);
        }
    }

    void VisualRenderTarget::FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask, RectangleF destinationRectangle)
    {
        if (bitmap != nullptr && brush != nullptr) {
            D2D1_RECT_F dest = D2D1::RectF((float)destinationRectangle.Left,
                                           (float)destinationRectangle.Top,
                                           (float)destinationRectangle.Right,
                                           (float)destinationRectangle.Bottom);

            this->renderTarget->FillOpacityMask((ID2D1Bitmap*)bitmap->GetInstance(),
                                                (ID2D1Brush*)brush->GetInstance(),
                                                (D2D1_OPACITY_MASK_CONTENT)opacityMask,
                                                &dest);
        }
    }

    void VisualRenderTarget::FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush,
                                             OpacityMaskContent opacityMask, RectangleF destinationRectangle, RectangleF sourceRectangle)
    {
        if (bitmap != nullptr && brush != nullptr) {
            D2D1_RECT_F dest = D2D1::RectF((float)destinationRectangle.Left,
                                           (float)destinationRectangle.Top,
                                           (float)destinationRectangle.Right,
                                           (float)destinationRectangle.Bottom);
            D2D1_RECT_F src = D2D1::RectF((float)sourceRectangle.Left,
                                          (float)sourceRectangle.Top,
                                          (float)sourceRectangle.Right,
                                          (float)sourceRectangle.Bottom);

            this->renderTarget->FillOpacityMask((ID2D1Bitmap*)bitmap->GetInstance(),
                                                (ID2D1Brush*)brush->GetInstance(),
                                                (D2D1_OPACITY_MASK_CONTENT)opacityMask,
                                                &dest, &src);
        }
    }

    void VisualRenderTarget::FillRectangle(RectangleF rectangle, VisualResourceEntity ^ brush)
    {
        if (brush != nullptr) {
            D2D1_RECT_F rec = D2D1::RectF((float)rectangle.Left,
                                          (float)rectangle.Top,
                                          (float)rectangle.Right,
                                          (float)rectangle.Bottom);
            this->renderTarget->FillRectangle(rec, (ID2D1Brush*)brush->GetInstance());
        }
    }

        //this->renderTarget->FillRoundedRectangle;
        //this->renderTarget->SetAntialiasMode;
}