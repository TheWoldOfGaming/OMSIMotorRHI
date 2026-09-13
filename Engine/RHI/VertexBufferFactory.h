#pragma once
#include <RHI/IVertexBuffer.h>
#include <RHI/IRenderDevice.h>

namespace Engine
{
	IVertexBuffer* FactoryCreateVertexBuffer(const VertexBufferDesc& desc, IRenderDevice* device);
}