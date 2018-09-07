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

// ���\�[�X����}�N��
#define SAFE_RELEASE(release)	{ \
	if (release != NULL) {		\
		release->Release();		\
		release = NULL;			\
	}							\
}

namespace VisualTree {

	/// <summary>VisualTree�`��p�R���g���[���B</summary>
	public ref class VisualTeeControl
		: public System::Windows::Forms::UserControl
	{
    public:
        delegate void VisualRenderEventHandler(Object ^ sender, VisualRenderEventArgs ^ e);
        delegate void VisualResourceEventHandler(Object ^ sender, EventArgs ^ e);

        [Category("VisualTree �ݒ�")]
        [Description("�`�揈�����L�q����")]
        event VisualRenderEventHandler ^ VisualRenderEvent;

        [Category("VisualTree �ݒ�")]
        [Description("�`�惊�\�[�X�̏�������������������")]
        event VisualResourceEventHandler ^ VisualInitialResourceEvent;

	private:
		ID2D1Factory *m_pD2DFactory;

        // �����_�[�^�[�Q�b�g
		ID2D1DCRenderTarget * renderTarget;

		List<VisualResource ^>^ srcres;
		VisualResources ^ resources;

        /// <summary>�K�v�ȃf�U�C�i�[�ϐ��B</summary>
		System::ComponentModel::Container ^components;

	public:
		/// <summary>�R���X�g���N�^�B</summary>
		VisualTeeControl()
			: m_pD2DFactory(NULL), renderTarget(NULL)
		{
			InitializeComponent();

			CreateDeviceIndependentResources();
			this->srcres = gcnew List<VisualResource^>();
			this->resources = gcnew VisualResources();
		}

	protected:
		/// <summary>�g�p���̃��\�[�X�����ׂăN���[���A�b�v����B</summary>
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
        // Direct2D���\�[�X�T�C�N��
        //-------------------------------------------------------------------------
		HRESULT CreateDeviceIndependentResources();
		HRESULT CreateDeviceResources();

        /// <summary>�`����J�n����B</summary>
        /// <param name="ps">�`��͈͂��擾����B</param>
		HRESULT RenderStart(const PAINTSTRUCT &ps);

        /// <summary>�f�o�C�X���X�g�����A���\�[�X��������B</summary>
		void DiscardDeviceResources();

	public:
        //-------------------------------------------------------------------------
        // �`�揈��
        //-------------------------------------------------------------------------
        /// <summary>���\�[�X���������s���B</summary>
        /// <param name="name">�C�x���g�I�u�W�F�N�g�B</param>
        virtual void OnInitialResource(EventArgs ^ e);

        /// <summary>�`�揈�����s���B</summary>
        /// <param name="name">�C�x���g�I�u�W�F�N�g�B</param>
        virtual void OnRander(VisualRenderEventArgs ^ e);

        /// <summary>�Ǘ����Ă��郊�\�[�X���������B</summary>
        void ClearResource();

    public:
        //-------------------------------------------------------------------------
        // ���\�[�X�쐬
        //-------------------------------------------------------------------------
        /// <summary>�\���b�h�J���[�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="red">�ԐF�����B</param>
        /// <param name="green">�ΐF�����B</param>
        /// <param name="blue">�F�����B</param>
        /// <param name="alpha">���������B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, int red, int green, int blue, int alpha);

        /// <summary>�\���b�h�J���[�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="color">�u���V�̐F�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfSolidColorBrush ^ CreateSolidColorBrush(String ^ name, Color color);

        /// <summary>�W�I���g�����쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfPathGeometry ^ CreatePathGeometry(String ^ name);

        /// <summary>�r�b�g�}�b�v�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�u���V�Ɏg�p����r�b�g�}�b�v�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfBitmapBrush ^ CreateBitmapBrush(String ^ name, Bitmap ^ bitmap);

        /// <summary>���C���O���f�[�V�����u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfRadialGradientBrush ^ VisualTeeControl::CreateRadialGradientBrush(String ^ name);
	};
}
