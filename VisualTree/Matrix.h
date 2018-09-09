#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

namespace VisualTree
{
    /// <summary>座標変換マトリクス。</summary>
    public value class Matrix
    {
    private:
        // 変換値
        float _11, _12;
        float _21, _22;
        float _31, _32;

    public:
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
    };
}
