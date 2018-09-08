#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <vector>
#include "VisualResource.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree {

	public ref class VisualResourceOfPathGeometry
		: public VisualResource
	{
	public:
		enum class FILL_MODE
		{
			FILL_MODE_ALTERNATE = 0,
			FILL_MODE_WINDING = 1,
			FILL_MODE_FORCE_DWORD = -1
		};

		enum class FIGURE_BEGIN
		{
			FIGURE_BEGIN_FILLED = 0,
			FIGURE_BEGIN_HOLLOW = 1,
			FIGURE_BEGIN_FORCE_DWORD = -1
		};

		enum class FIGURE_END
		{
			FIGURE_END_OPEN = 0,
			FIGURE_END_CLOSED = 1,
			FIGURE_END_FORCE_DWORD = -1
		};

        enum class SWEEP_DIRECTION
        {
            SWEEP_DIRECTION_COUNTER_CLOCKWISE = 0,
            SWEEP_DIRECTION_CLOCKWISE = 1,
            SWEEP_DIRECTION_FORCE_DWORD = -1
        };

        enum class ARC_SIZE
        {
            ARC_SIZE_SMALL = 0,
            ARC_SIZE_LARGE = 1,
            ARC_SIZE_FORCE_DWORD = -1
        };

	public:
        ref class BezierSegment
        {
        private:
            PointF pos1, pos2, pos3;

        public:
            BezierSegment() {}

            BezierSegment(PointF p1, PointF p2, PointF p3)
                : pos1(p1), pos2(p2), pos3(p3) {}

        public:
            property PointF Point1 {
                PointF get() { return this->pos1; }
                void set(PointF pos) { this->pos1 = pos; }
            }

            property PointF Point2 {
                PointF get() { return this->pos2; }
                void set(PointF pos) { this->pos2 = pos; }
            }

            property PointF Point3 {
                PointF get() { return this->pos3; }
                void set(PointF pos) { this->pos3 = pos; }
            }
        };

        ref class ArcSegment
        {
        private:
            PointF  point;
            SizeF   size;
            float   rotation;
            SWEEP_DIRECTION sweep;
            ARC_SIZE        arc;

        public:
            ArcSegment() {}

            ArcSegment(PointF point, SizeF size, float rotationAngle, SWEEP_DIRECTION sweepDirection, ARC_SIZE arcSize)
                : point(point), size(size), rotation(rotationAngle), sweep(sweepDirection), arc(arcSize) {}

        public:
            property PointF Point {
                PointF get() { return this->point; }
                void set(PointF pos) { this->point = pos; }
            }

            property SizeF Size {
                SizeF get() { return this->size; }
                void set(SizeF sz) { this->size = sz; }
            }

            property float RotationAngle {
                float get() { return this->rotation; }
                void set(float rotation) { this->rotation = rotation; }
            }

            property SWEEP_DIRECTION SweepDirection {
                SWEEP_DIRECTION get() { return this->sweep; }
                void set(SWEEP_DIRECTION rotation) { this->sweep = rotation; }
            }

            property ARC_SIZE ArcSize {
                ARC_SIZE get() { return this->arc; }
                void set(ARC_SIZE rotation) { this->arc = rotation; }
            }
        };

		ref class GeometrySink
			: IDisposable
		{
		private:
			ID2D1GeometrySink * sink;

		internal:
			GeometrySink(ID2D1GeometrySink * sink) 
				: sink(sink)
			{}

			~GeometrySink() {
				if (this->sink != NULL) {
					this->sink->Close();
					this->sink->Release();
					this->sink = NULL;
				}
			}

			!GeometrySink() {
				this->~GeometrySink();
			}

		public:
			void SetFillMode(FILL_MODE mode)
			{
				this->sink->SetFillMode((D2D1_FILL_MODE)mode);
			}

			void BeginFigure(PointF pos, FIGURE_BEGIN begin)
			{
				this->sink->BeginFigure(D2D1::Point2F(pos.X, pos.Y), (D2D1_FIGURE_BEGIN)begin);
			}

			void AddLines(System::Collections::Generic::IEnumerable<PointF>^ points)
			{
                std::vector<D2D1_POINT_2F> pos;
                for each (PointF^ p in points) {
                    pos.push_back(D2D1::Point2F(p->X, p->Y));
                }
                this->sink->AddLines(pos.data(), pos.size());
			}

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

            void AddBezier(PointF pos1, PointF pos2, PointF pos3)
            {
                D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                    D2D1::Point2F(pos1.X, pos1.Y),
                    D2D1::Point2F(pos2.X, pos2.Y),
                    D2D1::Point2F(pos3.X, pos3.Y)
                );
                this->sink->AddBezier(seg);
            }

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
                this->sink->AddBeziers(segs.data(), segs.size());
            }

			void EndFigure(FIGURE_END end)
			{
				this->sink->EndFigure((D2D1_FIGURE_END)end);
			}
		};

	private:
		ID2D1PathGeometry * geometry;

	public:
		VisualResourceOfPathGeometry(String ^ name, ID2D1Factory * factory)
			: VisualResource(name)
		{
			ID2D1PathGeometry * geo;
			HRESULT hr = factory->CreatePathGeometry(&geo);
			if (SUCCEEDED(hr)) {
				this->geometry = geo;
			}
			else {
				throw gcnew ApplicationException("error");
			}
		}

		~VisualResourceOfPathGeometry() {
		}

	public:
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

		VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) override {
			return gcnew VisualResourceEntity2D(this, this->geometry, true);
		}
	};
}
