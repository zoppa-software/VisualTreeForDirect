#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "ArcSize.h"
#include "FillMode.h"
#include "FigureBegin.h"
#include "FigureEnd.h"
#include "SweepDirection.h"
#include "VisualResource.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Drawing;

    /// <summary>�p�X�W�I���g�����\�[�X�B</summary>
	public ref class VisualResourceOfPathGeometry
		: public VisualResource
	{
	public:
        /// <summary>�x�W�F�Ȑ��Z�O�����g�B</summary>
        ref class BezierSegment
        {
        private:
            // ����_
            PointF pos1, pos2, pos3;

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            BezierSegment() {}

            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="p1">����_1�B</param>
            /// <param name="p2">����_2�B</param>
            /// <param name="p3">����_3�B</param>
            BezierSegment(PointF p1, PointF p2, PointF p3)
                : pos1(p1), pos2(p2), pos3(p3) {}

        public:
            /// <summary>����_1��ݒ�A�擾����B</summary>
            property PointF Point1 {
                PointF get() { return this->pos1; }
                void set(PointF pos) { this->pos1 = pos; }
            }

            /// <summary>����_2��ݒ�A�擾����B</summary>
            property PointF Point2 {
                PointF get() { return this->pos2; }
                void set(PointF pos) { this->pos2 = pos; }
            }

            /// <summary>����_3��ݒ�A�擾����B</summary>
            property PointF Point3 {
                PointF get() { return this->pos3; }
                void set(PointF pos) { this->pos3 = pos; }
            }
        };

        /// <summary>�~�ʃZ�O�����g�B</summary>
        ref class ArcSegment
        {
        private:
            PointF          point;
            SizeF           size;
            float           rotation;
            SweepDirection  sweep;
            ArcSize         arc;

        public:
            /// <summary>�R���X�g���N�^�B</summary>
            ArcSegment() {}

            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="point">�ʂ̏I�_�B</param>
            /// <param name="size">�ʂ�X���a�� Y���a�B</param>
            /// <param name="rotationAngle">�����v���ɉ�]����p�x�B</param>
            /// <param name="sweepDirection">�ʂ̑|�������v��肩�����v��肩���w�肷��l�B</param>
            /// <param name="arcSize">����̌ʂ� 180�����傫�����ǂ������w�肷��l�B</param>
            ArcSegment(PointF point, SizeF size, float rotationAngle,
                       SweepDirection sweepDirection, ArcSize arcSize)
                : point(point), size(size), rotation(rotationAngle),
                  sweep(sweepDirection), arc(arcSize) {}

        public:
            /// <summary>�ʂ̏I�_��ݒ�A�擾����B</summary>
            property PointF Point {
                PointF get() { return this->point; }
                void set(PointF pos) { this->point = pos; }
            }

            /// <summary>�ʂ�X���a�� Y���a��ݒ�A�擾����B</summary>
            property SizeF Size {
                SizeF get() { return this->size; }
                void set(SizeF sz) { this->size = sz; }
            }

            /// <summary>�����v���ɉ�]����p�x��ݒ�A�擾����B</summary>
            property float RotationAngle {
                float get() { return this->rotation; }
                void set(float rotation) { this->rotation = rotation; }
            }

            /// <summary>�ʂ̑|�������v��肩�����v��肩���w�肷��l��ݒ�A�擾����B</summary>
            property VisualTree::SweepDirection SweepDirection {
                VisualTree::SweepDirection get() { return this->sweep; }
                void set(VisualTree::SweepDirection rotation) { this->sweep = rotation; }
            }

            /// <summary>����̌ʂ� 180�����傫�����ǂ������w�肷��l��ݒ�A�擾����B</summary>
            property VisualTree::ArcSize ArcSize {
                VisualTree::ArcSize get() { return this->arc; }
                void set(VisualTree::ArcSize rotation) { this->arc = rotation; }
            }
        };

        /// <summary>�`������i�[����W�I���g���V���N�B</summary>
		ref class GeometrySink
			: IDisposable
		{
		private:
            // �W�I���g���p�X
			ID2D1GeometrySink * sink;

		internal:
            /// <summary>�R���X�g���N�^�B</summary>
            /// <param name="sink">���ɂȂ�W�I���g���p�X�B</param>
			GeometrySink(ID2D1GeometrySink * sink) 
				: sink(sink)
			{}

            /// <summary>�f�X�g���N�^�B</summary>
			~GeometrySink() {
				if (this->sink != NULL) {
					this->sink->Close();
					this->sink->Release();
					this->sink = NULL;
				}
			}

            /// <summary>�t�@�C�i���C�U�B</summary>
			!GeometrySink() {
				this->~GeometrySink();
			}

		public:
            /// <summary>���̃W�I���g���V���N�ɂ���ċL�q���ꂽ�W�I���g���̓����ɂ���_�ƊO���ɂ���_����肷�邽�߂Ɏg�p���郁�\�b�h���w�肵�܂��B</summary>
            /// <param name="mode">����_1�B</param>
			void SetFillMode(FillMode mode)
			{
				this->sink->SetFillMode((D2D1_FILL_MODE)mode);
			}

            /// <summary>�w�肳�ꂽ�_����V�����}���J�n���܂��B</summary>
            /// <param name="pos">�V�����}���J�n����_�B</param>
            /// <param name="begin">�V�����}��h��Ԃ����ǂ����B</param>
			void BeginFigure(PointF pos, FigureBegin begin)
			{
				this->sink->BeginFigure(D2D1::Point2F(pos.X, pos.Y), (D2D1_FIGURE_BEGIN)begin);
			}

            /// <summary>�_���w�肵�Ē�����ǉ�����B</summary>
            /// <param name="x">X�ʒu�B</param>
            /// <param name="y">Y�ʒu�B</param>
            void AddLine(float x, float y)
			{
                this->sink->AddLine(D2D1::Point2F(x, y));
			}

            /// <summary>�_���w�肵�Ē�����ǉ�����B</summary>
            /// <param name="point">�_�ʒu�B</param>
            void AddLine(PointF point)
			{
                this->sink->AddLine(D2D1::Point2F(point.X, point.Y));
			}

            /// <summary>�_���X�g���w�肵�Ĉ�A�̒�����ǉ�����B</summary>
            /// <param name="point">�_���X�g�B</param>
			void AddLines(System::Collections::Generic::IEnumerable<PointF>^ points)
			{
                std::vector<D2D1_POINT_2F> pos;
                for each (PointF p in points) {
                    pos.push_back(D2D1::Point2F(p.X, p.Y));
                }
                this->sink->AddLines(pos.data(), (UINT32)pos.size());
			}

            /// <summary>�~�ʏ����w�肵�ĉ~�ʂ�ǉ�����B</summary>
            /// <param name="segment">�~�ʏ��B</param>
            void AddArc(ArcSegment ^ segment)
            {
                D2D1_ARC_SEGMENT arc;
                arc.point = D2D1::Point2F(segment->Point.X, segment->Point.Y);
                arc.size = D2D1::SizeF(segment->Size.Width, segment->Size.Height);
                arc.rotationAngle = segment->RotationAngle;
                arc.sweepDirection = (D2D1_SWEEP_DIRECTION)segment->SweepDirection;
                arc.arcSize = (D2D1_ARC_SIZE)segment->ArcSize;
                this->sink->AddArc(arc);
            }

            /// <summary>�O�_���w�肵�ăx�W�F�Ȑ���ǉ�����B</summary>
            /// <param name="pos1">�_1�B</param>
            /// <param name="pos2">�_2�B</param>
            /// <param name="pos3">�_3�B</param>
            void AddBezier(PointF pos1, PointF pos2, PointF pos3)
            {
                D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                    D2D1::Point2F(pos1.X, pos1.Y),
                    D2D1::Point2F(pos2.X, pos2.Y),
                    D2D1::Point2F(pos3.X, pos3.Y)
                );
                this->sink->AddBezier(seg);
            }

            /// <summary>��A�� 3���x�W�G�Ȑ����쐬���ăW�I���g���V���N�ɒǉ����܂��B</summary>
            /// <param name="segment">�x�W�G�Ȑ����B</param>
            void AddBeziers(BezierSegment^ segment)
            {
                D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                    D2D1::Point2F(segment->Point1.X, segment->Point1.Y),
                    D2D1::Point2F(segment->Point2.X, segment->Point2.Y),
                    D2D1::Point2F(segment->Point3.X, segment->Point3.Y)
                );
                this->sink->AddBezier(&seg);
            }

            /// <summary>��A�� 3���x�W�G�Ȑ����쐬���ăW�I���g���V���N�ɒǉ����܂��B</summary>
            /// <param name="segment">�x�W�G�Ȑ����B</param>
            void AddBeziers(System::Collections::Generic::IEnumerable<BezierSegment^>^ segment)
            {
                std::vector<D2D1_BEZIER_SEGMENT> segs;
                for each (BezierSegment^ segpos in segment) {
                    D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                        D2D1::Point2F(segpos->Point1.X, segpos->Point1.Y),
                        D2D1::Point2F(segpos->Point2.X, segpos->Point2.Y),
                        D2D1::Point2F(segpos->Point3.X, segpos->Point3.Y)
                    );
                    segs.push_back(seg);
                }
                this->sink->AddBeziers(segs.data(), (UINT32)segs.size());
            }

            /// <summary>���݂̐}���I�����܂��B�K�v�ɉ����āA�}����邱�Ƃ��ł��܂��B</summary>
            /// <param name="end">���݂̐}����邩�ǂ����������l�B</param>
			void EndFigure(FigureEnd end)
			{
				this->sink->EndFigure((D2D1_FIGURE_END)end);
			}
		};

	private:
        // �p�X�W�I���g��
		ID2D1PathGeometry * geometry;

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="factory">�����_�[�t�@�N�g���B</param>
		VisualResourceOfPathGeometry(String ^ name, ID2D1Factory * factory)
			: VisualResource(name)
		{
			ID2D1PathGeometry * geo;
			HRESULT hr = factory->CreatePathGeometry(&geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
				throw gcnew ApplicationException("�p�X�W�I���g���̍쐬�Ɏ��s");
			}
		}

        /// <summary>�f�X�g���N�^�B</summary>
		~VisualResourceOfPathGeometry() {}

	public:
        /// <summary>�W�I���g���V���N���쐬����B</summary>
        /// <return>�W�I���g���V���N�B</return>
		GeometrySink ^ CreateGeometrySink()
		{
			ID2D1GeometrySink * sink;
			HRESULT hr = this->geometry->Open(&sink);
			if (SUCCEEDED(hr)) {
				return gcnew GeometrySink(sink);
			}
			else {
				throw gcnew ApplicationException("error");
			}
		}

        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
		VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
			return gcnew VisualResourceEntity2D(this, this->geometry, true);
		}

    internal:
        /// <summary>�p�X�W�I���g���̎��̂��擾����B</summary>
        /// <return>�p�X�W�I���g���B</return>
        ID2D1PathGeometry * GetGeometry() {
            return this->geometry;
        }
	};
}
