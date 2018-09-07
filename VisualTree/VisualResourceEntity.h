#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree {

    ref class VisualResource;

    /// <summary>���\�[�X�N���X�E�`����́B</summary>
    public ref class VisualResourceEntity
    {
    protected:
        // ���ƂȂ������\�[�X�Q��
        VisualResource ^    resource;

        // Direct2D�̃C���X�^���X
        ID2D1Resource *		instance;

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        VisualResourceEntity(VisualResource ^ resource, ID2D1Resource * instance) {
            this->resource = resource;
            this->instance = instance;
        }

    public:
        /// <summary>���\�[�X���������B</summary>
        void SafeRelease() {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>Direct2D�̃C���X�^���X���擾����B</summary>
        ID2D1Resource * GetInstance() {
            return this->instance;
        }

        /// <summary>�F�ݒ��ύX����B</summary>
        /// <param name="color">�ύX����F�B</param>
        virtual void SetColor(System::Drawing::Color color) {}
    };

    /// <summary>���\�[�X�N���X�E�`����́i�\���b�h�u���V�p�j</summary>
    ref class VisualResourceEntityOfSolidBrush sealed
        : public VisualResourceEntity
    {
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        VisualResourceEntityOfSolidBrush(VisualResource ^ parent, ID2D1Resource * instance)
            : VisualResourceEntity(parent, instance) {
        }

    public:
        /// <summary>�F�ݒ��ύX����B</summary>
        /// <param name="color">�ύX����F�B</param>
        void SetColor(System::Drawing::Color color) override;
    };
}