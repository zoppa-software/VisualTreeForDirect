#pragma once

namespace VisualTree
{
    /// <summary>�摜���g��k���܂��͉�]�����Ƃ��Ɏg�p�����A���S���Y�����w�肵�܂��B�Œ�掿�̉摜���o�͂���܂��B</summary>
    public enum class BitmapInterpolationMode
    {
        /// <summary>�ł��߂���_���T���v�����O���A���̐��m�ȐF���g�p���܂��B</summary>
        INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR = 0,

        /// <summary>4�_�T���v���Ɛ��`��Ԃ��g�p���܂��B</summary>
        INTERPOLATION_MODE_DEFINITION_LINEAR = 1,

        /// <summary>��Ԃ�16�T���v����3���J�[�l�����g�p���܂��B</summary>
        INTERPOLATION_MODE_DEFINITION_CUBIC = 2,

        /// <summary>1�̃s�N�Z������4�̐��`�T���v�����g�p���āA�ǍD�ȃG�b�W�A���`�G�C���A�V���O���������܂��B���̃��[�h�́A�s�N�Z���������Ȃ��摜�ŏ��ʂ��k������̂ɓK���Ă��܂��B</summary>
        INTERPOLATION_MODE_DEFINITION_MULTI_SAMPLE_LINEAR = 3,

        /// <summary>�ٕ����t�B���^�����O���g�p���āA�r�b�g�}�b�v�̕ό`���ꂽ�`��ɏ]���ăp�^�[�����T���v�����O���܂��B</summary>
        INTERPOLATION_MODE_DEFINITION_ANISOTROPIC = 4,

        /// <summary>�ϊ��}�g���N�X�Ƀ_�E���X�P�[�����O���܂܂�Ă���ꍇ�A�σT�C�Y�̍��i���L���[�r�b�N�J�[�l�����g�p���ĉ摜�̃v���X�P�[�������s���܂��B���ɁA�ŏI�o�͂�3����ԃ��[�h���g�p���܂��B</summary>
        INTERPOLATION_MODE_DEFINITION_HIGH_QUALITY_CUBIC = 5,

        /// <summary>��`��B</summary>
        INTERPOLATION_MODE_DEFINITION_FANT = 6,

        /// <summary>�~�b�v�}�b�v���j�A�B</summary>
        INTERPOLATION_MODE_DEFINITION_MIPMAP_LINEAR = 7,

        /// <summary>�ߐڋߗ׃t�B���^�����O�B �ł��߂��s�N�Z���܂��͍ł��߂��_�̃T���v�����O�Ƃ��Ă΂�܂��B</summary>
        BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR = INTERPOLATION_MODE_DEFINITION_NEAREST_NEIGHBOR,

        /// <summary>���`�t�B���^�����O�B</summary>
        BITMAP_INTERPOLATION_MODE_LINEAR = INTERPOLATION_MODE_DEFINITION_LINEAR,

        /// <summary>�����l�B</summary>
        BITMAP_INTERPOLATION_MODE_FORCE_DWORD = -1,
    };
}