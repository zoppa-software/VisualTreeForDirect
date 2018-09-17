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

    /// <summary>�r�b�g�}�b�v���\�[�X�B</summary>
    public ref class VisualResourceOfBitmap sealed
        : public VisualResource
    {
    private:
        // �`��r�b�g�}�b�v
        Bitmap ^    bitmap;

        // Direct2D�r�b�g�}�b�v
        ID2D1Bitmap * d2bitmap;

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�`��r�b�g�}�b�v�B</param>
		VisualResourceOfBitmap(String ^ name, Bitmap ^ bitmap)
			: VisualResource(name), bitmap(bitmap), d2bitmap(NULL)
		{}

        /// <summary>�f�X�g���N�^�B</summary>
		virtual ~VisualResourceOfBitmap()
		{
            if (this->bitmap != nullptr) {
                delete this->bitmap;
                this->bitmap = nullptr;
            }
        }

    public:
        /// <summary>�`�悷��r�b�g�}�b�v��ݒ�A�擾����B</summary>
        property Bitmap ^ Source
        {
            Bitmap ^ get() { return this->bitmap; }
            void set(Bitmap ^ bit) { this->bitmap = bit; }
        }

    public:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            if (this->d2bitmap == NULL) {
                // �r�b�g�}�b�v�`��^�[�Q�b�g�̍쐬
                ID2D1BitmapRenderTarget * bitmapTarget = NULL;
                HRESULT hr = renderTarget->CreateCompatibleRenderTarget(
                    D2D1::SizeF((float)this->bitmap->Width, (float)this->bitmap->Height),
                    &bitmapTarget
                );

                ID2D1Bitmap * bitmap = NULL;
                if (SUCCEEDED(hr)) {
                    // �`�悷��r�b�g�}�b�v���擾       
                    hr = bitmapTarget->GetBitmap(&bitmap);

                    if (SUCCEEDED(hr)) {
                        // �`��r�b�g�}�b�v����r�b�g�}�b�v�����擾���A�R�s�[����
                        BitmapData ^ bmpData = this->bitmap->LockBits(System::Drawing::Rectangle(0, 0, this->bitmap->Width, this->bitmap->Height),
                            ImageLockMode::ReadWrite,
                            PixelFormat::Format32bppArgb);
                        D2D1_RECT_U rec = D2D1::RectU(0, 0, this->bitmap->Width, this->bitmap->Height);
                        bitmap->CopyFromMemory(&rec, (void*)bmpData->Scan0, bmpData->Stride);
                        this->bitmap->UnlockBits(bmpData);
                    }
                }

                // �r�b�g�}�b�v�`��^�[�Q�b�g�̉��
                bitmapTarget->Release();
                this->d2bitmap = bitmap;
            }
            return gcnew VisualResourceEntity2D(this, this->d2bitmap, true);
        }
    };
}