#pragma once

using namespace System::Drawing;

namespace VisualTree
{
    /// <summary>�ȉ~�̒��S�_�AX���a�A����� Y���a���i�[���܂��B</summary>
    public value class Ellipse
    {
    private:
        // �ȉ~�̒��S�_
        PointF  point;

        // �ȉ~��X���a
        float   radiusX;

        // �ȉ~��Y���a
        float   radiusY;

    public:
        /// <summary>�ȉ~�̒��S�_��ݒ�A�擾����B</summary>
        property PointF CenterPoint {
            PointF get() { return this->point; }
            void set(PointF value) { this->point = value; }
        }

        /// <summary>�ȉ~��X���a��ݒ�A�擾����B</summary>
        property float RadiusX {
            float get() { return this->radiusX; }
            void set(float value) { this->radiusX = value; }
        }

        /// <summary>�ȉ~��Y���a��ݒ�A�擾����B</summary>
        property float RadiusY {
            float get() { return this->radiusY; }
            void set(float value) { this->radiusY = value; }
        }

    public:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="point">�ȉ~�̒��S�_�B</param>
        /// <param name="radiusX">�ȉ~��X���a�B</param>
        /// <param name="radiusY">�ȉ~��Y���a�B</param>
        Ellipse(PointF point, float radiusX, float radiusY)
            : point(point), radiusX(radiusX), radiusY(radiusY)
        {}
    };
}

