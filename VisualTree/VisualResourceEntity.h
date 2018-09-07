#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree {

    ref class VisualResource;

    /// <summary>リソースクラス・描画実体。</summary>
    public ref class VisualResourceEntity
    {
    protected:
        // 元となったリソース参照
        VisualResource ^    resource;

        // Direct2Dのインスタンス
        ID2D1Resource *		instance;

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        VisualResourceEntity(VisualResource ^ resource, ID2D1Resource * instance) {
            this->resource = resource;
            this->instance = instance;
        }

    public:
        /// <summary>リソースを解放する。</summary>
        void SafeRelease() {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        ID2D1Resource * GetInstance() {
            return this->instance;
        }

        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        virtual void SetColor(System::Drawing::Color color) {}
    };

    /// <summary>リソースクラス・描画実体（ソリッドブラシ用）</summary>
    ref class VisualResourceEntityOfSolidBrush sealed
        : public VisualResourceEntity
    {
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        VisualResourceEntityOfSolidBrush(VisualResource ^ parent, ID2D1Resource * instance)
            : VisualResourceEntity(parent, instance) {
        }

    public:
        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        void SetColor(System::Drawing::Color color) override;
    };
}