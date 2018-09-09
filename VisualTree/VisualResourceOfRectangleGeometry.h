#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>��`�W�I���g�����\�[�X�B</summary>
	public ref class VisualResourceOfRectangleGeometry
		: public VisualResource
	{
	private:
        // �W�I���g��
		ID2D1RectangleGeometry * geometry;

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="factory">�t�@�N�g���@�\�B</param>
        /// <param name="rectangle">�Ώۋ�`�B</param>
		VisualResourceOfRectangleGeometry(String ^ name,
                                          ID2D1Factory * factory,
                                          RectangleF rectangle)
			: VisualResource(name)
		{
            D2D1_RECT_F rec = D2D1::RectF(rectangle.Left,
                                          rectangle.Top,
                                          rectangle.Right,
                                          rectangle.Bottom);
			ID2D1RectangleGeometry * geo;
			HRESULT hr = factory->CreateRectangleGeometry(rec, &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
				throw gcnew ApplicationException("error");
			}
		}

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfRectangleGeometry() {}

	public:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
		VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
			return gcnew VisualResourceEntity2D(this, this->geometry, true);
		}
	};
}