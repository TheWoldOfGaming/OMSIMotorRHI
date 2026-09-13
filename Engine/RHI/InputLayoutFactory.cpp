#include <RHI/InputLayoutFactory.h>
#include <RHI/IVertexShader.h>
#include <RHI/DX11/D3D11InputLayout.h>

#include <d3d11.h>

namespace Engine
{
	IInputLayout* FactoryCreateInputLayout(IRenderDevice* device, IVertexShader* vertexShader)
	{
#ifdef _WIN32
		ID3D11Device* d3dDevice = static_cast<ID3D11Device*>(device->GetNativeDevice());

		void* bytecodeData = nullptr;
		size_t bytecodeSize = 0;
		vertexShader->GetBytecode(bytecodeData, bytecodeSize);

		D3D11InputLayout* inputLayout = new D3D11InputLayout();

		if (!inputLayout->Create(d3dDevice, bytecodeData, bytecodeSize))
		{
			delete inputLayout;
			return nullptr;
		}

		return inputLayout;

#else
		return nullptr;
#endif
	}
}