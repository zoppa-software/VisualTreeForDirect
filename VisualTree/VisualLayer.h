#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <limits>
#include "AntialiasMode.h"
#include "LayerOptions.h"
#include "Matrix.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>�`�惌�C���[�B</summary>
    public ref class VisualLayer sealed
        : IDisposable
    {
    public:
        /// <summary>���C���[ ���\�[�X�̃R���e���c�̋��E�A�}�X�N���A�s�����x�̐ݒ�A����т��̑��̃I�v�V�������i�[���܂��B</summary>
        ref class LayerParameters
        {
        public:
            /// <summary>���C���[�̃R���e���c�̋��E�B</summary>
            RectangleF contentBounds;

            /// <summary>�W�I���g�� �}�X�N�́A�����_�[ �^�[�Q�b�g�ɓ�������Ă��郌�C���[�̗̈���w�肵�܂��B</summary>
            VisualResourceEntity ^ geometricMask;

            /// <summary>�A���`�G�C���A�V���O ���[�h���w�肷��l�B</summary>
            AntialiasMode maskAntialiasMode;

            /// <summary>���C���[�̍쐬���ɃW�I���g�� �}�X�N�ɓK�p�����ϊ����w�肷��l�B</summary>
            Matrix maskTransform;

            /// <summary>�^�[�Q�b�g�ɓ��������Ƃ��Ƀ��C���[���̂��ׂẴ��\�[�X�Ɉꗥ�ɓK�p�����s�����x�̒l�B</summary>
            float opacity;

            /// <summary>���C���[�̕s�����x�̕ύX�Ɏg�p�����u���V�B</summary>
            VisualResourceEntity ^ opacityBrush;

            /// <summary>���C���[�� ClearType �A���`�G�C���A�V���O���g�p���ăe�L�X�g�������_�����O���邩�ǂ������w�肷��l�B</summary>
            LayerOptions layerOptions;

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            LayerParameters()
                : contentBounds(RectangleF(FLT_MIN, FLT_MIN, FLT_MAX, FLT_MAX)),
                  geometricMask(nullptr),
                  maskAntialiasMode(AntialiasMode::ANTIALIAS_MODE_PER_PRIMITIVE),
                  maskTransform(Matrix::Identity()),
                  opacity(1),
                  opacityBrush(nullptr),
                  layerOptions(LayerOptions::D2D1_LAYER_OPTIONS_NONE)
            {}
        };

    private:
        // ���C���[�Q��
        ID2D1Layer * layer;

        // ���C���[�p�����[�^
        LayerParameters ^ parameters;

    public:
        /// <summary>���C���[�p�����[�^���擾����B</summary>
        property LayerParameters ^ Parameters
        {
            LayerParameters ^ get() {
                return this->parameters;
            }
        }

    internal:
        /// <summary>�R���X�g���N�^�B</summary>
        VisualLayer()
            : layer(NULL)
        {
            this->parameters = gcnew LayerParameters();
        }

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="layer">�Ώۃ��C���[�B</param>
        VisualLayer(ID2D1Layer * layer)
            : layer(layer)
        {
            this->parameters = gcnew LayerParameters();
        }

    public:
        /// <summary>�f�X�g���N�^�B</summary>
        ~VisualLayer()
        {
            if (this->layer != NULL) {
                this->layer->Release();
                this->layer = NULL;
            }
        }

        /// <summary>�t�@�C�i���C�U�B</summary>
        !VisualLayer()
        {
            this->~VisualLayer();
        }

    internal:
        /// <summary>�Ώۃ��C���[�̃|�C���^���擾����B</summary>
        /// <return>�Ώۃ��C���[�B</return>
        ID2D1Layer * GetInstance() { return this->layer; }
    };
}

