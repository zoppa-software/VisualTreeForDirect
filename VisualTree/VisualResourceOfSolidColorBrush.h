#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>単色ブラシリソース。</summary>
	public ref class VisualResourceOfSolidColorBrush sealed
		: public VisualResource
	{
	private:
        // 色成分値
        float	alpha, red, green, blue;

	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="red">赤色成分値。</param>
        /// <param name="green">緑色成分値。</param>
        /// <param name="blue">青色成分値。</param>
        /// <param name="alpha">透明成分値。</param>
		VisualResourceOfSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
			: VisualResource(name),
              alpha(alpha / 255.0f),
              red(red / 255.0f),
              green(green / 255.0f),
              blue(blue / 255.0f) {}

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfSolidColorBrush() {}

	public:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            ID2D1SolidColorBrush * brush;
            D2D1_COLOR_F color = D2D1::ColorF(this->red, this->green, this->blue, this->alpha);
            renderTarget->CreateSolidColorBrush(color, &brush);
            return gcnew VisualResourceEntityOfSolidBrush(this, brush);
        }

        /// <summary>色を変更する。</summary>
        /// <param name="color">色。</param>
        void SetColor(Color color)
        {
            this->red = red / 255.0f;
            this->green = green / 255.0f;
            this->blue = blue / 255.0f;
        }

        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        void SetOpacity(int opacity)
        {
            this->alpha = opacity / 255.0f;
        }
	};
}
