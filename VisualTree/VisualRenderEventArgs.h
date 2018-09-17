#pragma once
#include "VisualResources.h"
#include "VisualRenderTarget.h"

namespace VisualTree
{
    using namespace System;

    /// <summary>�`��C�x���g�I�u�W�F�N�g�B</summary>
    public ref class VisualRenderEventArgs sealed
        : EventArgs
    {
    private:
        // �`��Ώ�
        VisualRenderTarget render;

        // ���\�[�X�R���N�V����
        VisualResources ^ resources;

    public:
        /// <summary>�`��ΏۃC���X�^���X���擾����B</summary>
        property VisualRenderTarget RenderTarget {
            VisualRenderTarget get() { return this->render; }
        }

        /// <summary>���\�[�X�R���N�V�������擾����B</summary>
        property VisualResources ^ Resources {
            VisualResources ^ get() { return this->resources; }
        }

    public:
    	/// <summary>�R���X�g���N�^�B</summary>
	    /// <param name="renderTarget">�����_�����O�^�[�Q�b�g�B</param>
        /// <param name="resources">���\�[�X�R���N�V�����B</param>
        VisualRenderEventArgs(VisualRenderTarget renderTarget, VisualResources ^ resources)
            : render(renderTarget), resources(resources)
        {}
    };
}
