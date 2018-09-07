#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualRenderEventArgs.h"
#include "VisualResources.h"
#include "VisualResourceOfSolidColorBrush.h"
#include "VisualResourceOfPathGeometry.h"
#include "VisualResourceOfBitmapBrush.h"
#include "VisualResourceOfRadialGradientBrush.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// リソース解放マクロ
#define SAFE_RELEASE(release)	{ \
	if (release != NULL) {		\
		release->Release();		\
		release = NULL;			\
	}							\
}

namespace VisualTree {

	/// <summary>VisualTree描画用コントロール。</summary>
	public ref class VisualTeeControl
		: public System::Windows::Forms::UserControl
	{
    public:
        delegate void VisualRenderEventHandler(Object ^ sender, VisualRenderEventArgs ^ e);
        delegate void VisualResourceEventHandler(Object ^ sender, EventArgs ^ e);

        [Category("VisualTree 設定")]
        [Description("描画処理を記述する")]
        event VisualRenderEventHandler ^ VisualRenderEvent;

        [Category("VisualTree 設定")]
        [Description("描画リソースの初期化処理を実装する")]
        event VisualResourceEventHandler ^ VisualInitialResourceEvent;

	private:
		ID2D1Factory *m_pD2DFactory;

        // レンダーターゲット
		ID2D1DCRenderTarget * renderTarget;

		List<VisualResource ^>^ srcres;
		VisualResources ^ resources;

        /// <summary>必要なデザイナー変数。</summary>
		System::ComponentModel::Container ^components;

	public:
		/// <summary>コンストラクタ。</summary>
		VisualTeeControl()
			: m_pD2DFactory(NULL), renderTarget(NULL)
		{
			InitializeComponent();

			CreateDeviceIndependentResources();
			this->srcres = gcnew List<VisualResource^>();
			this->resources = gcnew VisualResources();
		}

	protected:
		/// <summary>使用中のリソースをすべてクリーンアップする。</summary>
		~VisualTeeControl() {
			if (components) {
				delete components;
			}
			SAFE_RELEASE(m_pD2DFactory);
			this->DiscardDeviceResources();
		}

    protected:
        void OnLoad(EventArgs ^ e) override
        {
            this->OnInitialResource(e);
        }

		virtual void WndProc(Message% m) override;

    private:

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		}
#pragma endregion

        //-------------------------------------------------------------------------
        // Direct2Dリソースサイクル
        //-------------------------------------------------------------------------
		HRESULT CreateDeviceIndependentResources();
		HRESULT CreateDeviceResources();

        /// <summary>描画を開始する。</summary>
        /// <param name="ps">描画範囲を取得する。</param>
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

        /// <summary>ビットマップブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="bitmap">ブラシに使用するビットマップ。</param>
        /// <return>リソース。</return>
        VisualResourceOfBitmapBrush ^ CreateBitmapBrush(String ^ name, Bitmap ^ bitmap);

        /// <summary>ライングラデーションブラシを作成する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        VisualResourceOfRadialGradientBrush ^ VisualTeeControl::CreateRadialGradientBrush(String ^ name);
	};
}
