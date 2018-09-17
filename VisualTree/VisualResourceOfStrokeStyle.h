#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "CapStyle.h"
#include "DashStyle.h"
#include "LineJoin.h"
#include "VisualResource.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>�X�g���[�N�X�^�C�����\�[�X�B</summary>
    public ref class VisualResourceOfStrokeStyle sealed
        : public VisualResource
    {
    public:
        /// <summary>�`��̗֊s��`���X�g���[�N���L�q���܂��B</summary>
        ref class StrokeStyleProperties
        {
        private:
            // �X�g���[�N�W�I���g���ŊJ���Ă����[�`��
            CapStyle startCap;

            // �X�g���[�N�W�I���g���ŊJ���Ă���I�[�`��
            CapStyle endCap;

            // �e�_�b�V���Z�O�����g�̗��[�̌`��
            CapStyle dashCap;

            // �Z�O�����g�̌������@�������l
            LineJoin lineJoin;

            // �ڍ����ꂽ�p�̐ڍ��̌����̐����B���̒l�͏��1.0f�ȏ�ł��邩�̂悤�Ɉ����܂�
            float miterLimit;

            // �X�g���[�N�Ƀ_�b�V���p�^�[�������邩�ǂ������w�肷��l
            DashStyle dashStyle;

            // �_�b�V���V�[�P���X���̃I�t�Z�b�g���w�肷��l
            float dashOffset;

        public:
            /// <summary>�X�g���[�N�W�I���g���ŊJ���Ă����[�`���ݒ�A�擾����B</summary>
            property CapStyle StartCap {
                CapStyle get() { return this->startCap; }
                void set(CapStyle value) { this->startCap = value; }
            }

            /// <summary>�X�g���[�N�W�I���g���ŊJ���Ă���I�[�`���ݒ�A�擾����B</summary>
            property CapStyle EndCap {
                CapStyle get() { return this->endCap; }
                void set(CapStyle value) { this->endCap = value; }
            }

            /// <summary>�e�_�b�V���Z�O�����g�̗��[�̌`���ݒ�A�擾����B</summary>
            property CapStyle DashCap {
                CapStyle get() { return this->dashCap; }
                void set(CapStyle value) { this->dashCap = value; }
            }

            /// <summary>�Z�O�����g�̌������@�������l��ݒ�A�擾����B</summary>
            property VisualTree::LineJoin LineJoin {
                VisualTree::LineJoin get() { return this->lineJoin; }
                void set(VisualTree::LineJoin value) { this->lineJoin = value; }
            }

            /// <summary>�ڍ����ꂽ�p�̐ڍ��̌����̐�����ݒ�A�擾����B</summary>
            property float MiterLimit {
                float get() { return this->miterLimit; }
                void set(float value) { this->miterLimit = value; }
            }

            /// <summary>�X�g���[�N�Ƀ_�b�V���p�^�[�������邩�ǂ������w�肷��l��ݒ�A�擾����B</summary>
            property VisualTree::DashStyle DashStyle {
                VisualTree::DashStyle get() { return this->dashStyle; }
                void set(VisualTree::DashStyle value) { this->dashStyle = value; }
            }

            /// <summary>�_�b�V���V�[�P���X���̃I�t�Z�b�g���w�肷��l��ݒ�A�擾����B</summary>
            property float DashOffset {
                float get() { return this->dashOffset; }
                void set(float value) { this->dashOffset = value; }
            }
        };

	private:
        // �`��t�@�N�g��
        ID2D1Factory * factory;

        // �X�g���[�N�X�^�C��
        ID2D1StrokeStyle * strokeStyle;

        // �X�g���[�N�`��
        StrokeStyleProperties ^ properties;

        // �_�b�V���p�^�[��
        List<float>^ dashes;

    public:
        /// <summary>�`��̗֊s��`���X�g���[�N���擾����B</summary>
        property StrokeStyleProperties ^ Properties
        {
            StrokeStyleProperties ^ get() { return this->properties; }
        }

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="factory">�`��t�@�N�g���B</param>
        VisualResourceOfStrokeStyle(String ^ name, ID2D1Factory * factory)
            : VisualResource(name), factory(factory), strokeStyle(NULL)
        {      
            this->properties = gcnew StrokeStyleProperties();
            this->dashes = gcnew List<float>();
        }

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfStrokeStyle() {}

    public:
        /// <summary>�_�b�V���p�^�[������������B</summary>
        void DashesClear()
        {
            this->dashes->Clear();
        }

        /// <summary>�_�b�V���p�^�[���ɒǉ�����B</summary>
        /// <param name="value">�ǉ�����l�B</param>
        void DashesAdd(float value)
        {
            this->dashes->Add(value);
        }

        /// <summary>�_�b�V���p�^�[���ɒǉ�����B</summary>
        /// <param name="values">�ǉ�����l���X�g�B</param>
        void DashesAddRange(System::Collections::Generic::IEnumerable<float>^ values)
        {
            this->dashes->AddRange(values);
        }

        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
            if (this->factory != NULL) {
                if (this->strokeStyle == NULL) {
                    D2D1_STROKE_STYLE_PROPERTIES prop = D2D1::StrokeStyleProperties(
                        (D2D1_CAP_STYLE)this->properties->StartCap,
                        (D2D1_CAP_STYLE)this->properties->EndCap,
                        (D2D1_CAP_STYLE)this->properties->DashCap,
                        (D2D1_LINE_JOIN)this->properties->LineJoin,
                        this->properties->MiterLimit,
                        (D2D1_DASH_STYLE)this->properties->DashStyle,
                        this->properties->DashOffset);

                    ID2D1StrokeStyle * stroke;
                    std::vector<float> dhs(this->dashes->Count);
                    for each (float v in this->dashes) {
                        dhs.push_back(v);
                    }
                    this->factory->CreateStrokeStyle(prop, (float*)dhs.data(), (UINT32)dhs.size(), &stroke);
                    this->strokeStyle = stroke;
                }
                return gcnew VisualResourceEntity2D(this, this->strokeStyle, true);
            }
            else {
                return nullptr;
            }
		}
    };
}
