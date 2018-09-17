#include "stdafx.h"
#include "VisualResourceEntity.h"
#include "VisualResourceOfSolidColorBrush.h"

namespace VisualTree
{
    //-------------------------------------------------------------------------
    // ブラシ用、リソース実体
    //-------------------------------------------------------------------------
    void VisualResourceEntityOfBrush::SetOpacity(int opacity)
    {
        ((ID2D1Brush*)this->instance)->SetOpacity(opacity / 255.0f);
    }

    void VisualResourceEntityOfBrush::SetTransform()
    {
        ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Identity());
    }

    void VisualResourceEntityOfBrush::SetTransform(float offsetX, float offsetY)
    {
        ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Translation(offsetX, offsetY));
    }

    void VisualResourceEntityOfBrush::SetTransform(Matrix matrix)
    {
        ((ID2D1Brush*)this->instance)->SetTransform(matrix.Convert());
    }

    //-------------------------------------------------------------------------
    // ソリッドブラシ用、リソース実体
    //-------------------------------------------------------------------------
    void VisualResourceEntityOfSolidBrush::SetColor(System::Drawing::Color color)
    {
        D2D1_COLOR_F clr = D2D1::ColorF(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
        ((ID2D1SolidColorBrush*)this->instance)->SetColor(clr);
    }

    void VisualResourceEntityOfSolidBrush::SetOpacity(int opacity)
    {
        ((ID2D1SolidColorBrush*)this->instance)->SetOpacity(opacity / 255.0f);
    }

    void VisualResourceEntityOfSolidBrush::SetTransform()
    {
        ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Identity());
    }

    void VisualResourceEntityOfSolidBrush::SetTransform(float offsetX, float offsetY)
    {
        ((ID2D1Brush*)this->instance)->SetTransform(D2D1::Matrix3x2F::Translation(offsetX, offsetY));
    }

    void VisualResourceEntityOfSolidBrush::SetTransform(Matrix matrix)
    {
        ((ID2D1Brush*)this->instance)->SetTransform(matrix.Convert());
    }

    //-------------------------------------------------------------------------
    // COM用、リソース実体
    //-------------------------------------------------------------------------
    void VisualResourceEntityWrite::SafeRelease()
    {
        if (this->instance != NULL && this->isLongLife) {
            this->instance->Release();
            this->instance = NULL;
        }
    }

    void VisualResourceEntityWrite::ForceRelease()
    {
        if (this->instance != NULL) {
            this->instance->Release();
            this->instance = NULL;
        }
    }

    IUnknown * VisualResourceEntityWrite::GetWriteInstance()
    {
        return this->instance;
    }
}