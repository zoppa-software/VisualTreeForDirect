#pragma once

namespace VisualTree
{
    /// <summary>�ȉ~�̌ʂ��`�悳���������`���܂��B</summary>
    public enum class SweepDirection
    {
        /// <summary>�ʂ͔����v��� (���̊p�x) �����ɕ`�悳��܂��B</summary>
        SWEEP_DIRECTION_COUNTER_CLOCKWISE = 0,

        /// <summary>�ʂ͎��v��� (���̊p�x) �����ɕ`�悳��܂��B</summary>
        SWEEP_DIRECTION_CLOCKWISE = 1,

        /// <summary>�����l�B</summary>
        SWEEP_DIRECTION_FORCE_DWORD = -1
    };
}
