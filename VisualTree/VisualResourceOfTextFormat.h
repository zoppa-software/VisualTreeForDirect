#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vcclr.h>
#include "DWriteFontWeight.h"
#include "DWriteFontStyle.h"
#include "DWriteFontStretch.h"
#include "VisualResource.h"
#include "VisualResourceEntity.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Globalization;

    /// <summary>�e�L�X�g�t�H�[�}�b�g�E���\�[�X�B</summary>
	public ref class VisualResourceOfTextFormat
		: public VisualResource
	{
	private:
        // �`��t�@�N�g��
        IDWriteFactory * factory;

        // �t�H�[�}�b�g����
        IDWriteTextFormat * format;

        // �t�H���g�t�@�~����
        String ^ fontFamilyName;

        // �t�H���g�E�F�C�g
        DWriteFontWeight fontWeight;

        // �t�H���g�X�^�C��
        DWriteFontStyle fontStyle;

        // �t�H���g�X�^�C��
        DWriteFontStretch fontStretch;

        // �t�H���g�T�C�Y
        float fontSize;

        // ���P�[����
        String ^ localNm;

    public:
        /// <summary>�t�H���g�t�@�~������ݒ�A�擾����B</summary>
        property String ^ FontFamilyName {
            String ^ get() { return this->fontFamilyName; }
            void set(String ^ value) { this->fontFamilyName = value; }
        }

        /// <summary>�t�H���g�E�F�C�g��ݒ�A�擾����B</summary>
        property DWriteFontWeight FontWeight {
            DWriteFontWeight get() { return this->fontWeight; }
            void set(DWriteFontWeight value) { this->fontWeight = value; }
        }

        /// <summary>�t�H���g�X�^�C����ݒ�A�擾����B</summary>
        property DWriteFontStyle FontStyle {
            DWriteFontStyle get() { return this->fontStyle; }
            void set(DWriteFontStyle value) { this->fontStyle = value; }
        }

        /// <summary>�t�H���g�X�g���b�`��ݒ�A�擾����B</summary>
        property DWriteFontStretch FontStretch {
            DWriteFontStretch get() { return this->fontStretch; }
            void set(DWriteFontStretch value) { this->fontStretch = value; }
        }

        /// <summary>�t�H���g�T�C�Y��ݒ�A�擾����B</summary>
        property float FontSize {
            float get() { return this->fontSize; }
            void set(float value) { this->fontSize = value; }
        }

        /// <summary>���P�[������ݒ�A�擾����B</summary>
        property String ^ LocalName {
            String ^ get() { return this->localNm; }
            void set(String ^ value) { this->localNm = value; }
        }

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="factory">�`��t�@�N�g���B</param>
        VisualResourceOfTextFormat(String ^ name, IDWriteFactory * factory)
			: VisualResource(name),
              factory(factory),
              format(NULL),
              fontFamilyName(String::Empty),
              fontWeight(DWriteFontWeight::DWRITE_FONT_WEIGHT_NORMAL),
              fontStretch(DWriteFontStretch::DWRITE_FONT_STRETCH_NORMAL),
              fontSize(10.5f)
        {
            this->localNm = CultureInfo::CurrentCulture->Name;
        }

        /// <summary>�f�X�g���N�^�B</summary>
        ~VisualResourceOfTextFormat() {}

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualResourceOfTextFormat()
        {
            this->~VisualResourceOfTextFormat();
        }

	public:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            if (this->factory != NULL) {
                if (this->format == NULL) {
                    IDWriteTextFormat * format;
                    const wchar_t * familyPtr = NULL;
                    if (this->fontFamilyName != nullptr) {
                        pin_ptr<const wchar_t> familyName = PtrToStringChars(this->fontFamilyName);
                        familyPtr = familyName;
                    }
                    pin_ptr<const wchar_t> local = this->localNm != nullptr ?
                        PtrToStringChars(this->localNm) : (WCHAR*)NULL;

                    this->factory->CreateTextFormat(familyPtr,
                                                    NULL,
                                                    (DWRITE_FONT_WEIGHT)this->fontWeight,
                                                    (DWRITE_FONT_STYLE)this->fontStyle,
                                                    (DWRITE_FONT_STRETCH)this->fontStretch,
                                                    this->fontSize,
                                                    local,
                                                    &format);
                    this->format = format;
                }
                return gcnew VisualResourceEntityWrite(this, this->format, true);
            }
            else {
                return nullptr;
            }
        }
	};
}

