#pragma once
#include <RHI/IRenderContext.h>
#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	class D3D11RenderContext : public IRenderContext
	{
	public:
		D3D11RenderContext(
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
			IDXGISwapChain* swapChain,
			ID3D11RenderTargetView* backBufferRTV
		);

		~D3D11RenderContext() override;

		void Clear(float r, float g, float b, float a) override;
		void Present() override;

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context;

		IDXGISwapChain* m_swapChain = nullptr;
		ID3D11RenderTargetView* m_backBufferRTV = nullptr;
	};
}