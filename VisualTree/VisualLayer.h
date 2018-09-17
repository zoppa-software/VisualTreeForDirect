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

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>�`�惌�C���[�B</summary>
    public ref class VisualLayer sealed
        : IDisposable
    {
    public:
        /// <summary>���C���[ ���\�[�X�̃R���e���c�̋��E�A�}�X�N���A�s�����x�̐ݒ�A����т��̑��̃I�v�V�������i�[���܂��B</summary>
        ref class LayerParameters
        {
        private:
            // ���C���[�̃R���e���c�̋��E
            RectangleF contentBounds;

            // �W�I���g���}�X�N�́A�����_�[ �^�[�Q�b�g�ɓ�������Ă��郌�C���[�̗̈���w�肵�܂�
            VisualResourceEntity ^ geometricMask;

            // �A���`�G�C���A�V���O���[�h���w�肷��l
            AntialiasMode maskAntialiasMode;

            // ���C���[�̍쐬���ɃW�I���g���}�X�N�ɓK�p�����ϊ����w�肷��l
            Matrix maskTransform;

            // �^�[�Q�b�g�ɓ��������Ƃ��Ƀ��C���[���̂��ׂẴ��\�[�X�Ɉꗥ�ɓK�p�����s�����x�̒l
            float opacity;

            // ���C���[�̕s�����x�̕ύX�Ɏg�p�����u���V
            VisualResourceEntity ^ opacityBrush;

            // ���C���[�� ClearType �A���`�G�C���A�V���O���g�p���ăe�L�X�g�������_�����O���邩�ǂ������w�肷��l
            LayerOptions layerOptions;

        public:
            /// <summary>���C���[�̃R���e���c�̋��E��ݒ�A�擾����B</summary>
            property RectangleF ContentBounds {
                RectangleF get() { return this->contentBounds; }
                void set(RectangleF value) { this->contentBounds = value; }
            }

            /// <summary>�W�I���g���}�X�N��ݒ�A�擾����B</summary>
            property VisualResourceEntity ^ GeometricMask {
                VisualResourceEntity ^ get() { return this->geometricMask; }
                void set(VisualResourceEntity ^ value) { this->geometricMask = value; }
            }

            /// <summary>�A���`�G�C���A�V���O���[�h��ݒ�A�擾����B</summary>
            property AntialiasMode MaskAntialiasMode {
                AntialiasMode get() { return this->maskAntialiasMode; }
                void set(AntialiasMode value) { this->maskAntialiasMode = value; }
            }

            /// <summary>���C���[�̍쐬���ɃW�I���g���}�X�N��ݒ�A�擾����B</summary>
            property Matrix MaskTransform {
                Matrix get() { return this->maskTransform; }
                void set(Matrix value) { this->maskTransform = value; }
            }

            /// <summary>���C���[�� ClearType �A���`�G�C���A�V���O���g�p���ăe�L�X�g�������_�����O���邩�ǂ������w�肷��l��ݒ�A�擾����B</summary>
            property float Opacity {
                float get() { return this->opacity; }
                void set(float value) { this->opacity = value; }
            }

            /// <summary>���C���[�̕s�����x�̕ύX�Ɏg�p�����u���V��ݒ�A�擾����B</summary>
            property VisualResourceEntity ^ OpacityBrush {
                VisualResourceEntity ^ get() { return this->opacityBrush; }
                void set(VisualResourceEntity ^ value) { this->opacityBrush = value; }
            }

            /// <summary>�s�����x�̒l��ݒ�A�擾����B</summary>
            property VisualTree::LayerOptions LayerOptions {
                VisualTree::LayerOptions get() { return this->layerOptions; }
                void set(VisualTree::LayerOptions value) { this->layerOptions = value; }
            }

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            LayerParameters()
                : contentBounds(RectangleF(FLT_MIN, FLT_MIN, FLT_MAX, FLT_MAX)),
                  geometricMask(nullptr),
                  maskAntialiasMode(AntialiasMode::ANTIALIAS_MODE_PER_PRIMITIVE),
                  maskTransform(Matrix::Identity()),
                  opacity(1),
                  opacityBrush(nullptr),
                  layerOptions(VisualTree::LayerOptions::D2D1_LAYER_OPTIONS_NONE)
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

