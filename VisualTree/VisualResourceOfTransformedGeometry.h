#pragma once

#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Matrix.h"
#include "VisualResource.h"
#include "VisualResourceOfPathGeometry.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>��`�W�I���g�����\�[�X�B</summary>
	public ref class VisualResourceOfTransformedGeometry
		: public VisualResource
	{
	private:
        // �W�I���g��
		ID2D1TransformedGeometry * geometry;

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="factory">�t�@�N�g���@�\�B</param>
        /// <param name="rectangle">�Ώۋ�`�B</param>
		VisualResourceOfTransformedGeometry(String ^ name,
                                            ID2D1Factory * factory,
                                            VisualResourceOfPathGeometry ^ pathGeometry,
                                            Matrix matrix)
			: VisualResource(name)
		{
			ID2D1TransformedGeometry * geo;
			HRESULT hr = factory->CreateTransformedGeometry(pathGeometry->GetGeometry(), matrix.Convert(), &geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
				throw gcnew ApplicationException("error");
			}
		}

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfTransformedGeometry() {}

	public:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
		VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
			return gcnew VisualResourceEntity2D(this, this->geometry, true);
		}
	};
}