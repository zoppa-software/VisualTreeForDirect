#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "ExtendModeParameter.h"
#include "BitmapInterpolationMode.h"
#include "VisualResource.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

namespace VisualTree
{
    /// <summary>ビットマップブラシリソース。</summary>
    public ref class VisualResourceOfBitmapBrush sealed
        : public VisualResource
    {
    public:
        /// <summary>不足部の引き延ばしプロパティ。</summary>
        ref class BitmapBrushProperties
        {
        private:
            // 引き延ばし設定
            ExtendModeParameter exX, exY;

            // 補間モード
            BitmapInterpolationMode mode;

        public:
            /// <summary>横方向引き延ばし設定を設定、取得する。</summary>
            property ExtendModeParameter ExtendModeX {
                ExtendModeParameter get() { return this->exX; }
                void set(ExtendModeParameter val) { this->exX = val; }
            }

            /// <summary>縦方向引き延ばし設定を設定、取得する。</summary>
            property ExtendModeParameter ExtendModeY {
                ExtendModeParameter get() { return this->exY; }
                void set(ExtendModeParameter val) { this->exY = val; }
            }

            /// <summary>補間モードを設定、取得する。</summary>
            property BitmapInterpolationMode InterpolationMode {
                BitmapInterpolationMode get() { return this->mode; }
                void set(BitmapInterpolationMode val) { this->mode = val; }
            }

        public:
            /// <summary>コンストラクタ。</summary>
            BitmapBrushProperties()
                : exX(ExtendModeParameter::EXTEND_MODE_WRAP),
                  exY(ExtendModeParameter::EXTEND_MODE_WRAP),
                  mode(BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
            {}
        };

    private:
        // 描画ビットマップ
        Bitmap ^    bitmap;

        // 配置モードプロパティ
        BitmapBrushProperties ^ properties;

    public:
        /// <summary>ビットマップを配置するための不足部の引き延ばしプロパティを取得する。</summary>
        property BitmapBrushProperties ^ Properties
        {
            BitmapBrushProperties ^ get() { return this->properties; }
        }

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">描画ビットマップ。</param>
		VisualResourceOfBitmapBrush(String ^ name, Bitmap ^ bitmap)
			: VisualResource(name), bitmap(bitmap)
		{
            this->properties = gcnew BitmapBrushProperties();
        }

        /// <summary>デストラクタ。</summary>
		virtual ~VisualResourceOfBitmapBrush()
		{
            if (this->bitmap != nullptr) {
                delete this->bitmap;
                this->bitmap = nullptr;
            }
        }

    public:
        /// <summary>描画するビットマップを設定、取得する。</summary>
        property Bitmap ^ Source
        {
            Bitmap ^ get() { return this->bitmap; }
            void set(Bitmap ^ bit) { this->bitmap = bit; }
        }

    public:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            // ビットマップ描画ターゲットの作成
            ID2D1BitmapRenderTarget * bitmapTarget = NULL;
            HRESULT hr = renderTarget->CreateCompatibleRenderTarget(
                D2D1::SizeF((float)this->bitmap->Width, (float)this->bitmap->Height),
                &bitmapTarget
            );

            ID2D1BitmapBrush * brush;
            if (SUCCEEDED(hr)) {
                // 描画するビットマップを取得
                ID2D1Bitmap * bitmap = NULL;
                hr = bitmapTarget->GetBitmap(&bitmap);

                if (SUCCEEDED(hr)) {
                    // 描画ビットマップからビットマップ情報を取得し、コピーする
                    BitmapData ^ bmpData = this->bitmap->LockBits(System::Drawing::Rectangle(0, 0, this->bitmap->Width, this->bitmap->Height),
                                                                  ImageLockMode::ReadWrite,
                                                                  PixelFormat::Format32bppArgb);
                    D2D1_RECT_U rec = D2D1::RectU(0, 0, this->bitmap->Width, this->bitmap->Height);
                    bitmap->CopyFromMemory(&rec, (void*)bmpData->Scan0, bmpData->Stride);
                    this->bitmap->UnlockBits(bmpData);
                    
                    // ビットマップブラシを作成する
		            renderTarget->CreateBitmapBrush(bitmap, 
                        D2D1::BitmapBrushProperties((D2D1_EXTEND_MODE)this->properties->ExtendModeX,
                                                    (D2D1_EXTEND_MODE)this->properties->ExtendModeY,
                                                    (D2D1_BITMAP_INTERPOLATION_MODE)this->properties->InterpolationMode),
                    &brush);
                    bitmap->Release();
                }
            }

            // ビットマップ描画ターゲットの解放
            bitmapTarget->Release();
            return gcnew VisualResourceEntity2D(this, brush);
        }
    };
}