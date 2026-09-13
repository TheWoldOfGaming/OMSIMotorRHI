#include <RHI/VertexShaderFactory.h>
#include <RHI/DX11/D3D11VertexShader.h>

#include <d3d11.h>

namespace Engine
{
	IVertexShader* FactoryCreateVertexShader(IRenderDevice* device)
	{
#ifdef _WIN32
		ID3D11Device* d3dDevice = static_cast<ID3D11Device*>(device->GetNativeDevice());

		D3D11VertexShader* vertexShader = new D3D11VertexShader();

		if (!vertexShader->Create(d3dDevice, L"Shaders/BasicVertexShader.hlsl", "VSMain"))
		{
			delete vertexShader;
			return nullptr;
		}

		return vertexShader;

#else
		return nullptr;
#endif
	}
}