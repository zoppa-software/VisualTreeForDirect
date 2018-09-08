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

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace VisualTree
{
    /// <summary>�X�g���[�N�X�^�C�����\�[�X�B</summary>
    public ref class VisualResourceOfStrokeStyle sealed
        : public VisualResource
    {
    public:
        /// <summary>�`��̗֊s��`���X�g���[�N���L�q���܂��B</summary>
        ref class StrokeStyleProperties
        {
        public:
            /// <summary>�X�g���[�N�W�I���g���ŊJ���Ă����[�`��B</summary>
            CapStyle startCap;

            /// <summary>�X�g���[�N�W�I���g���ŊJ���Ă���I�[�`��B</summary>
            CapStyle endCap;

            /// <summary>�e�_�b�V���Z�O�����g�̗��[�̌`��B</summary>
            CapStyle dashCap;

            /// <summary>�Z�O�����g�̌������@�������l�B</summary>
            LineJoin lineJoin;

            /// <summary>�ڍ����ꂽ�p�̐ڍ��̌����̐����B���̒l�͏��1.0f�ȏ�ł��邩�̂悤�Ɉ����܂��B</summary>
            float miterLimit;

            /// <summary>�X�g���[�N�Ƀ_�b�V���p�^�[�������邩�ǂ������w�肷��l�B</summary>
            DashStyle dashStyle;

            /// <summary>�_�b�V���V�[�P���X���̃I�t�Z�b�g���w�肷��l�B</summary>
            float dashOffset;
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
            this->dashes = gcnew List<float>();
            this->properties = gcnew StrokeStyleProperties();
        }

        /// <summary>�f�X�g���N�^�B</summary>
        virtual ~VisualResourceOfStrokeStyle() {}

    public:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
            if (this->factory != NULL) {
                if (this->strokeStyle == NULL) {
                    D2D1_STROKE_STYLE_PROPERTIES prop = D2D1::StrokeStyleProperties(
                        (D2D1_CAP_STYLE)this->properties->startCap,
                        (D2D1_CAP_STYLE)this->properties->endCap,
                        (D2D1_CAP_STYLE)this->properties->dashCap,
                        (D2D1_LINE_JOIN)this->properties->lineJoin,
                        this->properties->miterLimit,
                        (D2D1_DASH_STYLE)this->properties->dashStyle,
                        this->properties->dashOffset);
                    ID2D1StrokeStyle * stroke;
                    std::vector<float> dhs(this->dashes->Count);
                    for each (float v in this->dashes) {
                        dhs.push_back(v);
                    }
                    this->factory->CreateStrokeStyle(prop, (float*)dhs.data(), dhs.size(), &stroke);
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
