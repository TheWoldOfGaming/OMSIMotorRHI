#pragma once
#include <RHI/IPixelShader.h>
#include <RHI/IRenderDevice.h>

namespace Engine
{
	IPixelShader* FactoryCreatePixelShader(IRenderDevice* device);
}