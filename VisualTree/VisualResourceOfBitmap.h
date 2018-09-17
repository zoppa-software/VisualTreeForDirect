#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "ExtendModeParameter.h"
#include "BitmapInterpolationMode.h"
#include "VisualResource.h"
#include "VisualResourceEntity.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Drawing::Imaging;

    /// <summary>ビットマップリソース。</summary>
    public ref class VisualResourceOfBitmap sealed
        : public VisualResource
    {
    private:
        // 描画ビットマップ
        Bitmap ^    bitmap;

        // Direct2Dビットマップ
        ID2D1Bitmap * d2bitmap;

    public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">描画ビットマップ。</param>
		VisualResourceOfBitmap(String ^ name, Bitmap ^ bitmap)
			: VisualResource(name), bitmap(bitmap), d2bitmap(NULL)
		{}

        /// <summary>デストラクタ。</summary>
		virtual ~VisualResourceOfBitmap()
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
            if (this->d2bitmap == NULL) {
                // ビットマップ描画ターゲットの作成
                ID2D1BitmapRenderTarget * bitmapTarget = NULL;
                HRESULT hr = renderTarget->CreateCompatibleRenderTarget(
                    D2D1::SizeF((float)this->bitmap->Width, (float)this->bitmap->Height),
                    &bitmapTarget
                );

                ID2D1Bitmap * bitmap = NULL;
                if (SUCCEEDED(hr)) {
                    // 描画するビットマップを取得       
                    hr = bitmapTarget->GetBitmap(&bitmap);

                    if (SUCCEEDED(hr)) {
                        // 描画ビットマップからビットマップ情報を取得し、コピーする
                        BitmapData ^ bmpData = this->bitmap->LockBits(System::Drawing::Rectangle(0, 0, this->bitmap->Width, this->bitmap->Height),
                            ImageLockMode::ReadWrite,
                            PixelFormat::Format32bppArgb);
                        D2D1_RECT_U rec = D2D1::RectU(0, 0, this->bitmap->Width, this->bitmap->Height);
                        bitmap->CopyFromMemory(&rec, (void*)bmpData->Scan0, bmpData->Stride);
                        this->bitmap->UnlockBits(bmpData);
                    }
                }

                // ビットマップ描画ターゲットの解放
                bitmapTarget->Release();
                this->d2bitmap = bitmap;
            }
            return gcnew VisualResourceEntity2D(this, this->d2bitmap, true);
        }
    };
}