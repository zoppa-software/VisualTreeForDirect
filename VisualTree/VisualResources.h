#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"
#include "VisualResourceEntity.h"

namespace VisualTree
{
    using namespace System;
    using namespace System::Collections::Generic;

    /// <summary>���\�[�X�E�R���N�V�����B</summary>
	public ref class VisualResources sealed
	{
    private:
        /// <summary>���\�[�X�E�e�[�u���B</summary>
        Dictionary<String ^, VisualResourceEntity ^>^ items;

    public:
        /// <summary>�o�^���Ă��郊�\�[�X�����擾����B</summary>
        /// <return>���\�[�X���B</return>
        property int Count
        {
            int get() {
                return this->items->Count;
            }
        }

        /// <summary>���O���w�肵�ă��\�[�X���擾����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�B</return>
        property VisualResourceEntity ^ default[String^]
        {
            VisualResourceEntity ^ get(String^ name) {
                VisualResourceEntity ^ val;
                return (this->items->TryGetValue(name, val) ? val : nullptr);
            }
        }

        /// <summary>���\�[�X����񋓂���B</summary>
        property Dictionary<String ^, VisualResourceEntity ^>::KeyCollection ^ Keys
        {
            Dictionary<String ^, VisualResourceEntity ^>::KeyCollection ^ get() {
                return this->items->Keys;
            }
        }

        /// <summary>���\�[�X��񋓂���B</summary>
        property Dictionary<String ^, VisualResourceEntity ^>::ValueCollection ^ Values 
        {
            Dictionary<String ^, VisualResourceEntity ^>::ValueCollection ^ get() {
                return this->items->Values;
            }
        }

	public:
        /// <summary>�R���X�g���N�^�B</summary>
        VisualResources()
        {
            this->items = gcnew Dictionary<String ^, VisualResourceEntity ^>();
        }

	public:
        /// <summary>�S�Ẵ��\�[�X���폜����B</summary>
        void Clear()
        {
            this->items->Clear();
        }

        /// <summary>�w�薼�̃��\�[�X��ێ����Ă�����^��Ԃ��B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <return>���\�[�X�������Ă�����^�B</return>
        bool HasResource(String^ name)
        {
            return this->items->ContainsKey(name);
        }

    internal:
        /// <summary>���\�[�X��ǉ�����B</summary>
        /// <param name="name">���\�[�X���B</param>
        /// <param name="resource">�ǉ����郊�\�[�X�B</param>
        void Add(String ^ name, VisualResourceEntity ^ resource)
        {
            this->items->Add(name, resource);
        }
	};
}