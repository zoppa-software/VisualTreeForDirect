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
    /// <summary>矩形ジオメトリリソース。</summary>
	public ref class VisualResourceOfTransformedGeometry
		: public VisualResource
	{
	private:
        // ジオメトリ
		ID2D1TransformedGeometry * geometry;

	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="factory">ファクトリ機能。</param>
        /// <param name="rectangle">対象矩形。</param>
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

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfTransformedGeometry() {}

	public:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
		VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
			return gcnew VisualResourceEntity2D(this, this->geometry, true);
		}
	};
}