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

    /// <summary>テキストフォーマット・リソース。</summary>
	public ref class VisualResourceOfTextFormat
		: public VisualResource
	{
	private:
        // 描画ファクトリ
        IDWriteFactory * factory;

        // フォーマット実体
        IDWriteTextFormat * format;

        // フォントファミリ名
        String ^ fontFamilyName;

        // フォントウェイト
        DWriteFontWeight fontWeight;

        // フォントスタイル
        DWriteFontStyle fontStyle;

        // フォントスタイル
        DWriteFontStretch fontStretch;

        // フォントサイズ
        float fontSize;

        // ロケール名
        String ^ localNm;

    public:
        /// <summary>フォントファミリ名を設定、取得する。</summary>
        property String ^ FontFamilyName {
            String ^ get() { return this->fontFamilyName; }
            void set(String ^ value) { this->fontFamilyName = value; }
        }

        /// <summary>フォントウェイトを設定、取得する。</summary>
        property DWriteFontWeight FontWeight {
            DWriteFontWeight get() { return this->fontWeight; }
            void set(DWriteFontWeight value) { this->fontWeight = value; }
        }

        /// <summary>フォントスタイルを設定、取得する。</summary>
        property DWriteFontStyle FontStyle {
            DWriteFontStyle get() { return this->fontStyle; }
            void set(DWriteFontStyle value) { this->fontStyle = value; }
        }

        /// <summary>フォントストレッチを設定、取得する。</summary>
        property DWriteFontStretch FontStretch {
            DWriteFontStretch get() { return this->fontStretch; }
            void set(DWriteFontStretch value) { this->fontStretch = value; }
        }

        /// <summary>フォントサイズを設定、取得する。</summary>
        property float FontSize {
            float get() { return this->fontSize; }
            void set(float value) { this->fontSize = value; }
        }

        /// <summary>ロケール名を設定、取得する。</summary>
        property String ^ LocalName {
            String ^ get() { return this->localNm; }
            void set(String ^ value) { this->localNm = value; }
        }

	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="factory">描画ファクトリ。</param>
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

        /// <summary>デストラクタ。</summary>
        ~VisualResourceOfTextFormat() {}

        /// <summary>ファイナライザ。</summary>
        !VisualResourceOfTextFormat()
        {
            this->~VisualResourceOfTextFormat();
        }

	public:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
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

