#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"
#include "Matrix.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    ref class VisualResource;

    /// <summary>リソースクラス・描画実体。</summary>
    public ref class VisualResourceEntity abstract
    {
    protected:
        // 元となったリソース参照
        VisualResource ^    resource;

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        VisualResourceEntity(VisualResource ^ resource)
            : resource(resource) {}

    public:
        /// <summary>リソースを解放する。</summary>
        virtual void SafeRelease() abstract;

        /// <summary>リソースを解放する。</summary>
        virtual void ForceRelease() abstract;

        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        virtual ID2D1Resource * GetInstance() { return NULL; }

        /// <summary>コムインターフェイスのインスタンスを取得する。</summary>
        virtual IUnknown * GetWriteInstance() { return NULL; }

        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        virtual void SetColor(System::Drawing::Color color) abstract;

        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        virtual void SetOpacity(int opacity) abstract;

        /// <summary>座標系を平衡移動させる。</summary>
        virtual void SetTransform() abstract;

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        virtual void SetTransform(float offsetX, float offsetY) abstract;

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="matrix">移動量マトリックス。</param>
        virtual void SetTransform(Matrix matrix) abstract;
    };

    /// <summary>リソースクラス・描画実体。</summary>
    ref class VisualResourceEntity2D
        : public VisualResourceEntity
    {
    protected:
        // Direct2Dのインスタンス
        ID2D1Resource *		instance;

        // 長いライフサイクルならば真
        bool isLongLife;

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        VisualResourceEntity2D(VisualResource ^ resource, ID2D1Resource * instance)
            : VisualResourceEntity(resource), instance(instance), isLongLife(false) {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        /// <param name="isLongLife">長いライフサイクルならば真。</param>
        VisualResourceEntity2D(VisualResource ^ resource, ID2D1Resource * instance, bool isLongLife)
            : VisualResourceEntity(resource), instance(instance), isLongLife(isLongLife) {}

    public:
        /// <summary>リソースを解放する。</summary>
        void SafeRelease() override
        {
            if (this->instance != NULL && this->isLongLife) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>リソースを解放する。</summary>
        void ForceRelease() override
        {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>Direct2Dのインスタンスを取得する。</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->instance;
        }

        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        void SetColor(System::Drawing::Color color) override {}

        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        void SetOpacity(int opacity) override {}

        /// <summary>座標系を平衡移動させる。</summary>
        void SetTransform() override {}

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        void SetTransform(float offsetX, float offsetY) override {}

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="matrix">移動量マトリックス。</param>
        void SetTransform(Matrix matrix) override {}
    };

    /// <summary>リソースクラス・描画実体（ブラシ用）</summary>
    ref class VisualResourceEntityOfBrush sealed
        : public VisualResourceEntity2D
    {
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        VisualResourceEntityOfBrush(VisualResource ^ parent, ID2D1Resource * instance)
            : VisualResourceEntity2D(parent, instance) {}

    public:
        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        void SetColor(System::Drawing::Color color) override {}

        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        void SetOpacity(int opacity) override;

        /// <summary>座標系を平衡移動させる。</summary>
        void SetTransform() override;

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        void SetTransform(float offsetX, float offsetY) override;

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="matrix">移動量マトリックス。</param>
        void SetTransform(Matrix matrix) override;
    };

    /// <summary>リソースクラス・描画実体（ソリッドブラシ用）</summary>
    ref class VisualResourceEntityOfSolidBrush sealed
        : public VisualResourceEntity2D
    {
    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        VisualResourceEntityOfSolidBrush(VisualResource ^ parent, ID2D1Resource * instance)
            : VisualResourceEntity2D(parent, instance) {}

    public:
        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        void SetColor(System::Drawing::Color color) override;

        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        void SetOpacity(int opacity) override;

        /// <summary>座標系を平衡移動させる。</summary>
        void SetTransform() override;

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        void SetTransform(float offsetX, float offsetY) override;

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="matrix">移動量マトリックス。</param>
        void SetTransform(Matrix matrix) override;
    };

    /// <summary>リソースクラス・描画実体（COM）</summary>
    ref class VisualResourceEntityWrite
        : public VisualResourceEntity
    {
    protected:
        // コムインターフェイスのインスタンス
        IUnknown *		instance;

        // 長いライフサイクルならば真
        bool isLongLife;

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        VisualResourceEntityWrite(VisualResource ^ resource, IUnknown * instance)
            : VisualResourceEntity(resource), instance(instance), isLongLife(false) {}

        /// <summary>コンストラクタ。</summary>
        /// <param name="resource">元のリソース。</param>
        /// <param name="instance">Direct2Dのインスタンス。</param>
        /// <param name="isLongLife">長いライフサイクルならば真。</param>
        VisualResourceEntityWrite(VisualResource ^ resource, IUnknown * instance, bool isLongLife)
            : VisualResourceEntity(resource), instance(instance), isLongLife(isLongLife) {}

    public:
        /// <summary>リソースを解放する。</summary>
        void SafeRelease() override
        {
            if (this->instance != NULL && this->isLongLife) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>リソースを解放する。</summary>
        void ForceRelease() override
        {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>コムインターフェイスのインスタンスを取得する。</summary>
        IUnknown * GetWriteInstance() override
        {
            return this->instance;
        }

        /// <summary>色設定を変更する。</summary>
        /// <param name="color">変更する色。</param>
        void SetColor(System::Drawing::Color color) override {}

        /// <summary>透明度を変更する。</summary>
        /// <param name="opacity">透明度（0 ～ 255）。</param>
        void SetOpacity(int opacity) override {}

        /// <summary>座標系を平衡移動させる。</summary>
        void SetTransform() override {}

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        void SetTransform(float offsetX, float offsetY) override {}

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="matrix">移動量マトリックス。</param>
        void SetTransform(Matrix matrix) override {}
    };
}