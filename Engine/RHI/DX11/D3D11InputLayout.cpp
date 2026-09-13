#include <RHI/DX11/D3D11InputLayout.h>
#include <RHI/Vertex.h>

#include <Core/Logger.h>

namespace Engine
{
	bool D3D11InputLayout::Create(void* nativeDevice, void* shaderByteCode, size_t byteCodeSize)
	{
		ID3D11Device* device = static_cast<ID3D11Device*>(nativeDevice);

		D3D11_INPUT_ELEMENT_DESC inputLayout[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 0,							  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, color), D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		HRESULT hr =device->CreateInputLayout(
			inputLayout,
			ARRAYSIZE(inputLayout),
			shaderByteCode,
			byteCodeSize,
			&m_inputLayout
		);

		if (FAILED(hr))
		{
			Logger::Error(LogCategory::DX3D, "Failed to create Input Layout.");
			return false;
		}

		return true;
	}

	void D3D11InputLayout::Destroy()
	{
		m_inputLayout.Reset();
	}

	D3D11InputLayout::~D3D11InputLayout()
	{
		Destroy();
	}

	void* D3D11InputLayout::GetLayoutPointer() const
	{
		return m_inputLayout.Get();
	}
}