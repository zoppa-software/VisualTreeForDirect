#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

namespace VisualTree
{
    /// <summary>���W�ϊ��}�g���N�X�B</summary>
    public value class Matrix
    {
    private:
        // �ϊ��l
        float _11, _12;
        float _21, _22;
        float _31, _32;

    public:
        /// <summary>���ϊ��̃}�g���N�X���擾����B</summary>
        /// <return>�}�g���N�X�B</return>
        static Matrix Identity()
        {
            Matrix res;
            res._11 = 1.f;
            res._12 = 0.f;
            res._21 = 0.f;
            res._22 = 1.f;
            res._31 = 0.f;
            res._32 = 0.f;
            return res;
        }

        /// <summary>�}�g���N�X��Direct2D�p�̃}�g���N�X�ɕϊ�����B</summary>
        /// <return>�}�g���N�X�B</return>
        D2D1_MATRIX_3X2_F Convert()
        {
            return D2D1::Matrix3x2F(
                this->_11,
                this->_12,
                this->_21,
                this->_22,
                this->_31,
                this->_32
            );
        }

        /// <summary>�ړ��}�g���N�X���擾����B</summary>
        /// <param name="size">�ړ��ʁB</param>
        /// <return>�}�g���N�X�B</return>
        static Matrix Translation(SizeF size)
        {
            Matrix res;
            res._11 = 1.f;
            res._12 = 0.f;
            res._21 = 0.f;
            res._22 = 1.f;
            res._31 = size.Width;
            res._32 = size.Height;
            return res;
        }

        /// <summary>�ړ��}�g���N�X���擾����B</summary>
        /// <param name="x">X�ړ��ʁB</param>
        /// <param name="y">Y�ړ��ʁB</param>
        /// <return>�}�g���N�X�B</return>
        static Matrix Translation(float x, float y)
        {
            Matrix res;
            res._11 = 1.f;
            res._12 = 0.f;
            res._21 = 0.f;
            res._22 = 1.f;
            res._31 = x;
            res._32 = y;
            return res;
        }

        static Matrix Rotation(float angle, PointF center)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(center.X, center.Y));

            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        static Matrix Rotation(float angle)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Rotation(angle);
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        static Matrix Scale(float x, float y, PointF center)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(x, y, D2D1::Point2F(center.X, center.Y));
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        static Matrix Scale(float x, float y)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(x, y);
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        static Matrix Scale(SizeF size, PointF center)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(
                                D2D1::SizeF(size.Width, size.Height),
                                D2D1::Point2F(center.X, center.Y));
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        static Matrix Scale(SizeF size)
        {
            Matrix res;
            D2D1::Matrix3x2F max = D2D1::Matrix3x2F::Scale(
                                D2D1::SizeF(size.Width, size.Height));
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }

        static Matrix operator*(Matrix left, Matrix right)
        {
            Matrix res;
            D2D1_MATRIX_3X2_F l = left.Convert();
            D2D1_MATRIX_3X2_F r = right.Convert();
            D2D1_MATRIX_3X2_F max = l * r;
            res._11 = max._11;
            res._12 = max._12;
            res._21 = max._21;
            res._22 = max._22;
            res._31 = max._31;
            res._32 = max._32;
            return res;
        }
    };
}
