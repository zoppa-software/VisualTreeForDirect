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
    /// <summary>�P�F�u���V���\�[�X�B</summary>
	public ref class VisualResourceOfSolidColorBrush sealed
		: public VisualResource
	{
	private:
        // �F�����l
        float	alpha, red, green, blue;

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="red">�ԐF�����l�B</param>
        /// <param name="green">�ΐF�����l�B</param>
        /// <param name="blue">�F�����l�B</param>
        /// <param name="alpha">���������l�B</param>
		VisualResourceOfSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
			: VisualResource(name),
              alpha(alpha / 255.0f),
              red(red / 255.0f),
              green(green / 255.0f),
              blue(blue / 255.0f) {}

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfSolidColorBrush() {}

	public:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            ID2D1SolidColorBrush * brush;
            D2D1_COLOR_F color = D2D1::ColorF(this->red, this->green, this->blue, this->alpha);
            renderTarget->CreateSolidColorBrush(color, &brush);
            return gcnew VisualResourceEntityOfSolidBrush(this, brush);
        }

        /// <summary>�F��ύX����B</summary>
        /// <param name="color">�F�B</param>
        void SetColor(Color color)
        {
            this->red = red / 255.0f;
            this->green = green / 255.0f;
            this->blue = blue / 255.0f;
        }

        /// <summary>�����x��ύX����B</summary>
        /// <param name="opacity">�����x�i0 �` 255�j�B</param>
        void SetOpacity(int opacity)
        {
            this->alpha = opacity / 255.0f;
        }
	};
}
