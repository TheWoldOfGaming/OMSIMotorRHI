#pragma once
#include <RHI/IVertexShader.h>
#include <RHI/IRenderDevice.h>

namespace Engine
{
	IVertexShader* FactoryCreateVertexShader(IRenderDevice* device);
}