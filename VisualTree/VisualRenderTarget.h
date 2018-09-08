#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Ellipse.h"
#include "VisualResources.h"
#include "VisualResourceEntity.h"
//#include "VisualResourceOfSolidColorBrush.h"
//#include "VisualResourceOfPathGeometry.h"

using namespace System;
using namespace System::Drawing;
//using namespace System::ComponentModel;
//using namespace System::Collections;
//using namespace System::Collections::Generic;
//using namespace System::Windows::Forms;
//using namespace System::Data;
//using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>描画対象インスタンス。</summary>
    public value struct VisualRenderTarget
    {
    private:
        // レンダリングターゲット
        ID2D1DCRenderTarget * renderTarget;

    internal:
        /// <summary>コンストラクタ。</summary>
        /// <param name="renderTarget">レンダリングターゲット。</param>
        VisualRenderTarget(ID2D1DCRenderTarget * renderTarget)
            : renderTarget(renderTarget)
        {}

    public:
        //-----------------------------------------------------------------------------
        // 座標変換
        //-----------------------------------------------------------------------------
        /// <summary>座標系を平衡移動させる。</summary>
        void SetTransform();

        /// <summary>座標系を平衡移動させる。</summary>
        /// <param name="offsetX">X移動量。</param>
        /// <param name="offsetY">Y移動量。</param>
        void SetTransform(int offsetX, int offsetY);

        //-----------------------------------------------------------------------------
        // 背景色クリア
        //-----------------------------------------------------------------------------
        /// <summary>描画領域を指定された色にクリアします。</summary>
        /// <param name="color">クリアする色。</param>
        void Clear(Color color);

        /// <summary>描画領域を指定された色にクリアします。</summary>
        /// <param name="red">赤色成分。</param>
        /// <param name="green">緑色成分。</param>
        /// <param name="blue">青色成分。</param>
        /// <param name="alpha">等価色成分。</param>
        void Clear(int red, int green, int blue, int alpha);

        //-----------------------------------------------------------------------------
        // 描画API
        //-----------------------------------------------------------------------------
        //this->renderTarget->DrawBitmap;

        /// <summary>指定された寸法とストロークで楕円の輪郭を描画します。</summary>
        /// <param name="rect">描画する楕円の位置と半径。</param>
        /// <param name="brush">楕円の輪郭の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">楕円のストロークの太さ。</param>
        void DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>指定された寸法とストロークで楕円の輪郭を描画します。</summary>
        /// <param name="ellipse">楕円領域。</param>
        /// <param name="brush">楕円の輪郭の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">楕円のストロークの太さ。</param>
        void DrawEllipse(Ellipse ellipse, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>指定されたジオメトリの輪郭を描画します。</summary>
        /// <param name="geometry">描画ジオメトリ。</param>
        /// <param name="brush">ストロークを塗りつぶすブラシ。</param>
        /// <param name="strokeWidth">ストロークの太さ。</param>
        void DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth);

        //this->renderTarget->DrawGlyphRun;
        /// <summary>指定されたストローク スタイルを使用して、指定された点の間に線を描画します。</summary>
        /// <param name="startPt">線の始点。</param>
        /// <param name="endPt">線の終点。</param>
        /// <param name="brush">線の描画に使用するブラシ。</param>
        /// <param name="strokeWidth">線のストロークの太さ。</param>
        void DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>矩形を描画します。</summary>
        /// <param name="rectangle">対象の矩形。</param>
        /// <param name="brush">線のブラシ。</param>
        void DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush);

        /// <summary>矩形を描画します。</summary>
        /// <param name="rectangle">対象の矩形。</param>
        /// <param name="brush">線のブラシ。</param>
        /// <param name="strokeWidth">線のストロークの太さ。</param>
        void DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>書式情報を使用して、指定された文字列を描画します。</summary>
        /// <param name="text">描画文字列。</param>
        /// <param name="format">書式情報。</param>
        /// <param name="rect">文字列が描画される領域のサイズと位置。</param>
        /// <param name="brush">描画に使用するブラシ。</param>
        void DrawText(String ^ text, VisualResourceEntity ^ format, RectangleF rect, VisualResourceEntity ^ brush);

        //this->renderTarget->DrawTextLayout;
        //this->renderTarget->FillRoundedRectangle;

        /// <summary>指定された楕円領域の内部を描画します。</summary>
        /// <param name="ellipse">楕円領域。</param>
        /// <param name="brush">楕円内部を塗りつぶすブラシ。</param>
        void FillEllipse(Ellipse ellipse, VisualResourceEntity ^ brush);

        /// <summary>指定されたジオメトリの内部を描画します。</summary>
        /// <param name="geometry">描画ジオメトリ。</param>
        /// <param name="brush">ジオメトリ内部を塗りつぶすブラシ。</param>
        void FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush);

        //this->renderTarget->FillMesh;
        //this->renderTarget->FillOpacityMask;
        //this->renderTarget->FillRectangle;

        /// <summary>塗りつぶされた矩形を描画します。</summary>
        /// <param name="rectangle">対象の矩形。</param>
        /// <param name="brush">内部を塗りつぶすブラシ。</param>
        void FillRectangle(RectangleF rectangle, VisualResourceEntity ^ brush);

        //this->renderTarget->FillRoundedRectangle;
        //this->renderTarget->SetAntialiasMode;
    };
}

