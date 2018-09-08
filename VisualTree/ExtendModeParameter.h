#pragma once

namespace VisualTree
{
    /// <summary>�z�u���@���w�肷��B</summary>
    public enum class ExtendModeParameter
    {
        /// <summary>�T���v���|�C���g���G�b�W�ɃN�����v���邱�Ƃɂ��A�\�[�X�̃G�b�W���g�����܂��B</summary>
        EXTEND_MODE_CLAMP = 0,

        /// <summary>�x�[�X�^�C���͕ϊ����ꂸ�ɕ`�悳��A�c��̓x�[�X�^�C�����J��Ԃ����Ƃœh��Ԃ���܂��B</summary>
        EXTEND_MODE_WRAP = 1,

        /// <summary>�܂�Ԃ��Ɠ����ł����A��փ^�C�������]���܂��B�x�[�X�^�C���͕ό`���ꂸ�ɕ`�悳��܂��B</summary>
        EXTEND_MODE_MIRROR = 2,

        /// <summary>�����l�B</summary>
        EXTEND_MODE_FORCE_DWORD = -1
    };
}
