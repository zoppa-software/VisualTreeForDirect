#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
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
    /// <summary>�`��ΏۃC���X�^���X�B</summary>
    public value struct VisualRenderTarget
    {
    private:
        // �����_�����O�^�[�Q�b�g
        ID2D1DCRenderTarget * renderTarget;

    internal:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="renderTarget">�����_�����O�^�[�Q�b�g�B</param>
        VisualRenderTarget(ID2D1DCRenderTarget * renderTarget)
            : renderTarget(renderTarget)
        {}

    public:
        //-----------------------------------------------------------------------------
        // �w�i�F�N���A
        //-----------------------------------------------------------------------------
        /// <summary>�`��̈���w�肳�ꂽ�F�ɃN���A���܂��B</summary>
        /// <param name="color">�N���A����F�B</param>
        void Clear(Color color);

        /// <summary>�`��̈���w�肳�ꂽ�F�ɃN���A���܂��B</summary>
        /// <param name="red">�ԐF�����B</param>
        /// <param name="green">�ΐF�����B</param>
        /// <param name="blue">�F�����B</param>
        /// <param name="alpha">�����F�����B</param>
        void Clear(int red, int green, int blue, int alpha);

        //-----------------------------------------------------------------------------
        // �`��API
        //-----------------------------------------------------------------------------
        //this->renderTarget->DrawBitmap;
        //this->renderTarget->DrawEllipse;

        /// <summary>�w�肳�ꂽ���@�ƃX�g���[�N�őȉ~�̗֊s��`�悵�܂��B</summary>
        /// <param name="rect">�`�悷��ȉ~�̈ʒu�Ɣ��a�B</param>
        /// <param name="brush">�ȉ~�̗֊s�̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">�ȉ~�̃X�g���[�N�̑����B</param>
        void DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>�w�肳�ꂽ�W�I���g���̗֊s��`�悵�܂��B</summary>
        /// <param name="geometry">�`��W�I���g���B</param>
        /// <param name="brush">�X�g���[�N��h��Ԃ��u���V�B</param>
        /// <param name="strokeWidth">�X�g���[�N�̑����B</param>
        void DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth);

        //this->renderTarget->DrawGlyphRun;
        /// <summary>�w�肳�ꂽ�X�g���[�N �X�^�C�����g�p���āA�w�肳�ꂽ�_�̊Ԃɐ���`�悵�܂��B</summary>
        /// <param name="startPt">���̎n�_�B</param>
        /// <param name="endPt">���̏I�_�B</param>
        /// <param name="brush">���̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">���̃X�g���[�N�̑����B</param>
        void DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth);

        //this->renderTarget->DrawRectangle;
        //this->renderTarget->DrawRoundedRectangle;
        //this->renderTarget->DrawText;
        //this->renderTarget->DrawTextLayout;
        //this->renderTarget->FillRoundedRectangle;
        //this->renderTarget->FillEllipse;

        /// <summary>�w�肳�ꂽ�W�I���g���̓�����`�悵�܂��B</summary>
        /// <param name="geometry">�`��W�I���g���B</param>
        /// <param name="brush">�W�I���g��������h��Ԃ��u���V�B</param>
        void FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush);

        //this->renderTarget->FillMesh;
        //this->renderTarget->FillOpacityMask;
        //this->renderTarget->FillRectangle;

        /// <summary>�h��Ԃ��ꂽ��`��`�悵�܂��B</summary>
        /// <param name="rectangle">�Ώۂ̋�`�B</param>
        /// <param name="brush">������h��Ԃ��u���V�B</param>
        void FillRectangle(System::Drawing::Rectangle ^ rectangle, VisualResourceEntity ^ brush);

        //this->renderTarget->FillRoundedRectangle;
        //this->renderTarget->SetAntialiasMode;
    };
}

