#pragma once

namespace VisualTree
{
    /// <summary>���C���[���쐬�I�v�V�����B</summary>
    public enum class LayerOptions
    {
        /// <summary>���̃��C���[�̃e�L�X�g�ł́AClearType �A���`�G�C���A�V���O���g�p���܂���B</summary>
        D2D1_LAYER_OPTIONS_NONE = 0,

        /// <summary>���C���[�� ClearType �e�L�X�g�p�ɐ����������_�����O����܂��B</summary>
        D2D1_LAYER_OPTIONS_INITIALIZE_FOR_CLEARTYPE = 1,

        /// <summary>�����l�B�B</summary>
        D2D1_LAYER_OPTIONS_FORCE_DWORD = -1
    };
}