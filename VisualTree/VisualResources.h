#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include "VisualResource.h"
#include "VisualResourceEntity.h"

using namespace System;
using namespace System::Collections::Generic;

namespace VisualTree
{
    /// <summary>リソース・コレクション。</summary>
	public ref class VisualResources sealed
	{
    private:
        /// <summary>リソース・テーブル。</summary>
        Dictionary<String ^, VisualResourceEntity ^>^ items;

    public:
        /// <summary>登録しているリソース数を取得する。</summary>
        /// <return>リソース数。</return>
        property int Count
        {
            int get() {
                return this->items->Count;
            }
        }

        /// <summary>名前を指定してリソースを取得する。</summary>
        /// <param name="name">リソース名。</param>
        /// <return>リソース。</return>
        property VisualResourceEntity ^ default[String^]
        {
            VisualResourceEntity ^ get(String^ name) {
                VisualResourceEntity ^ val;
                return (this->items->TryGetValue(name, val) ? val : nullptr);
            }
        }

        /// <summary>リソース名を列挙する。</summary>
        property Dictionary<String ^, VisualResourceEntity ^>::KeyCollection ^ Keys
        {
            Dictionary<String ^, VisualResourceEntity ^>::KeyCollection ^ get() {
                return this->items->Keys;
            }
        }

        /// <summary>リソースを列挙する。</summary>
        property Dictionary<String ^, VisualResourceEntity ^>::ValueCollection ^ Values 
        {
            Dictionary<String ^, VisualResourceEntity ^>::ValueCollection ^ get() {
                return this->items->Values;
            }
        }

	public:
        /// <summary>コンストラクタ。</summary>
        VisualResources()
        {
            this->items = gcnew Dictionary<String ^, VisualResourceEntity ^>();
        }

	public:
        /// <summary>全てのリソースを削除する。</summary>
        void Clear()
        {
            this->items->Clear();
        }

    internal:
        /// <summary>リソースを追加する。</summary>
        /// <param name="name">リソース名。</param>
        /// <param name="resource">追加するリソース。</param>
        void Add(String ^ name, VisualResourceEntity ^ resource)
        {
            this->items->Add(name, resource);
        }
	};
}