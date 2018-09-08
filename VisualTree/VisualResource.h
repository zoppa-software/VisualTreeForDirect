#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Drawing;

namespace VisualTree
{
    ref class VisualResourceEntity;

    /// <summary>���\�[�X�N���X�B</summary>
	public ref class VisualResource
		: IDisposable
	{
	private:
		/// <summary>���\�[�X���B</summary>
        String ^ name;

	protected:
        /// <summary>�R���X�g���N�^�B</summary>
        /// <param name="name">���\�[�X���B</param>
		VisualResource(String ^ name)
			: name(name)
		{}

        /// <summary>�f�X�g���N�^�B</summary>
		virtual ~VisualResource() {}

        /// <summary>�t�@�C�i���C�U�B</summary>
		!VisualResource() {
			this->~VisualResource();
		}

	public:
        /// <summary>���\�[�X���擾����B</summary>
		property String ^ Name {
			String ^ get() { return this->name; }
		}

	public:
        /// <summary>����������s���B</summary>
        /// <param name="obj">��r�ΏہB</param>
        /// <return>��������ΐ^�B</return>
		bool Equals(Object ^ obj) override {
			if (this->GetType()->IsInstanceOfType(obj)) {
				return this->name == ((VisualResource^)obj)->name;
			}
			else {
				return false;
			}
		}

        /// <summary>�n�b�V���R�[�h���擾����B</summary>
        /// <return>�n�b�V���R�[�h�l�B</return>
		int GetHashCode() override {
			return this->name->GetHashCode();
		}

	internal:
        /// <summary>���\�[�X�����̂ɕϊ�����B</summary>
        /// <param name="name">�����_�[�^�[�Q�b�g�B</param>
        /// <return>���\�[�X���́B</return>
		virtual VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) {
			return nullptr;
		}
	};
}

