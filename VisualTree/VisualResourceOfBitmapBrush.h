#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
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
        /// <summary>ビットマップの配置方法を指定する。</summary>
        enum class EXTEND_MODE
        {
            /// <summary>サンプルポイントをエッジにクランプすることにより、ソースのエッジを拡張します。</summary>
            EXTEND_MODE_CLAMP = 0,
    
            /// <summary>ベースタイルは変換されずに描画され、残りはベースタイルを繰り返すことで塗りつぶされます。</summary>
            EXTEND_MODE_WRAP = 1,
    
            /// <summary>折り返しと同じですが、代替タイルが反転します。ベースタイルは変形されずに描画されます。</summary>
            EXTEND_MODE_MIRROR = 2,

            /// <summary>無効値。</summary>
            EXTEND_MODE_FORCE_DWORD = -1

        };

        /// <summary>不足部の引き延ばしプロパティ。</summary>
        ref class BitmapBrushProperties
        {
        private:
            // 引き延ばし設定
            EXTEND_MODE exX, exY;

        public:
            /// <summary>横方向引き延ばし設定を設定、取得する。</summary>
            property EXTEND_MODE ExtendModeX {
                EXTEND_MODE get() { return this->exX; }
                void set(EXTEND_MODE val) { this->exX = val; }
            }

            /// <summary>縦方向引き延ばし設定を設定、取得する。</summary>
            property EXTEND_MODE ExtendModeY {
                EXTEND_MODE get() { return this->exY; }
                void set(EXTEND_MODE val) { this->exY = val; }
            }

        public:
            /// <summary>コンストラクタ。</summary>
            BitmapBrushProperties()
                : exX(EXTEND_MODE::EXTEND_MODE_WRAP), exY(EXTEND_MODE::EXTEND_MODE_WRAP)
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
                                                    (D2D1_EXTEND_MODE)this->properties->ExtendModeY),
                    &brush);
                    bitmap->Release();
                }
            }

            // ビットマップ描画ターゲットの解放
            bitmapTarget->Release();
            return gcnew VisualResourceEntity(this, brush);
        }
    };
}