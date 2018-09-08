#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "GammaParameter.h"
#include "ExtendModeParameter.h"
#include "VisualResource.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace VisualTree
{
    /// <summary>ライングラデーションブラシインスタンス。</summary>
	public ref class VisualResourceOfLinearGradientBrush
        : public VisualResource
    {
    public:
        /// <summary>グラデーション境界の位置と色を格納する。</summary>
        ref class GradientStop
        {
        public:
            // 色
            Color color;

            // 位置
            float position;

        public:
            /// <summary>コンストラクタ。</summary>
            /// <param name="edgeColor">色。</param>
            /// <param name="position">位置。</param>
            GradientStop(Color edgeColor, float position)
                : color(edgeColor), position(position)
            {}
        };

        /// <summary>グラデーション勾配軸の開始点と終了点を格納。</summary>
        ref class LinearGradientBrushProperties
        {
        private:
            // グラデーション軸の開始点
            PointF  startPoint;

            // グラデーション軸の終了点
            PointF  endPoint;

        public:
            /// <summary>グラデーション軸の開始点を設定、取得する。</summary>
            property PointF StartPoint {
                PointF get() { return this->startPoint; }
                void set(PointF pos) { this->startPoint = pos; }
            }

            /// <summary>グラデーション軸の終了点を設定、取得する。</summary>
            property PointF EndPoint {
                PointF get() { return this->endPoint; }
                void set(PointF pos) { this->endPoint = pos; }
            }
        };

	private:
        // グラデーション境界の位置と色リスト
        List<GradientStop^>^ gradientStops;

        // ガンマ色空間
        GammaParameter gamma;

        // 色の引き延ばし設定
        ExtendModeParameter extendMode;

        // グラデーションの原点のオフセット、グラデーション楕円のサイズと位置
        LinearGradientBrushProperties ^ properties;

    public:
        /// <summary>ガンマ色空間設定を設定、取得する。</summary>
        property GammaParameter Gamma {
            GammaParameter get() { return this->gamma; }
            void set(GammaParameter gamma) { this->gamma = gamma; }
        }

        /// <summary>色の引き延ばし設定を設定、取得する。</summary>
        property ExtendModeParameter ExtendMode {
            ExtendModeParameter get() { return this->extendMode; }
            void set(ExtendModeParameter mode) { this->extendMode = mode; }
        }

        /// <summary>グラデーション勾配軸の開始点と終了点を設定、取得する。</summary>
        property LinearGradientBrushProperties ^ Propertes {
            LinearGradientBrushProperties ^ get() { return this->properties; }
        }

	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
		VisualResourceOfLinearGradientBrush(String ^ name)
			: VisualResource(name), gamma(GammaParameter::GAMMA_2_2), extendMode(ExtendModeParameter::EXTEND_MODE_CLAMP) {
            this->gradientStops = gcnew List<GradientStop^>();
            this->properties = gcnew LinearGradientBrushProperties();
        }

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfLinearGradientBrush() {}

	public:
        /// <summary>グラデーション境界の位置と色を全て消去する。</summary>
        void Clear()
        {
            this->gradientStops->Clear();
        }

        /// <summary>グラデーション境界の位置と色を追加する。</summary>
        void AddGradientStop(Color edgeColor, float position)
        {
            this->gradientStops->Add(gcnew GradientStop(edgeColor, position));
        }

        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            // グラデーション境界の位置と色をリスト化する
            std::vector<D2D1_GRADIENT_STOP> pos;
            if (this->gradientStops->Count > 0) {
                for each (GradientStop^ stp in this->gradientStops) {
                    D2D1_GRADIENT_STOP st;
                    st.color = D2D1::ColorF(stp->color.R / 255.0f,
                        stp->color.G / 255.0f,
                        stp->color.B / 255.0f,
                        stp->color.A / 255.0f);
                    st.position = stp->position;
                    pos.push_back(st);
                }
            }
            else {
                D2D1_GRADIENT_STOP st;
                st.color = D2D1::ColorF(1, 1, 1, 1);
                st.position = 1;
                pos.push_back(st);
            }
            
            // グラデーション設定を行う
            ID2D1GradientStopCollection * gradientStops = NULL;
            ID2D1LinearGradientBrush * brush = NULL;
            HRESULT hr = renderTarget->CreateGradientStopCollection(pos.data(),
                                                                    pos.size(),
                                                                    (D2D1_GAMMA)this->gamma,
                                                                    (D2D1_EXTEND_MODE)this->extendMode,
                                                                    &gradientStops);
            if (SUCCEEDED(hr)) {
                D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES props = D2D1::LinearGradientBrushProperties(
                    D2D1::Point2F(this->properties->StartPoint.X, this->properties->StartPoint.Y),
                    D2D1::Point2F(this->properties->EndPoint.X, this->properties->EndPoint.Y));
                renderTarget->CreateLinearGradientBrush(props, gradientStops, &brush);
                gradientStops->Release();
            }
            return gcnew VisualResourceEntity2D(this, brush);
        }
    };
}