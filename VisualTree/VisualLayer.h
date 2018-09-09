#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <limits>
#include "AntialiasMode.h"
#include "LayerOptions.h"
#include "Matrix.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>描画レイヤー。</summary>
    public ref class VisualLayer sealed
        : IDisposable
    {
    public:
        /// <summary>レイヤー リソースのコンテンツの境界、マスク情報、不透明度の設定、およびその他のオプションを格納します。</summary>
        ref class LayerParameters
        {
        public:
            RectangleF contentBounds;

            VisualResourceEntity ^ geometricMask;

            AntialiasMode maskAntialiasMode;

            Matrix maskTransform;

            float opacity;

            VisualResourceEntity ^ opacityBrush;

            LayerOptions layerOptions;

        public:
            LayerParameters()
                : contentBounds(RectangleF(FLT_MIN, FLT_MIN, FLT_MAX, FLT_MAX)),
                  geometricMask(nullptr),
                  maskAntialiasMode(AntialiasMode::ANTIALIAS_MODE_PER_PRIMITIVE),
                  maskTransform(Matrix::Identity()),
                  opacity(1),
                  opacityBrush(nullptr),
                  layerOptions(LayerOptions::D2D1_LAYER_OPTIONS_NONE)
            {}
        };

    private:
        // レイヤー参照
        ID2D1Layer * layer;

        // レイヤーパラメータ
        LayerParameters ^ parameters;

    public:
        /// <summary>レイヤーパラメータを取得する。</summary>
        property LayerParameters ^ Parameters
        {
            LayerParameters ^ get() {
                return this->parameters;
            }
        }

    internal:
        /// <summary>コンストラクタ。</summary>
        VisualLayer()
            : layer(NULL)
        {
            this->parameters = gcnew LayerParameters();
        }

        /// <summary>コンストラクタ。</summary>
        /// <param name="layer">対象レイヤー。</param>
        VisualLayer(ID2D1Layer * layer)
            : layer(layer)
        {
            this->parameters = gcnew LayerParameters();
        }

    public:
        /// <summary>デストラクタ。</summary>
        ~VisualLayer()
        {
            if (this->layer != NULL) {
                this->layer->Release();
                this->layer = NULL;
            }
        }

        /// <summary>ファイナライザ。</summary>
        !VisualLayer()
        {
            this->~VisualLayer();
        }

    internal:
        /// <summary>対象レイヤーのポインタを取得する。</summary>
        /// <return>対象レイヤー。</return>
        ID2D1Layer * GetInstance() { return this->layer; }
    };
}

