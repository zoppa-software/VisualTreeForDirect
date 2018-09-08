#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vcclr.h>  
#include "VisualResource.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>テキストフォーマット・リソース。</summary>
	public ref class VisualResourceOfTextFormat
		: public VisualResource
	{
    public:
        enum class DWRITE_FONT_WEIGHT
        {
            /// <summary>
            /// Predefined font weight : Thin (100).
            /// </summary>
            DWRITE_FONT_WEIGHT_THIN = 100,

            /// <summary>
            /// Predefined font weight : Extra-light (200).
            /// </summary>
            DWRITE_FONT_WEIGHT_EXTRA_LIGHT = 200,

            /// <summary>
            /// Predefined font weight : Ultra-light (200).
            /// </summary>
            DWRITE_FONT_WEIGHT_ULTRA_LIGHT = 200,

            /// <summary>
            /// Predefined font weight : Light (300).
            /// </summary>
            DWRITE_FONT_WEIGHT_LIGHT = 300,

            /// <summary>
            /// Predefined font weight : Semi-light (350).
            /// </summary>
            DWRITE_FONT_WEIGHT_SEMI_LIGHT = 350,

            /// <summary>
            /// Predefined font weight : Normal (400).
            /// </summary>
            DWRITE_FONT_WEIGHT_NORMAL = 400,

            /// <summary>
            /// Predefined font weight : Regular (400).
            /// </summary>
            DWRITE_FONT_WEIGHT_REGULAR = 400,

            /// <summary>
            /// Predefined font weight : Medium (500).
            /// </summary>
            DWRITE_FONT_WEIGHT_MEDIUM = 500,

            /// <summary>
            /// Predefined font weight : Demi-bold (600).
            /// </summary>
            DWRITE_FONT_WEIGHT_DEMI_BOLD = 600,

            /// <summary>
            /// Predefined font weight : Semi-bold (600).
            /// </summary>
            DWRITE_FONT_WEIGHT_SEMI_BOLD = 600,

            /// <summary>
            /// Predefined font weight : Bold (700).
            /// </summary>
            DWRITE_FONT_WEIGHT_BOLD = 700,

            /// <summary>
            /// Predefined font weight : Extra-bold (800).
            /// </summary>
            DWRITE_FONT_WEIGHT_EXTRA_BOLD = 800,

            /// <summary>
            /// Predefined font weight : Ultra-bold (800).
            /// </summary>
            DWRITE_FONT_WEIGHT_ULTRA_BOLD = 800,

            /// <summary>
            /// Predefined font weight : Black (900).
            /// </summary>
            DWRITE_FONT_WEIGHT_BLACK = 900,

            /// <summary>
            /// Predefined font weight : Heavy (900).
            /// </summary>
            DWRITE_FONT_WEIGHT_HEAVY = 900,

            /// <summary>
            /// Predefined font weight : Extra-black (950).
            /// </summary>
            DWRITE_FONT_WEIGHT_EXTRA_BLACK = 950,

            /// <summary>
            /// Predefined font weight : Ultra-black (950).
            /// </summary>
            DWRITE_FONT_WEIGHT_ULTRA_BLACK = 950
        };

        enum class DWRITE_FONT_STYLE
        {
            /// <summary>
            /// Font slope style : Normal.
            /// </summary>
            DWRITE_FONT_STYLE_NORMAL,

            /// <summary>
            /// Font slope style : Oblique.
            /// </summary>
            DWRITE_FONT_STYLE_OBLIQUE,

            /// <summary>
            /// Font slope style : Italic.
            /// </summary>
            DWRITE_FONT_STYLE_ITALIC

        };

        enum class DWRITE_FONT_STRETCH
        {
            /// <summary>
            /// Predefined font stretch : Not known (0).
            /// </summary>
            DWRITE_FONT_STRETCH_UNDEFINED = 0,

            /// <summary>
            /// Predefined font stretch : Ultra-condensed (1).
            /// </summary>
            DWRITE_FONT_STRETCH_ULTRA_CONDENSED = 1,

            /// <summary>
            /// Predefined font stretch : Extra-condensed (2).
            /// </summary>
            DWRITE_FONT_STRETCH_EXTRA_CONDENSED = 2,

            /// <summary>
            /// Predefined font stretch : Condensed (3).
            /// </summary>
            DWRITE_FONT_STRETCH_CONDENSED = 3,

            /// <summary>
            /// Predefined font stretch : Semi-condensed (4).
            /// </summary>
            DWRITE_FONT_STRETCH_SEMI_CONDENSED = 4,

            /// <summary>
            /// Predefined font stretch : Normal (5).
            /// </summary>
            DWRITE_FONT_STRETCH_NORMAL = 5,

            /// <summary>
            /// Predefined font stretch : Medium (5).
            /// </summary>
            DWRITE_FONT_STRETCH_MEDIUM = 5,

            /// <summary>
            /// Predefined font stretch : Semi-expanded (6).
            /// </summary>
            DWRITE_FONT_STRETCH_SEMI_EXPANDED = 6,

            /// <summary>
            /// Predefined font stretch : Expanded (7).
            /// </summary>
            DWRITE_FONT_STRETCH_EXPANDED = 7,

            /// <summary>
            /// Predefined font stretch : Extra-expanded (8).
            /// </summary>
            DWRITE_FONT_STRETCH_EXTRA_EXPANDED = 8,

            /// <summary>
            /// Predefined font stretch : Ultra-expanded (9).
            /// </summary>
            DWRITE_FONT_STRETCH_ULTRA_EXPANDED = 9
        };

	private:
        // 描画ファクトリ
        IDWriteFactory *    factory;

        // フォーマット実体
        IDWriteTextFormat * format;

        // フォントファミリ名
        String ^ fontFamilyName;

    public:
        property String ^ FontFamilyName {
            String ^ get() { return this->fontFamilyName; }
            void set(String ^ value) { this->fontFamilyName = value; }
        }

	public:
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="factory">描画ファクトリ。</param>
        VisualResourceOfTextFormat(String ^ name, IDWriteFactory * factory)
			: VisualResource(name), factory(factory), format(NULL)
        {
            this->fontFamilyName = String::Empty;
        }

        /// <summary>デストラクタ。</summary>
		~VisualResourceOfTextFormat() {}

	public:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            if (this->factory != NULL && this->format == NULL) {
                IDWriteTextFormat * format;
                pin_ptr<const wchar_t> familyName = this->fontFamilyName != nullptr ? PtrToStringChars(this->fontFamilyName) : (WCHAR*)NULL;
                this->factory->CreateTextFormat(familyName, NULL, DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 10.5f, L"en-us", &format);
                //D2D1_COLOR_F color = D2D1::ColorF(this->red, this->green, this->blue, this->alpha);
                //renderTarget->CreateSolidColorBrush(color, &brush);
                this->format = format;
                return gcnew VisualResourceEntityWrite(this, format);
            }
            else {
                return nullptr;
            }
        }
	};
}

