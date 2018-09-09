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
    };
}
