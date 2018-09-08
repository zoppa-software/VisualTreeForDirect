#pragma once

namespace VisualTree
{
    /// <summary>�R�[�i�[�����B</summary>
    public enum class LineJoin
    {
        /// <summary>�ʏ�R�[�i�[�B</summary>
        LINE_JOIN_MITER = 0,

        /// <summary>�ʎ��R�[�i�[�B</summary>
        LINE_JOIN_BEVEL = 1,

        /// <summary>�ۂ߃R�[�i�[�B</summary>
        LINE_JOIN_ROUND = 2,

        /// <summary>���������~�b�g�𒴂��Ȃ��ꍇ�͕W���̊p�x�̒��_�B�������ꍇ�͌X�΂̕t�������_�B</summary>
        LINE_JOIN_MITER_OR_BEVEL = 3,

        /// <summary>�����l�B</summary>
        LINE_JOIN_FORCE_DWORD = -1
    };
}