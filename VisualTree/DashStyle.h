#pragma once

namespace VisualTree
{
    /// <summary>����B</summary>
    public enum class DashStyle
    {
        /// <summary>�\���b�h�B</summary>
        DASH_STYLE_SOLID = 0,

        /// <summary>�����B</summary>
        DASH_STYLE_DASH = 1,

        /// <summary>�_���B</summary>
        DASH_STYLE_DOT = 2,

        /// <summary>��_�����B</summary>
        DASH_STYLE_DASH_DOT = 3,

        /// <summary>��_�����B</summary>
        DASH_STYLE_DASH_DOT_DOT = 4,

        /// <summary>�J�X�^������B</summary>
        DASH_STYLE_CUSTOM = 5,

        /// <summary>�����l�B</summary>
        DASH_STYLE_FORCE_DWORD = -1
    };
}

