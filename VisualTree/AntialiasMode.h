#pragma once

namespace VisualTree
{
    /// <summary>��e�L�X�g�v���~�e�B�u�̃G�b�W�������_�����O������@���L�q���܂��B</summary>
    public enum class AntialiasMode
    {
        /// <summary>�e�v���~�e�B�u�̃G�b�W�́A�����A���`�G�C���A�V���O����܂��B</summary>
        ANTIALIAS_MODE_PER_PRIMITIVE = 0,

        /// <summary>�s�N�Z�����S���W�I���g���Ɋ܂܂��ꍇ�A�e�s�N�Z���������_�����O����܂��B</summary>
        ANTIALIAS_MODE_ALIASED = 1,

        /// <summary>�����l�B</summary>
        ANTIALIAS_MODE_FORCE_DWORD = -1
    };
}