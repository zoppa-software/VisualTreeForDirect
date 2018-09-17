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

	/// <summary>VisualTree�`��p�R���g���[���B</summary>
	public ref class VisualTeeControl
		: public System::Windows::Forms::UserControl
	{
    public:
        /// <summary>�`�揈���C�x���g�f���Q�[�g�B</summary>
        /// <param name="sender">�C�x���g���s���B</param>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        delegate void VisualRenderEventHandler(Object ^ sender, VisualRenderEventArgs ^ e);

        /// <summary>�`�惊�\�[�X�̏������C�x���g�f���Q�[�g�B</summary>
        /// <param name="sender">�C�x���g���s���B</param>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        delegate void VisualResourceEventHandler(Object ^ sender, EventArgs ^ e);

        /// <summary>�`�揈�����s���B</summary>
        [Category("VisualTree �ݒ�")]
        [Description("�`�揈�����s��")]
        event VisualRenderEventHandler ^ VisualRenderEvent;

        /// <summary>�`�惊�\�[�X�̏��������s���B</summary>
        [Category("VisualTree �ݒ�")]
        [Description("�`�惊�\�[�X�̏��������s��")]
        event VisualResourceEventHandler ^ VisualInitialResourceEvent;

	private:
        // Direct2D�t�@�N�g��
		ID2D1Factory * factory;

        // DirectWrite�t�@�N�g��
		IDWriteFactory * writeFactory;

        // �����_�[�^�[�Q�b�g
		ID2D1DCRenderTarget * renderTarget;

        // ���\�[�X���X�g�i�o�^���j
		Dictionary<String ^, VisualResource ^>^ srcres;

        // ���\�[�X���X�g�i�e�[�u���j
		VisualResources ^ resources;

        // �K�v�ȃf�U�C�i�[�ϐ�
		System::ComponentModel::Container ^components;

	public:
		/// <summary>�R���X�g���N�^�B</summary>
        VisualTeeControl();

	protected:
		/// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualTeeControl();

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualTeeControl();

    protected:
        //-------------------------------------------------------------------------
        // �C�x���g����
        //-------------------------------------------------------------------------
        /// <summary>���[�h�C�x���g�B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnLoad(EventArgs ^ e) override;

        /// <summary>�T�C�Y�`�F���W�C�x���g�B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnSizeChanged(EventArgs ^ e) override;

        /// <summary>�w�i�`��C�x���g�B</summary>
        /// <param name="e">�C�x���g�I�u�W�F�N�g�B</param>
        void OnPaintBackground(PaintEventArgs ^ e) override;

        /// <summary>�E�B���h�E�v���V�[�W���B</summary>
        /// <param name="m">���b�Z�[�W�\���́B</param>
		virtual void WndProc(Message% m) override;

    private:
        /// <summary>�R���|�[�l���g�����������B</summary>
        void InitializeComponent();

        //-------------------------------------------------------------------------
        // Direct2D���\�[�X�T�C�N��
        //-------------------------------------------------------------------------
        /// <summary>�f�o�C�X��ˑ����\�[�X���쐬����B</summary>
		HRESULT CreateDeviceIndependentResources();

        /// <summary>�f�o�C�X�ˑ����\�[�X���쐬����B</summary>
        /// <return>���s���ʁB</return>
		HRESULT CreateDeviceResources();

        /// <summary>�`����J�n����B</summary>
        /// <param name="ps">�`��͈͂��擾����B</param>
        /// <return>���s���ʁB</return>
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

        /// <summary>�����_�[�^�[�Q�b�g���č\�z����B</summary>
        void Rebuild();

        /// <summary>�w�薼�̃��\�[�X���폜����B</summary>
        /// <param name="name">�폜���郊�\�[�X���B</param>
        void Remove(String ^ name);

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

        /// <summary>�r�b�g�}�b�v���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">���Ƃ����r�b�g�}�b�v�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfBitmap ^ CreateBitmap(String ^ name, Bitmap ^ bitmap);

        /// <summary>�r�b�g�}�b�v�u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="bitmap">�u���V�Ɏg�p����r�b�g�}�b�v�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfBitmapBrush ^ CreateBitmapBrush(String ^ name, Bitmap ^ bitmap);

        /// <summary>���C���O���f�[�V�����u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfLinearGradientBrush ^ CreateLinearGradientBrush(String ^ name);

        /// <summary>���˃O���f�[�V�����u���V���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfRadialGradientBrush ^ CreateRadialGradientBrush(String ^ name);

        /// <summary>�����񏑎����\�[�X���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfTextFormat ^ CreateTextFormat(String ^ name);

        /// <summary>�X�g���[�N�X�^�C�����쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfStrokeStyle ^ CreateStrokeStyle(String ^ name);

        /// <summary>��`�W�I���g�����\�[�X���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="rectangle">�쐬�����`�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfRectangleGeometry ^ CreateRectangleGeometry(String ^ name, RectangleF rectangle);

        /// <summary>�ό`�W�I���g�����\�[�X���쐬����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="pathGeometry">�ό`����W�I���g���B</param>
        /// <param name="matrix">�ό`�}�g���N�X�B</param>
        /// <return>���\�[�X�B</return>
        VisualResourceOfTransformedGeometry ^ CreateTransformedGeometry(String ^ name, VisualResourceOfPathGeometry ^ pathGeometry, Matrix matrix);
	};
}
