#include <RHI/RenderDeviceFactory.h>
#include <RHI/DX11/D3D11RenderDevice.h>

namespace Engine
{
	IRenderDevice* FactoryCreateRenderDevice(const RenderDeviceDesc& desc)
	{
#ifdef _WIN32
		D3D11RenderDevice* device = new D3D11RenderDevice();

		if (!device->Initialize(desc.hwnd, desc.width, desc.height))
		{
			delete device;
			return nullptr;
		}


		return device;

#else
		return nullptr;
#endif
	}
}