#pragma once
#include "VisualResources.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Collections::Generic;

    /// <summary>���\�[�X�쐬�C�x���g�I�u�W�F�N�g�B</summary>
    public ref class VisualResourceEventArgs
        : EventArgs
    {
    private:
        // ���\�[�X�R���N�V����
        List<VisualResource ^>^ srcres;

    public:
        /// <summary>���\�[�X�R���N�V�������擾����B</summary>
        property List<VisualResource ^>^ Resources {
            List<VisualResource ^>^ get() { return this->srcres; }
        }

    public:
    	/// <summary>�R���X�g���N�^�B</summary>
        /// <param name="srcres">���\�[�X�R���N�V�����B</param>
        VisualResourceEventArgs(List<VisualResource ^>^ srcres)
            : srcres(srcres)
        {}
    };
}