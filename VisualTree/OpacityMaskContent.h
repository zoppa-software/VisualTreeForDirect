#pragma once

namespace VisualTree
{
    /// <summary>�s�����}�X�N�̓��e���w�肵�܂��B</summary>
    public enum class OpacityMaskContent
    {
        /// <summary>�s�����x�}�X�N�ɂ̓O���t�B�b�N�X���܂܂�Ă��܂��B�s�����x�}�X�N�̓K���} 2.2 �̐F��ԂŃu�����h����܂��B</summary>
        OPACITY_MASK_CONTENT_GRAPHICS = 0,
    
        /// <summary>�s�����x�}�X�N�ɂ� GDI �ȊO�̃e�L�X�g���܂܂�Ă��܂��B�u�����h�Ɏg�p�����K���}��Ԃ́A�����_�[ �^�[�Q�b�g�̃e�L�X�g �����_�����O �p�����[�^�[����擾����܂��B</summary>
        OPACITY_MASK_CONTENT_TEXT_NATURAL = 1,
    
        /// <summary>�s�����x�}�X�N�ɂ́AGDI �݊������_�����O ���[�h���g�p���ă����_�����O�����e�L�X�g���܂܂�Ă��܂��B�s�����x�}�X�N�́AGDI �����_�����O�̃K���}���g�p���ău�����h����܂��B</summary>
        OPACITY_MASK_CONTENT_TEXT_GDI_COMPATIBLE = 2,

        /// <summary>�����l�B</summary>
        OPACITY_MASK_CONTENT_FORCE_DWORD = -1
    };
}