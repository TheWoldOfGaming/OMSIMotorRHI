#pragma once
#include <RHI/IVertexBuffer.h>
#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	class D3D11VertexBuffer : public IVertexBuffer
	{
	public:
		D3D11VertexBuffer(ID3D11Device* device);
		~D3D11VertexBuffer() override;

		bool Create(const VertexBufferDesc& desc) override;
		void Destroy() override;

		void* GetNativeBuffer() const override;

		size_t GetVertexCount() const override;

	private:
		size_t m_vertexCount;
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
		ID3D11Device* m_device;
	};
}