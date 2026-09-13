#include <RHI/VertexBufferFactory.h>
#include <d3d11.h>
#include <RHI/DX11/D3D11VertexBuffer.h>

namespace Engine
{
	IVertexBuffer* FactoryCreateVertexBuffer(const VertexBufferDesc& desc, IRenderDevice* device)
	{
#ifdef _WIN32
        ID3D11Device* d3dDevice = static_cast<ID3D11Device*>(device->GetNativeDevice());

        D3D11VertexBuffer* buffer = new D3D11VertexBuffer(d3dDevice);

        if (!buffer->Create(desc))
        {
            delete buffer;
            return nullptr;
        }

        return buffer;
#else
        return nullptr;
#endif
	}
}