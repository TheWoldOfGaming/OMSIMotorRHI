#pragma once
#include <RHI/IRenderContext.h>
#include <RHI/IVertexBuffer.h>
#include <RHI/IVertexShader.h>
#include <RHI/IPixelShader.h>
#include <RHI/IInputLayout.h>
#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	class D3D11RenderDevice;

	class D3D11RenderContext : public IRenderContext
	{
	public:
		D3D11RenderContext(
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
			IDXGISwapChain* swapChain,
			ID3D11RenderTargetView* backBufferRTV,
			D3D11RenderDevice* owningDevice
		);

		~D3D11RenderContext() override;

		void Clear(float r, float g, float b, float a) override;
		void Present() override;
		void Draw(size_t vertexCount) override;

		void SetVertexBuffer(IVertexBuffer* buffer) override;
		void SetVertexShader(IVertexShader* shader) override;
		void SetPixelShader(IPixelShader* shader) override;
		void SetInputLayout(IInputLayout* layout) override;

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;

		IDXGISwapChain* m_swapChain = nullptr;
		ID3D11RenderTargetView* m_backBufferRTV = nullptr;

		D3D11RenderDevice* m_owningDevice = nullptr;
	};
}