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

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
	public ref class VisualResourceOfPathGeometry
		: public VisualResource
	{
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
            SweepDirection sweep;
            ArcSize        arc;

        public:
            ArcSegment() {}

            ArcSegment(PointF point, SizeF size, float rotationAngle, SweepDirection sweepDirection, ArcSize arcSize)
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

            property VisualTree::SweepDirection SweepDirection {
                VisualTree::SweepDirection get() { return this->sweep; }
                void set(VisualTree::SweepDirection rotation) { this->sweep = rotation; }
            }

            property VisualTree::ArcSize ArcSize {
                VisualTree::ArcSize get() { return this->arc; }
                void set(VisualTree::ArcSize rotation) { this->arc = rotation; }
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
			void SetFillMode(FillMode mode)
			{
				this->sink->SetFillMode((D2D1_FILL_MODE)mode);
			}

			void BeginFigure(PointF pos, FigureBegin begin)
			{
				this->sink->BeginFigure(D2D1::Point2F(pos.X, pos.Y), (D2D1_FIGURE_BEGIN)begin);
			}

            void AddLine(float x, float y)
			{
                this->sink->AddLine(D2D1::Point2F(x, y));
			}

            void AddLine(PointF point)
			{
                this->sink->AddLine(D2D1::Point2F(point.X, point.Y));
			}

			void AddLines(System::Collections::Generic::IEnumerable<PointF>^ points)
			{
                std::vector<D2D1_POINT_2F> pos;
                for each (PointF p in points) {
                    pos.push_back(D2D1::Point2F(p.X, p.Y));
                }
                this->sink->AddLines(pos.data(), (UINT32)pos.size());
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
                this->sink->AddBeziers(segs.data(), (UINT32)segs.size());
            }

			void EndFigure(FigureEnd end)
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

    internal:
        ID2D1PathGeometry * GetGeometry() {
            return this->geometry;
        }
	};
}
