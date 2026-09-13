#include <RHI/PixelShaderFactory.h>
#include <RHI/DX11/D3D11PixelShader.h>

#include <d3d11.h>

namespace Engine
{
	IPixelShader* FactoryCreatePixelShader(IRenderDevice* device)
	{
#ifdef _WIN32
		ID3D11Device* d3dDevice = static_cast<ID3D11Device*>(device->GetNativeDevice());

		D3D11PixelShader* pixelShader = new D3D11PixelShader();

		if (!pixelShader->Create(d3dDevice, L"Shaders/BasicPixelShader.hlsl", "PSMain"))
		{
			delete pixelShader;
			return nullptr;
		}

		return pixelShader;

#else
		return nullptr;
#endif
	}
}