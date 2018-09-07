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
        this->OnRander(gcnew VisualRenderEventArgs(VisualRenderTarget(this->renderTarget), this->resources));

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
    // �\���b�h�J���[�u���V
    VisualResourceOfSolidColorBrush ^ VisualTeeControl::CreateSolidColorBrush(String ^ name, int red, int green, int blue, int alpha)
    {
        VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, red, green, blue, alpha);
        this->srcres->Add(res);
        return res;
    }

    /// <summary>�\���b�h�J���[�u���V���쐬����B</summary>
    /// <param name="name">���\�[�X���B</param>
    /// <param name="color">�u���V�̐F�B</param>
    /// <return>���\�[�X�B</return>
    VisualResourceOfSolidColorBrush ^ VisualTeeControl::CreateSolidColorBrush(String ^ name, Color color)
    {
        VisualResourceOfSolidColorBrush ^ res = gcnew VisualResourceOfSolidColorBrush(name, color.R, color.G, color.B, color.A);
        this->srcres->Add(res);
        return res;
    }

    // �W�I���g��
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
