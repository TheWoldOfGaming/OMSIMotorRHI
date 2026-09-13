#pragma once
#include <Core/Common.h>

namespace Engine
{
	class IVertexBuffer
	{
	public:
		virtual ~IVertexBuffer() = default;
		
		virtual bool Create(const VertexBufferDesc& desc) = 0;
		virtual void Destroy() = 0;

		virtual void* GetNativeBuffer() const = 0;

		virtual size_t GetVertexCount() const = 0;
	};
}