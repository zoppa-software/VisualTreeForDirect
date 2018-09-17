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

    /// <summary>�r�b�g�}�b�v�u���V���\�[�X�B</summary>
    public ref class VisualResourceOfBitmapBrush sealed
        : public VisualResource
    {
    public:
        /// <summary>�s�����̈������΂��v���p�e�B�B</summary>
        ref class BitmapBrushProperties
        {
        private:
            // �������΂��ݒ�
            ExtendModeParameter exX, exY;

            // ��ԃ��[�h
            BitmapInterpolationMode mode;

        public:
            /// <summary>�������������΂��ݒ��ݒ�A�擾����B</summary>
            property ExtendModeParameter ExtendModeX {
                ExtendModeParameter get() { return this->exX; }
                void set(ExtendModeParameter val) { this->exX = val; }
            }

            /// <summary>�c�����������΂��ݒ��ݒ�A�擾����B</summary>
            property ExtendModeParameter ExtendModeY {
                ExtendModeParameter get() { return this->exY; }
                void set(ExtendModeParameter val) { this->exY = val; }
            }

            /// <summary>��ԃ��[�h��ݒ�A�擾����B</summary>
            property BitmapInterpolationMode InterpolationMode {
                BitmapInterpolationMode get() { return this->mode; }
                void set(BitmapInterpolationMode val) { this->mode = val; }
            }

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            BitmapBrushProperties()
                : exX(ExtendModeParameter::EXTEND_MODE_WRAP),
                  exY(ExtendModeParameter::EXTEND_MODE_WRAP),
                  mode(BitmapInterpolationMode::BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR)
            {}
        };

    private:
        // �`��r�b�g�}�b�v
        Bitmap ^    bitmap;

        // �z�u���[�h�v���p�e�B
        BitmapBrushProperties ^ properties;

    public:
        /// <summary>�`�悷��r�b�g�}�b�v��ݒ�A�擾����B</summary>
        property Bitmap ^ Source
        {
            Bitmap ^ get() { return this->bitmap; }
            void set(Bitmap ^ bit) { this->bitmap = bit; }
        }

        /// <summary>�r�b�g�}�b�v��z�u���邽�߂̕s�����̈������΂��v���p�e�B���擾����B</summary>
        property BitmapBrushProperties ^ Properties
        {
            BitmapBrushProperties ^ get() { return this->properties; }
        }

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�`��r�b�g�}�b�v�B</param>
		VisualResourceOfBitmapBrush(String ^ name, Bitmap ^ bitmap)
			: VisualResource(name), bitmap(bitmap)
		{
            this->properties = gcnew BitmapBrushProperties();
        }

        /// <summary>�f�X�g���N�^�B</summary>
		virtual ~VisualResourceOfBitmapBrush()
		{
            if (this->bitmap != nullptr) {
                delete this->bitmap;
                this->bitmap = nullptr;
            }
        }

    public:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            // �r�b�g�}�b�v�`��^�[�Q�b�g�̍쐬
            ID2D1BitmapRenderTarget * bitmapTarget = NULL;
            HRESULT hr = renderTarget->CreateCompatibleRenderTarget(
                D2D1::SizeF((float)this->bitmap->Width, (float)this->bitmap->Height),
                &bitmapTarget
            );

            ID2D1BitmapBrush * brush;
            if (SUCCEEDED(hr)) {
                // �`�悷��r�b�g�}�b�v���擾
                ID2D1Bitmap * bitmap = NULL;
                hr = bitmapTarget->GetBitmap(&bitmap);

                if (SUCCEEDED(hr)) {
                    // �`��r�b�g�}�b�v����r�b�g�}�b�v�����擾���A�R�s�[����
                    BitmapData ^ bmpData = this->bitmap->LockBits(System::Drawing::Rectangle(0, 0, this->bitmap->Width, this->bitmap->Height),
                                                                  ImageLockMode::ReadWrite,
                                                                  PixelFormat::Format32bppArgb);
                    D2D1_RECT_U rec = D2D1::RectU(0, 0, this->bitmap->Width, this->bitmap->Height);
                    bitmap->CopyFromMemory(&rec, (void*)bmpData->Scan0, bmpData->Stride);
                    this->bitmap->UnlockBits(bmpData);
                    
                    // �r�b�g�}�b�v�u���V���쐬����
		            renderTarget->CreateBitmapBrush(bitmap, 
                        D2D1::BitmapBrushProperties((D2D1_EXTEND_MODE)this->properties->ExtendModeX,
                                                    (D2D1_EXTEND_MODE)this->properties->ExtendModeY,
                                                    (D2D1_BITMAP_INTERPOLATION_MODE)this->properties->InterpolationMode),
                    &brush);
                    bitmap->Release();
                }
            }

            // �r�b�g�}�b�v�`��^�[�Q�b�g�̉��
            bitmapTarget->Release();
            return gcnew VisualResourceEntityOfBrush(this, brush);
        }
    };
}