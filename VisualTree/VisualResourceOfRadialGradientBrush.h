#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "VisualResource.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace VisualTree
{
    /// <summary>���C���O���f�[�V�����u���V�C���X�^���X�B</summary>
	public ref class VisualResourceOfRadialGradientBrush
        : public VisualResource
    {
    public:
        /// <summary>�K���}�F��Ԑݒ�B</summary>
        enum class GAMMA
        {
            /// <summary>2.2�K���}�F��Ԃŕ�Ԃ����B</summary>
            GAMMA_2_2 = 0,

            /// <summary>1.0�K���}�F��Ԃŕ�Ԃ����B</summary>
            GAMMA_1_0 = 1,

            /// <summary>�����l�B</summary>
            GAMMA_FORCE_DWORD = -1
        };

        /// <summary>�F�̈������΂��ݒ�B</summary>
        enum class EXTEND_MODE
        {
            /// <summary>�T���v���|�C���g���G�b�W�ɃN�����v���邱�Ƃɂ��A�\�[�X�̃G�b�W���g�����܂��B</summary>
            EXTEND_MODE_CLAMP = 0,
    
            /// <summary>�x�[�X�^�C���͕ϊ����ꂸ�ɕ`�悳��A�c��̓x�[�X�^�C�����J��Ԃ����Ƃœh��Ԃ���܂��B</summary>
            EXTEND_MODE_WRAP = 1,
    
            /// <summary>�܂�Ԃ��Ɠ����ł����A��փ^�C�������]���܂��B�x�[�X�^�C���͕ό`���ꂸ�ɕ`�悳��܂��B</summary>
            EXTEND_MODE_MIRROR = 2,

            /// <summary>�����l�B</summary>
            EXTEND_MODE_FORCE_DWORD = -1
        };

    public:
        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF���i�[����B</summary>
        ref class GradientStop
        {
        public:
            // �F
            Color color;

            // �ʒu
            float position;

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="edgeColor">�F�B</param>
            /// <param name="position">�ʒu�B</param>
            GradientStop(Color edgeColor, float position)
                : color(edgeColor), position(position)
            {}
        };

        /// <summary>�O���f�[�V�����̌��_�̃I�t�Z�b�g�A�O���f�[�V�����ȉ~�̃T�C�Y�ƈʒu���i�[�B</summary>
        ref class RadialGradientBrushProperties
        {
        private:
            // �O���f�[�V�����ȉ~�̒��S
            PointF  center;

            // �O���f�[�V�����ȉ~�̒��S�Ƒ��ΓI�ȃO���f�[�V�������_�̃I�t�Z�b�g
            PointF  gradientOriginOffset;

            // �O���f�[�V�����ȉ~��X���a
            float   radiusX;

            // �O���f�[�V�����ȉ~��Y���a
            float   radiusY;

        public:
            /// <summary>�O���f�[�V�����ȉ~�̒��S��ݒ�A�擾����B</summary>
            property PointF Center {
                PointF get() { return this->center; }
                void set(PointF pos) { this->center = pos; }
            }

            /// <summary>�O���f�[�V�����ȉ~�̒��S�Ƒ��ΓI�ȃO���f�[�V�������_�̃I�t�Z�b�g��ݒ�A�擾����B</summary>
            property PointF GradientOriginOffset {
                PointF get() { return this->gradientOriginOffset; }
                void set(PointF pos) { this->gradientOriginOffset = pos; }
            }

            /// <summary>�O���f�[�V�����ȉ~��X���a��ݒ�A�擾����B</summary>
            property float RadiusX {
                float get() { return this->radiusX; }
                void set(float pos) { this->radiusX = pos; }
            }

            /// <summary>�O���f�[�V�����ȉ~��Y���a��ݒ�A�擾����B</summary>
            property float RadiusY {
                float get() { return this->radiusY; }
                void set(float pos) { this->radiusY = pos; }
            }
        };

	private:
        // �O���f�[�V�������E�̈ʒu�ƐF���X�g
        List<GradientStop^>^ gradientStops;

        // �K���}�F���
        GAMMA gamma;

        // �F�̈������΂��ݒ�
        EXTEND_MODE extendMode;

        // �O���f�[�V�����̌��_�̃I�t�Z�b�g�A�O���f�[�V�����ȉ~�̃T�C�Y�ƈʒu
        RadialGradientBrushProperties ^ properties;

    public:
        /// <summary>�K���}�F��Ԑݒ��ݒ�A�擾����B</summary>
        property GAMMA Gamma {
            GAMMA get() { return this->gamma; }
            void set(GAMMA gamma) { this->gamma = gamma; }
        }

        /// <summary>�F�̈������΂��ݒ��ݒ�A�擾����B</summary>
        property EXTEND_MODE ExtendMode {
            EXTEND_MODE get() { return this->extendMode; }
            void set(EXTEND_MODE mode) { this->extendMode = mode; }
        }

        /// <summary>�O���f�[�V�����̌��_�̃I�t�Z�b�g�A�O���f�[�V�����ȉ~�̃T�C�Y�ƈʒu��ݒ�A�擾����B</summary>
        property RadialGradientBrushProperties ^ Propertes {
            RadialGradientBrushProperties ^ get() { return this->properties; }
        }

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
		VisualResourceOfRadialGradientBrush(String ^ name)
			: VisualResource(name), gamma(GAMMA::GAMMA_2_2), extendMode(EXTEND_MODE::EXTEND_MODE_CLAMP) {
            this->gradientStops = gcnew List<GradientStop^>();
            this->properties = gcnew RadialGradientBrushProperties();
        }

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfRadialGradientBrush() {}

	public:
        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF��S�ď�������B</summary>
        void Clear()
        {
            this->gradientStops->Clear();
        }

        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF��ǉ�����B</summary>
        void AddGradientStop(Color edgeColor, float position)
        {
            this->gradientStops->Add(gcnew GradientStop(edgeColor, position));
        }

        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
        VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override
        {
            // �O���f�[�V�������E�̈ʒu�ƐF�����X�g������
            std::vector<D2D1_GRADIENT_STOP> pos;
            if (this->gradientStops->Count > 0) {
                for each (GradientStop^ stp in this->gradientStops) {
                    D2D1_GRADIENT_STOP st;
                    st.color = D2D1::ColorF(stp->color.R / 255.0f,
                        stp->color.G / 255.0f,
                        stp->color.B / 255.0f,
                        stp->color.A / 255.0f);
                    st.position = stp->position;
                    pos.push_back(st);
                }
            }
            else {
                D2D1_GRADIENT_STOP st;
                st.color = D2D1::ColorF(1, 1, 1, 1);
                st.position = 1;
                pos.push_back(st);
            }
            
            // �O���f�[�V�����ݒ���s��
            ID2D1GradientStopCollection * gradientStops = NULL;
            ID2D1RadialGradientBrush * brush = NULL;
            HRESULT hr = renderTarget->CreateGradientStopCollection(pos.data(),
                                                                    pos.size(),
                                                                    (D2D1_GAMMA)this->gamma,
                                                                    (D2D1_EXTEND_MODE)this->extendMode,
                                                                    &gradientStops);
            if (SUCCEEDED(hr)) {
                D2D1_RADIAL_GRADIENT_BRUSH_PROPERTIES props = D2D1::RadialGradientBrushProperties(
                    D2D1::Point2F(this->properties->Center.X, this->properties->Center.Y),
                    D2D1::Point2F(this->properties->GradientOriginOffset.X, this->properties->GradientOriginOffset.Y),
                    this->properties->RadiusX,
                    this->properties->RadiusY);
                renderTarget->CreateRadialGradientBrush(props, gradientStops, &brush);
                gradientStops->Release();
            }
            return gcnew VisualResourceEntity(this, brush);
        }
    };
}
