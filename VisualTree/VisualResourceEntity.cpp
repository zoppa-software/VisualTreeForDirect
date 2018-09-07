#include "stdafx.h"
#include "VisualResourceEntity.h"
#include "VisualResourceOfSolidColorBrush.h"

namespace VisualTree
{
    /// <summary>色設定を変更する。</summary>
    /// <param name="color">変更する色。</param>
    void VisualResourceEntityOfSolidBrush::SetColor(System::Drawing::Color color) {
        if (this->resource->GetType() == VisualResourceOfSolidColorBrush::typeid) {
            D2D1_COLOR_F clr = D2D1::ColorF(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
            ((ID2D1SolidColorBrush*)this->instance)->SetColor(clr);
        }
    }
}