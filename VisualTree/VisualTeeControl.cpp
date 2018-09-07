#include "stdafx.h"
#include "VisualRenderTarget.h"
#include "VisualTeeControl.h"

namespace VisualTree {

	HRESULT VisualTeeControl::CreateDeviceIndependentResources()
	{
		ID2D1Factory* factory;
		HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
		m_pD2DFactory = factory;
		return res;
	}

	HRESULT VisualTeeControl::CreateDeviceResources()
	{
		HRESULT hr = S_OK;

		if (this->renderTarget == NULL && m_pD2DFactory != NULL)
		{
			// Create a DC render target.
			D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
				D2D1_RENDER_TARGET_TYPE_DEFAULT,
				D2D1::PixelFormat(
					DXGI_FORMAT_B8G8R8A8_UNORM,
					D2D1_ALPHA_MODE_IGNORE),
				0,
				0,
				D2D1_RENDER_TARGET_USAGE_NONE,
				D2D1_FEATURE_LEVEL_DEFAULT
				);

			ID2D1DCRenderTarget * dCRT;
			hr = m_pD2DFactory->CreateDCRenderTarget(&props, &dCRT);
			this->renderTarget = dCRT;
			if (!SUCCEEDED(hr)) { return hr; }

			for each (VisualResource ^ res in this->srcres) {
				this->resources->Add(res->Name, res->ChangeEntity(this->renderTarget));
			}
		}

		return hr;
	}

	void VisualTeeControl::WndProc(Message% message)
	{
        switch (message.Msg)
        {
        case WM_PAINT:
        case WM_DISPLAYCHANGE:
        {
            PAINTSTRUCT ps;
            BeginPaint((HWND)message.HWnd.ToPointer(), &ps);
            this->RenderStart(ps);
            EndPaint((HWND)message.HWnd.ToPointer(), &ps);
        }
        break;

        default:
            Control::WndProc(message);
            break;
        }
	}

    // 描画処理を実行する
	HRESULT VisualTeeControl::RenderStart(const PAINTSTRUCT &ps)
	{
		HRESULT hr;
		RECT rc;

		// 描画範囲を取得する
		GetClientRect((HWND)this->Handle.ToPointer(), &rc);

		// 描画ターゲットを取得する
		hr = CreateDeviceResources();
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // デバイスコンテキストにレンダーターゲットを紐付ける
		hr = this->renderTarget->BindDC(ps.hdc, &rc);
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // 描画開始を通知する
		this->renderTarget->BeginDraw();

        // 座標系を初期化する
		this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        // 描画を行う
        this->OnRander(gcnew VisualRenderEventArgs(VisualRenderTarget(this->renderTarget), this->resources));

        // 描画終了を通知する
		hr = this->renderTarget->EndDraw();

    LAST:
		if (hr == D2DERR_RECREATE_TARGET) {
			hr = S_OK;
			DiscardDeviceResources();
		}
		return hr;
	}

    // デバイスロスト向け、リソース解放処理
	void VisualTeeControl::DiscardDeviceResources()
	{
		SAFE_RELEASE(this->renderTarget);
		for each(VisualResourceEntity ^ ins in this->resources->Values) {
			ins->SafeRelease();
		}
	}

    //-------------------------------------------------------------------------
    // 描画処理
    //-------------------------------------------------------------------------
    // リソース初期化
    void VisualTeeControl::OnInitialResource(EventArgs ^ e)
    {
        this->VisualInitialResourceEvent(this, e);
    }

    // 描画処理実装
    void VisualTeeControl::OnRander(VisualRenderEventArgs ^ e)
    {
        this->VisualRenderEvent(this, e);
    }

    // 管理しているリソースを解放する
    void VisualTeeControl::ClearResource() {
        this->srcres->Clear();
        for each(VisualResourceEntity ^ ins in this->resources->Values) {
            ins->SafeRelease();
        }
        this->resources->Clear();
    }

    //-------------------------------------------------------------------------
    // リソース作成
    //-------------------------------------------------------------------------
    // ソリッドカラーブラシ
    VisualResourceOfSolidColorBrush ^ VisualTeeControl::CreateSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
    {
        VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, red, green, blue, alpha);
        this->srcres->Add(res);
        return res;
    }

    /// <summary>ソリッドカラーブラシを作成する。</summary>
    /// <param name="name">リソース名。</param>
    /// <param name="color">ブラシの色。</param>
    /// <return>リソース。</return>
    VisualResourceOfSolidColorBrush ^ VisualTeeControl::CreateSolidColorBrush(String ^ name, Color color)
    {
        VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, color.R, color.G, color.B, color.A);
        this->srcres->Add(res);
        return res;
    }

    // ジオメトリ
    VisualResourceOfPathGeometry ^ VisualTeeControl::CreatePathGeometry(String ^ name)
    {
        VisualResourceOfPathGeometry ^ res = gcnew VisualResourceOfPathGeometry(name, this->m_pD2DFactory);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfBitmapBrush ^ VisualTeeControl::CreateBitmapBrush(String ^ name, Bitmap ^ bitmap)
    {
        VisualResourceOfBitmapBrush ^ res = gcnew VisualResourceOfBitmapBrush(name, bitmap);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfRadialGradientBrush ^ VisualTeeControl::CreateRadialGradientBrush(String ^ name)
    {
        VisualResourceOfRadialGradientBrush ^ res = gcnew VisualResourceOfRadialGradientBrush(name);
        this->srcres->Add(res);
        return res;
    }
}
