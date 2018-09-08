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
        /// <summary>コンストラクタ。</summary>
        /// <param name="name">リソース名。</param>
		VisualResource(String ^ name)
			: name(name)
		{}

        /// <summary>デストラクタ。</summary>
		virtual ~VisualResource() {}

        /// <summary>ファイナライザ。</summary>
		!VisualResource() {
			this->~VisualResource();
		}

	public:
        /// <summary>リソースを取得する。</summary>
		property String ^ Name {
			String ^ get() { return this->name; }
		}

	public:
        /// <summary>等価判定を行う。</summary>
        /// <param name="obj">比較対象。</param>
        /// <return>等しければ真。</return>
		bool Equals(Object ^ obj) override {
			if (this->GetType()->IsInstanceOfType(obj)) {
				return this->name == ((VisualResource^)obj)->name;
			}
			else {
				return false;
			}
		}

        /// <summary>ハッシュコードを取得する。</summary>
        /// <return>ハッシュコード値。</return>
		int GetHashCode() override {
			return this->name->GetHashCode();
		}

	internal:
        /// <summary>リソースを実体に変換する。</summary>
        /// <param name="name">レンダーターゲット。</param>
        /// <return>リソース実体。</return>
		virtual VisualResourceEntity ^ ChangeEntity(ID2D1DCRenderTarget * renderTarget) {
			return nullptr;
		}
	};
}

