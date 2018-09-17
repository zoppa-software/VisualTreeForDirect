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

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>ストロークスタイルリソース。</summary>
    public ref class VisualResourceOfStrokeStyle sealed
        : public VisualResource
    {
    public:
        /// <summary>形状の輪郭を描くストロークを記述します。</summary>
        ref class StrokeStyleProperties
        {
        private:
            // ストロークジオメトリで開いている先端形状
            CapStyle startCap;

            // ストロークジオメトリで開いている終端形状
            CapStyle endCap;

            // 各ダッシュセグメントの両端の形状
            CapStyle dashCap;

            // セグメントの結合方法を示す値
            LineJoin lineJoin;

            // 接合された角の接合の厚さの制限。この値は常に1.0f以上であるかのように扱われます
            float miterLimit;

            // ストロークにダッシュパターンがあるかどうかを指定する値
            DashStyle dashStyle;

            // ダッシュシーケンス内のオフセットを指定する値
            float dashOffset;

        public:
            /// <summary>ストロークジオメトリで開いている先端形状を設定、取得する。</summary>
            property CapStyle StartCap {
                CapStyle get() { return this->startCap; }
                void set(CapStyle value) { this->startCap = value; }
            }

            /// <summary>ストロークジオメトリで開いている終端形状を設定、取得する。</summary>
            property CapStyle EndCap {
                CapStyle get() { return this->endCap; }
                void set(CapStyle value) { this->endCap = value; }
            }

            /// <summary>各ダッシュセグメントの両端の形状を設定、取得する。</summary>
            property CapStyle DashCap {
                CapStyle get() { return this->dashCap; }
                void set(CapStyle value) { this->dashCap = value; }
            }

            /// <summary>セグメントの結合方法を示す値を設定、取得する。</summary>
            property VisualTree::LineJoin LineJoin {
                VisualTree::LineJoin get() { return this->lineJoin; }
                void set(VisualTree::LineJoin value) { this->lineJoin = value; }
            }

            /// <summary>接合された角の接合の厚さの制限を設定、取得する。</summary>
            property float MiterLimit {
                float get() { return this->miterLimit; }
                void set(float value) { this->miterLimit = value; }
            }

            /// <summary>ストロークにダッシュパターンがあるかどうかを指定する値を設定、取得する。</summary>
            property VisualTree::DashStyle DashStyle {
                VisualTree::DashStyle get() { return this->dashStyle; }
                void set(VisualTree::DashStyle value) { this->dashStyle = value; }
            }

            /// <summary>ダッシュシーケンス内のオフセットを指定する値を設定、取得する。</summary>
            property float DashOffset {
                float get() { return this->dashOffset; }
                void set(float value) { this->dashOffset = value; }
            }
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
            this->properties = gcnew StrokeStyleProperties();
            this->dashes = gcnew List<float>();
        }

        /// <summary>デストラクタ。</summary>
        virtual ~VisualResourceOfStrokeStyle() {}

    public:
        /// <summary>ダッシュパターンを消去する。</summary>
        void DashesClear()
        {
            this->dashes->Clear();
        }

        /// <summary>ダッシュパターンに追加する。</summary>
        /// <param name="value">追加する値。</param>
        void DashesAdd(float value)
        {
            this->dashes->Add(value);
        }

        /// <summary>ダッシュパターンに追加する。</summary>
        /// <param name="values">追加する値リスト。</param>
        void DashesAddRange(System::Collections::Generic::IEnumerable<float>^ values)
        {
            this->dashes->AddRange(values);
        }

        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
            if (this->factory != NULL) {
                if (this->strokeStyle == NULL) {
                    D2D1_STROKE_STYLE_PROPERTIES prop = D2D1::StrokeStyleProperties(
                        (D2D1_CAP_STYLE)this->properties->StartCap,
                        (D2D1_CAP_STYLE)this->properties->EndCap,
                        (D2D1_CAP_STYLE)this->properties->DashCap,
                        (D2D1_LINE_JOIN)this->properties->LineJoin,
                        this->properties->MiterLimit,
                        (D2D1_DASH_STYLE)this->properties->DashStyle,
                        this->properties->DashOffset);

                    ID2D1StrokeStyle * stroke;
                    std::vector<float> dhs(this->dashes->Count);
                    for each (float v in this->dashes) {
                        dhs.push_back(v);
                    }
                    this->factory->CreateStrokeStyle(prop, (float*)dhs.data(), (UINT32)dhs.size(), &stroke);
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
