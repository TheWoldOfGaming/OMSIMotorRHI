#include <RHI/RenderDeviceFactory.h>
#include <RHI/IRenderDevice.h>

#include <RHI/Backends/D3D11/D3D11RenderDevice.h>


namespace Engine
{
	std::unique_ptr<IRenderDevice> CreateRenderDevice()
	{
		return std::make_unique<D3D11RenderDevice>();
	}
}