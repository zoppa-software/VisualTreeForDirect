#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "CapStyle.h"
#include "DashStyle.h"
#include "LineJoin.h"
#include "VisualResource.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace VisualTree
{
    /// <summary>ストロークスタイルリソース。</summary>
    public ref class VisualResourceOfStrokeStyle sealed
        : public VisualResource
    {
    public:
        /// <summary>形状の輪郭を描くストロークを記述します。</summary>
        ref class StrokeStyleProperties
        {
        public:
            /// <summary>ストロークジオメトリで開いている先端形状。</summary>
            CapStyle startCap;

            /// <summary>ストロークジオメトリで開いている終端形状。</summary>
            CapStyle endCap;

            /// <summary>各ダッシュセグメントの両端の形状。</summary>
            CapStyle dashCap;

            /// <summary>セグメントの結合方法を示す値。</summary>
            LineJoin lineJoin;

            /// <summary>接合された角の接合の厚さの制限。この値は常に1.0f以上であるかのように扱われます。</summary>
            float miterLimit;

            /// <summary>ストロークにダッシュパターンがあるかどうかを指定する値。</summary>
            DashStyle dashStyle;

            /// <summary>ダッシュシーケンス内のオフセットを指定する値。</summary>
            float dashOffset;
        };

	private:
        // 描画ファクトリ
        ID2D1Factory * factory;

        // ストロークスタイル
        ID2D1StrokeStyle * strokeStyle;

        // ストローク形状
        StrokeStyleProperties ^ properties;

        // ダッシュパターン
        List<float>^ dashes;

    public:
        /// <summary>形状の輪郭を描くストロークを取得する。</summary>
        property StrokeStyleProperties ^ Properties
        {
            StrokeStyleProperties ^ get() { return this->properties; }
        }

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="factory">描画ファクトリ。</param>
        VisualResourceOfStrokeStyle(String ^ name, ID2D1Factory * factory)
            : VisualResource(name), factory(factory), strokeStyle(NULL)
        {
            this->dashes = gcnew List<float>();
            this->properties = gcnew StrokeStyleProperties();
        }

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfStrokeStyle() {}

    public:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
            if (this->factory != NULL) {
                if (this->strokeStyle == NULL) {
                    D2D1_STROKE_STYLE_PROPERTIES prop = D2D1::StrokeStyleProperties(
                        (D2D1_CAP_STYLE)this->properties->startCap,
                        (D2D1_CAP_STYLE)this->properties->endCap,
                        (D2D1_CAP_STYLE)this->properties->dashCap,
                        (D2D1_LINE_JOIN)this->properties->lineJoin,
                        this->properties->miterLimit,
                        (D2D1_DASH_STYLE)this->properties->dashStyle,
                        this->properties->dashOffset);
                    ID2D1StrokeStyle * stroke;
                    std::vector<float> dhs(this->dashes->Count);
                    for each (float v in this->dashes) {
                        dhs.push_back(v);
                    }
                    this->factory->CreateStrokeStyle(prop, (float*)dhs.data(), dhs.size(), &stroke);
                    this->strokeStyle = stroke;
                }
                return gcnew VisualResourceEntity2D(this, this->strokeStyle, true);
            }
            else {
                return nullptr;
            }
		}
    };
}
