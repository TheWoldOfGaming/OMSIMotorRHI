#pragma once
#include <RHI/IRenderDevice.h>
#include <Core/Common.h>

namespace Engine
{
	IRenderDevice* FactoryCreateRenderDevice(const RenderDeviceDesc& desc);
}