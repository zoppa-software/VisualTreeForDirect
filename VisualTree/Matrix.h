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
        /// <summary>無変換のマトリクスを取得する。</summary>
        /// <return>マトリクス。</return>
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

        /// <summary>マトリクスをDirect2D用のマトリクスに変換する。</summary>
        /// <return>マトリクス。</return>
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

        /// <summary>移動マトリクスを取得する。</summary>
        /// <param name="size">移動量。</param>
        /// <return>マトリクス。</return>
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

        /// <summary>移動マトリクスを取得する。</summary>
        /// <param name="x">X移動量。</param>
        /// <param name="y">Y移動量。</param>
        /// <return>マトリクス。</return>
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
