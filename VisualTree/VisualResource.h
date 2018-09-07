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

    /// <summary>リソースクラス。</summary>
	public ref class VisualResource
		: IDisposable
	{
	private:
		/// <summary>リソース名。</summary>
        String ^ name;

	protected:
		VisualResource(String ^ name)
			: name(name)
		{}

		virtual ~VisualResource() {}

		!VisualResource() {
			this->~VisualResource();
		}

	public:
		property String ^ Name {
			String ^ get() { return this->name; }
		}

	public:
		bool Equals(Object ^ obj) override {
			if (this->GetType()->IsInstanceOfType(obj)) {
				return this->name == ((VisualResource^)obj)->name;
			}
			else {
				return false;
			}
		}

		int GetHashCode() override {
			return this->name->GetHashCode();
		}

	internal:
		virtual VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) {
			return nullptr;
		}
	};
}

