#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Ellipse.h"
#include "AntialiasMode.h"
#include "BitmapInterpolationMode.h"
#include "OpacityMaskContent.h"
#include "VisualResources.h"
#include "VisualResourceEntity.h"
#include "VisualLayer.h"

using namespace System;
using namespace System::Drawing;

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
        // ���W�ϊ�
        //-----------------------------------------------------------------------------
        /// <summary>���W�n�𕽍t�ړ�������B</summary>
        void SetTransform();

        /// <summary>���W�n�𕽍t�ړ�������B</summary>
        /// <param name="offsetX">X�ړ��ʁB</param>
        /// <param name="offsetY">Y�ړ��ʁB</param>
        void SetTransform(int offsetX, int offsetY);

        /// <summary>���W�n�𕽍t�ړ�������B</summary>
        /// <param name="matrix">�ړ��ʃ}�g���b�N�X�B</param>
        void SetTransform(Matrix matrix);

        /// <summary>�㑱�̂��ׂĂ̕`�摀�삪�N���b�v�����l�p�`���w�肵�܂��B</summary>
        /// <param name="rect">�N���b�s���O�̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="mode">�A���`�G�C���A�V���O���[�h�B</param>
        void PushAxisAlignedClip(RectangleF rect, AntialiasMode mode);

        /// <summary>�����_�[�^�[�Q�b�g���玲�ɕ��s�ȍŌ�̃N���b�v���폜���܂��B</summary>
        void PopAxisAlignedClip();

        //-----------------------------------------------------------------------------
        // �����ݒ�
        //-----------------------------------------------------------------------------
        /// <summary>�A���`�G�C���A�X��ݒ肷��B</summary>
        /// <param name="mode">�A���`�G�C���A�X���[�h�B</param>
        void SetAntialiasMode(AntialiasMode mode);

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
        // ���C���[����
        //-----------------------------------------------------------------------------
        /// <summary>���C���[���쐬����B</summary>
        /// <return>�쐬���ꂽ���C���[�B</return>
        VisualLayer ^ CreateLayer();

        /// <summary>���C���[���쐬����B</summary>
        /// <param name="name">���C���[�T�C�Y�B</param>
        /// <return>�쐬���ꂽ���C���[�B</return>
        VisualLayer ^ CreateLayer(SizeF size);

        /// <summary>PopLayer ���Ăяo�����܂Ń����_�[�^�[�Q�b�g�Ō㑱�̕`�摀������ׂĎ󂯎�邱�Ƃ��ł���悤�ɁA�w�肳�ꂽ���C���[�����̃����_�[ �^�[�Q�b�g�ɒǉ����܂��B</summary>
        /// <param name="layer">�ݒ肷�郌�C���[�B</param>
        void PushLayer(VisualLayer ^ layer);

        /// <summary>PushLayer�̍Ō�̌Ăяo���Ŏw�肳�ꂽ���C���[�ɕ`�摀�삪���_�C���N�g����Ȃ��悤�ɂ��܂��B</summary>
        void PopLayer();

        //-----------------------------------------------------------------------------
        // �`��API
        //-----------------------------------------------------------------------------
        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity, BitmapInterpolationMode interpolationMode);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, float opacity);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, BitmapInterpolationMode interpolationMode);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity, BitmapInterpolationMode interpolationMode);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, BitmapInterpolationMode interpolationMode, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="destinationRectangle">�����_�[ �^�[�Q�b�g�̍��W��Ԃɂ�����A�r�b�g�}�b�v���`�悳���̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, RectangleF destinationRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="opacity">�r�b�g�}�b�v�ɓK�p����s�����x�̒l���w�肷�� 0.0f �` 1.0f �̒l�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, float opacity);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="interpolationMode">�`�摀��ɂ���ăr�b�g�}�b�v�̃T�C�Y�����܂��͉�]���s����Ƃ��Ɏg�p�����ԃ��[�h�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap, BitmapInterpolationMode interpolationMode);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        /// <param name="sourceRectangle">�r�b�g�}�b�v�̍��W��Ԃɂ�����A�r�b�g�}�b�v���̕`�悷��̈�̃T�C�Y�ƈʒu (�f�o�C�X��ˑ��̃s�N�Z���P��)�B</param>
        void DrawBitmapSource(VisualResourceEntity ^ bitmap, RectangleF sourceRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v���A�w�肳�ꂽ�l�p�`�̃T�C�Y�Ɋg��܂��͏k��������ɕ`�悵�܂��B</summary>
        /// <param name="bitmap">�����_�����O����r�b�g�}�b�v�B</param>
        void DrawBitmap(VisualResourceEntity ^ bitmap);

        /// <summary>�w�肳�ꂽ���@�ƃX�g���[�N�őȉ~�̗֊s��`�悵�܂��B</summary>
        /// <param name="rect">�`�悷��ȉ~�̈ʒu�Ɣ��a�B</param>
        /// <param name="brush">�ȉ~�̗֊s�̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">�ȉ~�̃X�g���[�N�̑����B</param>
        void DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>�w�肳�ꂽ���@�ƃX�g���[�N�őȉ~�̗֊s��`�悵�܂��B</summary>
        /// <param name="rect">�`�悷��ȉ~�̈ʒu�Ɣ��a�B</param>
        /// <param name="brush">�ȉ~�̗֊s�̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">�ȉ~�̃X�g���[�N�̑����B</param>
        /// <param name="strokeStyle">�X�g���[�N�X�^�C���B</param>
        void DrawEllipse(RectangleF rect, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>�w�肳�ꂽ���@�ƃX�g���[�N�őȉ~�̗֊s��`�悵�܂��B</summary>
        /// <param name="ellipse">�ȉ~�̈�B</param>
        /// <param name="brush">�ȉ~�̗֊s�̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">�ȉ~�̃X�g���[�N�̑����B</param>
        void DrawEllipse(Ellipse ellipse, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>�w�肳�ꂽ���@�ƃX�g���[�N�őȉ~�̗֊s��`�悵�܂��B</summary>
        /// <param name="ellipse">�ȉ~�̈�B</param>
        /// <param name="brush">�ȉ~�̗֊s�̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">�ȉ~�̃X�g���[�N�̑����B</param>
        /// <param name="strokeStyle">�X�g���[�N�X�^�C���B</param>
        void DrawEllipse(Ellipse ellipse, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>�w�肳�ꂽ�W�I���g���̗֊s��`�悵�܂��B</summary>
        /// <param name="geometry">�`��W�I���g���B</param>
        /// <param name="brush">�X�g���[�N��h��Ԃ��u���V�B</param>
        /// <param name="strokeWidth">�X�g���[�N�̑����B</param>
        void DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>�w�肳�ꂽ�W�I���g���̗֊s��`�悵�܂��B</summary>
        /// <param name="geometry">�`��W�I���g���B</param>
        /// <param name="brush">�X�g���[�N��h��Ԃ��u���V�B</param>
        /// <param name="strokeWidth">�X�g���[�N�̑����B</param>
        /// <param name="strokeStyle">�X�g���[�N�X�^�C���B</param>
        void DrawGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        //this->renderTarget->DrawGlyphRun;

        /// <summary>�w�肳�ꂽ�X�g���[�N �X�^�C�����g�p���āA�w�肳�ꂽ�_�̊Ԃɐ���`�悵�܂��B</summary>
        /// <param name="startPt">���̎n�_�B</param>
        /// <param name="endPt">���̏I�_�B</param>
        /// <param name="brush">���̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">���̃X�g���[�N�̑����B</param>
        void DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>�w�肳�ꂽ�X�g���[�N �X�^�C�����g�p���āA�w�肳�ꂽ�_�̊Ԃɐ���`�悵�܂��B</summary>
        /// <param name="startPt">���̎n�_�B</param>
        /// <param name="endPt">���̏I�_�B</param>
        /// <param name="brush">���̕`��Ɏg�p����u���V�B</param>
        /// <param name="strokeWidth">���̃X�g���[�N�̑����B</param>
        void DrawLine(PointF startPt, PointF endPt, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>��`��`�悵�܂��B</summary>
        /// <param name="rectangle">�Ώۂ̋�`�B</param>
        /// <param name="brush">���̃u���V�B</param>
        /// <param name="strokeWidth">���̃X�g���[�N�̑����B</param>
        void DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush, float strokeWidth);

        /// <summary>��`��`�悵�܂��B</summary>
        /// <param name="rectangle">�Ώۂ̋�`�B</param>
        /// <param name="brush">���̃u���V�B</param>
        /// <param name="strokeWidth">���̃X�g���[�N�̑����B</param>
        /// <param name="strokeStyle">�X�g���[�N�X�^�C���B</param>
        void DrawRectangle(RectangleF rectangle, VisualResourceEntity ^ brush, float strokeWidth, VisualResourceEntity ^ strokeStyle);

        /// <summary>���������g�p���āA�w�肳�ꂽ�������`�悵�܂��B</summary>
        /// <param name="text">�`�敶����B</param>
        /// <param name="format">�������B</param>
        /// <param name="rect">�����񂪕`�悳���̈�̃T�C�Y�ƈʒu�B</param>
        /// <param name="brush">�`��Ɏg�p����u���V�B</param>
        void DrawText(String ^ text, VisualResourceEntity ^ format, RectangleF rect, VisualResourceEntity ^ brush);

        //this->renderTarget->DrawTextLayout;
        //this->renderTarget->FillRoundedRectangle;

        /// <summary>�w�肳�ꂽ�ȉ~�̈�̓�����`�悵�܂��B</summary>
        /// <param name="ellipse">�ȉ~�̈�B</param>
        /// <param name="brush">�ȉ~������h��Ԃ��u���V�B</param>
        void FillEllipse(Ellipse ellipse, VisualResourceEntity ^ brush);

        /// <summary>�w�肳�ꂽ�W�I���g���̓�����`�悵�܂��B</summary>
        /// <param name="geometry">�`��W�I���g���B</param>
        /// <param name="brush">�W�I���g��������h��Ԃ��u���V�B</param>
        void FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush);

        /// <summary>�w�肳�ꂽ�W�I���g���̓�����`�悵�܂��B</summary>
        /// <param name="geometry">�`��W�I���g���B</param>
        /// <param name="brush">�W�I���g��������h��Ԃ��u���V�B</param>
        /// <param name="opacitybrush">�W�I���g���ɓK�p����s�����x�}�X�N�B</param>
        void FillGeometry(VisualResourceEntity ^ geometry, VisualResourceEntity ^ brush, VisualResourceEntity ^ opacitybrush);

        //this->renderTarget->FillMesh;

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v�ɂ���ċL�q���ꂽ�s�����}�X�N���u���V�ɓK�p���A���̃u���V���g�p���ă����_�[�^�[�Q�b�g�̗̈���y�C���g���܂��B </summary>
        /// <param name="bitmap">�u���V�ɓK�p����s�����}�X�N�B</param>
        /// <param name="brush">�����_�[�^�[�Q�b�g�̗̈���y�C���g���邽�߂Ɏg�p�����u���V�B</param>
        /// <param name="opacitybrush">�s�����x�}�X�N�Ɋ܂܂��R���e���c�̃^�C�v�B</param>
        void FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v�ɂ���ċL�q���ꂽ�s�����}�X�N���u���V�ɓK�p���A���̃u���V���g�p���ă����_�[�^�[�Q�b�g�̗̈���y�C���g���܂��B </summary>
        /// <param name="bitmap">�u���V�ɓK�p����s�����}�X�N�B</param>
        /// <param name="brush">�����_�[�^�[�Q�b�g�̗̈���y�C���g���邽�߂Ɏg�p�����u���V�B</param>
        /// <param name="opacitybrush">�s�����x�}�X�N�Ɋ܂܂��R���e���c�̃^�C�v�B</param>
        /// <param name="destinationRectangle">�`�悷�郌���_�[�^�[�Q�b�g�̗̈�B</param>
        void FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask, RectangleF destinationRectangle);

        /// <summary>�w�肳�ꂽ�r�b�g�}�b�v�ɂ���ċL�q���ꂽ�s�����}�X�N���u���V�ɓK�p���A���̃u���V���g�p���ă����_�[�^�[�Q�b�g�̗̈���y�C���g���܂��B </summary>
        /// <param name="bitmap">�u���V�ɓK�p����s�����}�X�N�B</param>
        /// <param name="brush">�����_�[�^�[�Q�b�g�̗̈���y�C���g���邽�߂Ɏg�p�����u���V�B</param>
        /// <param name="opacitybrush">�s�����x�}�X�N�Ɋ܂܂��R���e���c�̃^�C�v�B</param>
        /// <param name="destinationRectangle">�`�悷�郌���_�[�^�[�Q�b�g�̗̈�B</param>
        /// <param name="sourceRectangle">�s�����}�X�N�Ƃ��Ďg�p����r�b�g�}�b�v�̗̈�B</param>
        void FillOpacityMask(VisualResourceEntity ^ bitmap, VisualResourceEntity ^ brush, OpacityMaskContent opacityMask, RectangleF destinationRectangle, RectangleF sourceRectangle);

        /// <summary>�h��Ԃ��ꂽ��`��`�悵�܂��B</summary>
        /// <param name="rectangle">�Ώۂ̋�`�B</param>
        /// <param name="brush">������h��Ԃ��u���V�B</param>
        void FillRectangle(RectangleF rectangle, VisualResourceEntity ^ brush);

        //this->renderTarget->FillRoundedRectangle;
    };
}

