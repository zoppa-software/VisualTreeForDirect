#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    ref class VisualResource;

    /// <summary>���\�[�X�N���X�E�`����́B</summary>
    public ref class VisualResourceEntity abstract
    {
    protected:
        // ���ƂȂ������\�[�X�Q��
        VisualResource ^    resource;

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        VisualResourceEntity(VisualResource ^ resource)
            : resource(resource) {}

    public:
        /// <summary>���\�[�X���������B</summary>
        virtual void SafeRelease() abstract;

        /// <summary>���\�[�X���������B</summary>
        virtual void ForceRelease() abstract;

        /// <summary>Direct2D�̃C���X�^���X���擾����B</summary>
        virtual ID2D1Resource * GetInstance() { return NULL; }

        /// <summary>�R���C���^�[�t�F�C�X�̃C���X�^���X���擾����B</summary>
        virtual IUnknown * GetWriteInstance() { return NULL; }

        /// <summary>�F�ݒ��ύX����B</summary>
        /// <param name="color">�ύX����F�B</param>
        virtual void SetColor(System::Drawing::Color color) {}
    };

    /// <summary>���\�[�X�N���X�E�`����́B</summary>
    ref class VisualResourceEntity2D
        : public VisualResourceEntity
    {
    protected:
        // Direct2D�̃C���X�^���X
        ID2D1Resource *		instance;

        // �������C�t�T�C�N���Ȃ�ΐ^
        bool isLongLife;

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        VisualResourceEntity2D(VisualResource ^ resource, ID2D1Resource * instance)
            : VisualResourceEntity(resource), instance(instance), isLongLife(false) {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        /// <param name="isLongLife">�������C�t�T�C�N���Ȃ�ΐ^�B</param>
        VisualResourceEntity2D(VisualResource ^ resource, ID2D1Resource * instance, bool isLongLife)
            : VisualResourceEntity(resource), instance(instance), isLongLife(isLongLife) {}

    public:
        /// <summary>���\�[�X���������B</summary>
        void SafeRelease() override
        {
            if (this->instance != NULL && this->isLongLife) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>���\�[�X���������B</summary>
        void ForceRelease() override
        {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>Direct2D�̃C���X�^���X���擾����B</summary>
        ID2D1Resource * GetInstance() override
        {
            return this->instance;
        }

        /// <summary>�F�ݒ��ύX����B</summary>
        /// <param name="color">�ύX����F�B</param>
        void SetColor(System::Drawing::Color color) override {}
    };

    /// <summary>���\�[�X�N���X�E�`����́i�\���b�h�u���V�p�j</summary>
    ref class VisualResourceEntityOfSolidBrush sealed
        : public VisualResourceEntity2D
    {
    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        VisualResourceEntityOfSolidBrush(VisualResource ^ parent, ID2D1Resource * instance)
            : VisualResourceEntity2D(parent, instance) {}

    public:
        /// <summary>�F�ݒ��ύX����B</summary>
        /// <param name="color">�ύX����F�B</param>
        void SetColor(System::Drawing::Color color) override;
    };

    /// <summary>���\�[�X�N���X�E�`����́iCOM�j</summary>
    ref class VisualResourceEntityWrite
        : public VisualResourceEntity
    {
    protected:
        // �R���C���^�[�t�F�C�X�̃C���X�^���X
        IUnknown *		instance;

        // �������C�t�T�C�N���Ȃ�ΐ^
        bool isLongLife;

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        VisualResourceEntityWrite(VisualResource ^ resource, IUnknown * instance)
            : VisualResourceEntity(resource), instance(instance), isLongLife(false) {}

        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="resource">���̃��\�[�X�B</param>
        /// <param name="instance">Direct2D�̃C���X�^���X�B</param>
        /// <param name="isLongLife">�������C�t�T�C�N���Ȃ�ΐ^�B</param>
        VisualResourceEntityWrite(VisualResource ^ resource, IUnknown * instance, bool isLongLife)
            : VisualResourceEntity(resource), instance(instance), isLongLife(isLongLife) {}

    public:
        /// <summary>���\�[�X���������B</summary>
        void SafeRelease() override
        {
            if (this->instance != NULL && this->isLongLife) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>���\�[�X���������B</summary>
        void ForceRelease() override
        {
            if (this->instance != NULL) {
                this->instance->Release();
                this->instance = NULL;
            }
        }

        /// <summary>�R���C���^�[�t�F�C�X�̃C���X�^���X���擾����B</summary>
        IUnknown * GetWriteInstance() override
        {
            return this->instance;
        }

        /// <summary>�F�ݒ��ύX����B</summary>
        /// <param name="color">�ύX����F�B</param>
        void SetColor(System::Drawing::Color color) override {}
    };
}