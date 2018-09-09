#include "stdafx.h"
#include "VisualRenderTarget.h"
#include "VisualTeeControl.h"

namespace VisualTree {

	HRESULT VisualTeeControl::CreateDeviceIndependentResources()
	{
        HRESULT res;

        // Direct2D�t�@�N�g�����쐬
        ID2D1Factory * factory;
        res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
        if (FAILED(res)) {
            return res;
        }
		this->factory = factory;

        // DirectWrite�t�@�N�g�����쐬
        IDWriteFactory * writeFactory;
        res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&writeFactory);
        if (FAILED(res)) {
            return res;
        }
        this->writeFactory = writeFactory;

		return res;
	}

	HRESULT VisualTeeControl::CreateDeviceResources()
	{
		HRESULT hr = S_OK;

		if (this->renderTarget == NULL && factory != NULL)
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
			hr = factory->CreateDCRenderTarget(&props, &dCRT);
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

    // �`�揈�������s����
	HRESULT VisualTeeControl::RenderStart(const PAINTSTRUCT &ps)
	{
		HRESULT hr;
		RECT rc;

		// �`��͈͂��擾����
		GetClientRect((HWND)this->Handle.ToPointer(), &rc);

		// �`��^�[�Q�b�g���擾����
		hr = CreateDeviceResources();
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // �f�o�C�X�R���e�L�X�g�Ƀ����_�[�^�[�Q�b�g��R�t����
		hr = this->renderTarget->BindDC(ps.hdc, &rc);
        if (FAILED(hr) || this->renderTarget == NULL) {
            goto LAST;
        }

        // �`��J�n��ʒm����
		this->renderTarget->BeginDraw();

        // ���W�n������������
		this->renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        // �`����s��
        try {
            this->OnRander(gcnew VisualRenderEventArgs(VisualRenderTarget(this->renderTarget), this->resources));
        }
        catch (NullReferenceException ^) {
            // ��|�C���^�Q�Ƃ𖳎�
        }

        // �`��I����ʒm����
		hr = this->renderTarget->EndDraw();

    LAST:
		if (hr == D2DERR_RECREATE_TARGET) {
			hr = S_OK;
			DiscardDeviceResources();
		}
		return hr;
	}

    // �f�o�C�X���X�g�����A���\�[�X�������
	void VisualTeeControl::DiscardDeviceResources()
	{
		SAFE_RELEASE(this->renderTarget);
		for each(VisualResourceEntity ^ ins in this->resources->Values) {
			ins->SafeRelease();
		}
	}

    //-------------------------------------------------------------------------
    // �`�揈��
    //-------------------------------------------------------------------------
    // ���\�[�X������
    void VisualTeeControl::OnInitialResource(EventArgs ^ e)
    {
        this->VisualInitialResourceEvent(this, e);
    }

    // �`�揈������
    void VisualTeeControl::OnRander(VisualRenderEventArgs ^ e)
    {
        this->VisualRenderEvent(this, e);
    }

    // �Ǘ����Ă��郊�\�[�X���������
    void VisualTeeControl::ClearResource() {
        this->srcres->Clear();
        for each(VisualResourceEntity ^ ins in this->resources->Values) {
            ins->SafeRelease();
        }
        this->resources->Clear();
    }

    //-------------------------------------------------------------------------
    // ���\�[�X�쐬
    //-------------------------------------------------------------------------
    VisualResourceOfSolidColorBrush ^ VisualTeeControl::CreateSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
    {
        VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, red, green, blue, alpha);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfSolidColorBrush ^ VisualTeeControl::CreateSolidColorBrush(String ^ name, Color color)
    {
        VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, color.R, color.G, color.B, color.A);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfPathGeometry ^ VisualTeeControl::CreatePathGeometry(String ^ name)
    {
        VisualResourceOfPathGeometry ^ res = gcnew VisualResourceOfPathGeometry(name, this->factory);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfBitmap ^ VisualTeeControl::CreateBitmap(String ^ name, Bitmap ^ bitmap)
    {
        VisualResourceOfBitmap ^ res = gcnew VisualResourceOfBitmap(name, bitmap);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfBitmapBrush ^ VisualTeeControl::CreateBitmapBrush(String ^ name, Bitmap ^ bitmap)
    {
        VisualResourceOfBitmapBrush ^ res = gcnew VisualResourceOfBitmapBrush(name, bitmap);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfLinearGradientBrush ^ VisualTeeControl::CreateLinearGradientBrush(String ^ name)
    {
        VisualResourceOfLinearGradientBrush ^ res = gcnew VisualResourceOfLinearGradientBrush(name);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfRadialGradientBrush ^ VisualTeeControl::CreateRadialGradientBrush(String ^ name)
    {
        VisualResourceOfRadialGradientBrush ^ res = gcnew VisualResourceOfRadialGradientBrush(name);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfTextFormat ^ VisualTeeControl::CreateTextFormat(String ^ name)
    {
        VisualResourceOfTextFormat ^ res = gcnew VisualResourceOfTextFormat(name, this->writeFactory);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfStrokeStyle ^ VisualTeeControl::CreateStrokeStyle(String ^ name)
    {
        VisualResourceOfStrokeStyle ^ res = gcnew VisualResourceOfStrokeStyle(name, this->factory);
        this->srcres->Add(res);
        return res;
    }

    VisualResourceOfRectangleGeometry ^ VisualTeeControl::CreateRectangleGeometry(String ^ name, RectangleF rectangle)
    {
        VisualResourceOfRectangleGeometry ^ res = gcnew VisualResourceOfRectangleGeometry(name, this->factory, rectangle);
        this->srcres->Add(res);
        return res;
    }
}
