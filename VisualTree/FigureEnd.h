#pragma once

namespace VisualTree
{
    /// <summary>�}���J���Ă��邩���Ă��邩�������܂��B</summary>
    public enum class FigureEnd
    {
        /// <summary>�}�͊J���Ă��܂��B</summary>
        FIGURE_END_OPEN = 0,

        /// <summary>�}�͕��Ă��܂��B</summary>
		FIGURE_END_CLOSED = 1,

        /// <summary>�����l�B</summary>
		FIGURE_END_FORCE_DWORD = -1
    };
}