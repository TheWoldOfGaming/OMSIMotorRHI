#pragma once
#include <memory>

namespace Engine
{
	class IRenderDevice;

	std::unique_ptr<IRenderDevice> CreateRenderDevice();
}