#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "GammaParameter.h"
#include "ExtendModeParameter.h"
#include "VisualResource.h"
#include "VisualResourceEntity.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    /// <summary>���C���O���f�[�V�����u���V�C���X�^���X�B</summary>
	public ref class VisualResourceOfLinearGradientBrush sealed
        : public VisualResource
    {
    public:
        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF���i�[����B</summary>
        ref class GradientStop
        {
        private:
            // �F
            Color color;

            // �ʒu
            float position;

        public:
            /// <summary>�F�ݒ��ݒ�A�擾����B</summary>
            property Color GradientColor {
                Color get() { return this->color; }
                void set(Color val) { this->color = val; }
            }

            /// <summary>�ʒu�ݒ��ݒ�A�擾����B</summary>
            property float Position {
                float get() { return this->position; }
                void set(float val) { this->position = val; }
            }

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="edgeColor">�F�B</param>
            /// <param name="position">�ʒu�B</param>
            GradientStop(Color edgeColor, float position)
                : color(edgeColor), position(position)
            {}
        };

        /// <summary>�O���f�[�V�������z���̊J�n�_�ƏI���_���i�[�B</summary>
        ref class LinearGradientBrushProperties
        {
        private:
            // �O���f�[�V�������̊J�n�_
            PointF  startPoint;

            // �O���f�[�V�������̏I���_
            PointF  endPoint;

        public:
            /// <summary>�O���f�[�V�������̊J�n�_��ݒ�A�擾����B</summary>
            property PointF StartPoint {
                PointF get() { return this->startPoint; }
                void set(PointF pos) { this->startPoint = pos; }
            }

            /// <summary>�O���f�[�V�������̏I���_��ݒ�A�擾����B</summary>
            property PointF EndPoint {
                PointF get() { return this->endPoint; }
                void set(PointF pos) { this->endPoint = pos; }
            }
        };

	private:
        // �O���f�[�V�������E�̈ʒu�ƐF���X�g
        List<GradientStop^>^ gradientStops;

        // �K���}�F���
        GammaParameter gamma;

        // �F�̈������΂��ݒ�
        ExtendModeParameter extendMode;

        // �O���f�[�V�����̌��_�̃I�t�Z�b�g�A�O���f�[�V�����ȉ~�̃T�C�Y�ƈʒu
        LinearGradientBrushProperties ^ properties;

    public:
        /// <summary>�K���}�F��Ԑݒ��ݒ�A�擾����B</summary>
        property GammaParameter Gamma {
            GammaParameter get() { return this->gamma; }
            void set(GammaParameter gamma) { this->gamma = gamma; }
        }

        /// <summary>�F�̈������΂��ݒ��ݒ�A�擾����B</summary>
        property ExtendModeParameter ExtendMode {
            ExtendModeParameter get() { return this->extendMode; }
            void set(ExtendModeParameter mode) { this->extendMode = mode; }
        }

        /// <summary>�O���f�[�V�������z���̊J�n�_�ƏI���_��ݒ�A�擾����B</summary>
        property LinearGradientBrushProperties ^ Propertes {
            LinearGradientBrushProperties ^ get() { return this->properties; }
        }

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
		VisualResourceOfLinearGradientBrush(String ^ name)
			: VisualResource(name),
              gamma(GammaParameter::GAMMA_2_2),
              extendMode(ExtendModeParameter::EXTEND_MODE_CLAMP)
        {
            this->gradientStops = gcnew List<GradientStop^>();
            this->properties = gcnew LinearGradientBrushProperties();
        }

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfLinearGradientBrush() {}

	public:
        /// <summary>�O���f�[�V�������E�̈ʒu�ƐF��S�ď�������B</summary>
        void ClearGradientStops()
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
                    st.color = D2D1::ColorF(stp->GradientColor.R / 255.0f,
                        stp->GradientColor.G / 255.0f,
                        stp->GradientColor.B / 255.0f,
                        stp->GradientColor.A / 255.0f);
                    st.position = stp->Position;
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
            ID2D1LinearGradientBrush * brush = NULL;
            HRESULT hr = renderTarget->CreateGradientStopCollection(pos.data(),
                                                                    (UINT32)pos.size(),
                                                                    (D2D1_GAMMA)this->gamma,
                                                                    (D2D1_EXTEND_MODE)this->extendMode,
                                                                    &gradientStops);
            if (SUCCEEDED(hr)) {
                D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES props = D2D1::LinearGradientBrushProperties(
                    D2D1::Point2F(this->properties->StartPoint.X, this->properties->StartPoint.Y),
                    D2D1::Point2F(this->properties->EndPoint.X, this->properties->EndPoint.Y));
                renderTarget->CreateLinearGradientBrush(props, gradientStops, &brush);
                gradientStops->Release();
            }
            return gcnew VisualResourceEntityOfBrush(this, brush);
        }
    };
}