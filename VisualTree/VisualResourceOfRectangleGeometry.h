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
    /// <summary>矩形ジオメトリリソース。</summary>
	public ref class VisualResourceOfRectangleGeometry
		: public VisualResource
	{
	private:
        // ジオメトリ
		ID2D1RectangleGeometry * geometry;

	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="factory">ファクトリ機能。</param>
        /// <param name="rectangle">対象矩形。</param>
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

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfRectangleGeometry() {}

	public:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
		VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
			return gcnew VisualResourceEntity2D(this, this->geometry, true);
		}
	};
}