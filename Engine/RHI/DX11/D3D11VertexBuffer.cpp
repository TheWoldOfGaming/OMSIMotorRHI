#include <RHI/DX11/D3D11VertexBuffer.h>
#include <RHI/DX11/D3D11RenderDevice.h>
#include <Core/Logger.h>

namespace Engine
{
	D3D11VertexBuffer::D3D11VertexBuffer(ID3D11Device* device)
		: m_vertexCount(0), m_device(device)
	{
	}

	bool D3D11VertexBuffer::Create(const VertexBufferDesc& desc)
	{
		m_vertexCount = desc.vertexCount;
		D3D11_BUFFER_DESC vbd{};
		vbd.ByteWidth = static_cast<UINT>(sizeof(Vertex) * desc.vertexCount);
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		

		D3D11_SUBRESOURCE_DATA sbd{};
		sbd.pSysMem = desc.vertices;
		sbd.SysMemPitch = 0;

		HRESULT hr = m_device->CreateBuffer(
			&vbd,
			&sbd,
			&m_vertexBuffer
		);

		if (FAILED(hr))
		{
			Logger::Error(LogCategory::DX3D, "Failed to create Vertex Buffer");
			return false;
		}

		return true;
	}

	void D3D11VertexBuffer::Destroy()
	{
		m_vertexBuffer.Reset();
	}

	void* D3D11VertexBuffer::GetNativeBuffer() const
	{
		return m_vertexBuffer.Get();
	}

	size_t D3D11VertexBuffer::GetVertexCount() const
	{
		return m_vertexCount;
	}

	D3D11VertexBuffer::~D3D11VertexBuffer()
	{

	}
}