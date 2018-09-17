#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <dwmapi.h>
#include "VisualRenderEventArgs.h"
#include "VisualResources.h"
#include "VisualResourceOfSolidColorBrush.h"
#include "VisualResourceOfPathGeometry.h"
#include "VisualResourceOfBitmap.h"
#include "VisualResourceOfBitmapBrush.h"
#include "VisualResourceOfLineGradientBrush.h"
#include "VisualResourceOfRadialGradientBrush.h"
#include "VisualResourceOfTextFormat.h"
#include "VisualResourceOfStrokeStyle.h"
#include "VisualResourceOfRectangleGeometry.h"
#include "VisualResourceOfTransformedGeometry.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Collections::Generic;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

	/// <summary>VisualTree描画用コントロール。</summary>
	public ref class VisualTeeControl
		: public System::Windows::Forms::UserControl
	{
    public:
        /// <summary>描画処理イベントデリゲート。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        delegate void VisualRenderEventHandler(Object ^ sender, VisualRenderEventArgs ^ e);

        /// <summary>描画リソースの初期化イベントデリゲート。</summary>
        /// <param name="sender">イベント発行元。</param>
        /// <param name="e">イベントオブジェクト。</param>
        delegate void VisualResourceEventHandler(Object ^ sender, EventArgs ^ e);

        /// <summary>描画処理を行う。</summary>
        [Category("VisualTree 設定")]
        [Description("描画処理を行う")]
        event VisualRenderEventHandler ^ VisualRenderEvent;

        /// <summary>描画リソースの初期化を行う。</summary>
        [Category("VisualTree 設定")]
        [Description("描画リソースの初期化を行う")]
        event VisualResourceEventHandler ^ VisualInitialResourceEvent;

	private:
        // Direct2Dファクトリ
		ID2D1Factory * factory;

        // DirectWriteファクトリ
		IDWriteFactory * writeFactory;

        // レンダーターゲット
		ID2D1DCRenderTarget * renderTarget;

        // リソースリスト（登録順）
		Dictionary<String ^, VisualResource ^>^ srcres;

        // リソースリスト（テーブル）
		VisualResources ^ resources;

        // 必要なデザイナー変数
		System::ComponentModel::Container ^components;

	public:
		/// <summary>コンストラクタ。</summary>
        VisualTeeControl();

	protected:
		/// <summary>デストラクタ。</summary>
        virtual ~VisualTeeControl();

        /// <summary>ファイナライザ。</summary>
        !VisualTeeControl();

    protected:
        //-------------------------------------------------------------------------
        // イベント処理
        //-------------------------------------------------------------------------
        /// <summary>ロードイベント。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnLoad(EventArgs ^ e) override;

        /// <summary>サイズチェンジイベント。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnSizeChanged(EventArgs ^ e) override;

        /// <summary>背景描画イベント。</summary>
        /// <param name="e">イベントオブジェクト。</param>
        void OnPaintBackground(PaintEventArgs ^ e) override;

        /// <summary>ウィンドウプロシージャ。</summary>
        /// <param name="m">メッセージ構造体。</param>
		virtual void WndProc(Message% m) override;

    private:
        /// <summary>コンポーネント初期化処理。</summary>
        void InitializeComponent();

        //-------------------------------------------------------------------------
        // Direct2Dリソースサイクル
        //-------------------------------------------------------------------------
        /// <summary>デバイス非依存リソースを作成する。</summary>
		HRESULT CreateDeviceIndependentResources();

        /// <summary>デバイス依存リソースを作成する。</summary>
        /// <return>実行結果。</return>
		HRESULT CreateDeviceResources();

        /// <summary>描画を開始する。</summary>
        /// <param name="ps">描画範囲を取得する。</param>
        /// <return>実行結果。</return>
		HRESULT RenderStart(const PAINTSTRUCT &ps);

        /// <summary>デバイスロスト向け、リソース解放処理。</summary>
		void DiscardDeviceResources();

	public:
        //-------------------------------------------------------------------------
        // 描画処理
        //-------------------------------------------------------------------------
        /// <summary>リソース初期化を行う。</summary>
        /// <param name="name">イベントオブジェクト。</param>
        virtual void OnInitialResource(EventArgs ^ e);

        /// <summary>描画処理を行う。</summary>
        /// <param name="name">イベントオブジェクト。</param>
        virtual void OnRander(VisualRenderEventArgs ^ e);

        /// <summary>管理しているリソースを解放する。</summary>
        void ClearResource();

        /// <summary>レンダーターゲットを再構築する。</summary>
        void Rebuild();

        /// <summary>指定名のリソースを削除する。</summary>
        /// <param name="name">削除するリソース名。</param>
        void Remove(String ^ name);

    public:
        //-------------------------------------------------------------------------
        // リソース作成
        //-------------------------------------------------------------------------
        /// <summary>ソリッドカラーブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="red">赤色成分。</param>
        /// <param name="green">緑色成分。</param>
        /// <param name="blue">青色成分。</param>
        /// <param name="alpha">透明成分。</param>
        /// <return>リソース。</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, int red, int green, int blue, int alpha);

        /// <summary>ソリッドカラーブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="color">ブラシの色。</param>
        /// <return>リソース。</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, Color color);

        /// <summary>ジオメトリを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfPathGeometry ^ CreatePathGeometry(String ^ name);

        /// <summary>ビットマップを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">元としたビットマップ。</param>
        /// <return>リソース。</return>
        VisualResourceOfBitmap ^ CreateBitmap(String ^ name, Bitmap ^ bitmap);

        /// <summary>ビットマップブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">ブラシに使用するビットマップ。</param>
        /// <return>リソース。</return>
        VisualResourceOfBitmapBrush ^ CreateBitmapBrush(String ^ name, Bitmap ^ bitmap);

        /// <summary>ライングラデーションブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfLinearGradientBrush ^ CreateLinearGradientBrush(String ^ name);

        /// <summary>放射グラデーションブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfRadialGradientBrush ^ CreateRadialGradientBrush(String ^ name);

        /// <summary>文字列書式リソースを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfTextFormat ^ CreateTextFormat(String ^ name);

        /// <summary>ストロークスタイルを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfStrokeStyle ^ CreateStrokeStyle(String ^ name);

        /// <summary>矩形ジオメトリリソースを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="rectangle">作成する矩形。</param>
        /// <return>リソース。</return>
        VisualResourceOfRectangleGeometry ^ CreateRectangleGeometry(String ^ name, RectangleF rectangle);

        /// <summary>変形ジオメトリリソースを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="pathGeometry">変形するジオメトリ。</param>
        /// <param name="matrix">変形マトリクス。</param>
        /// <return>リソース。</return>
        VisualResourceOfTransformedGeometry ^ CreateTransformedGeometry(String ^ name, VisualResourceOfPathGeometry ^ pathGeometry, Matrix matrix);
	};
}
