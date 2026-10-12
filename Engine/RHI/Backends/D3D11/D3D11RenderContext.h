#pragma once

#include <RHI/IRenderContext.h>

#include <wrl/client.h>
#include <d3d11.h>
#include <dxgi.h>

namespace Engine
{
	class D3D11RenderContext final : public IRenderContext
	{
	public:
		D3D11RenderContext(
			ID3D11DeviceContext* deviceContext,
			IDXGISwapChain* swapChain,
			ID3D11RenderTargetView* renderTargetView,
			int width,
			int height
		);

		bool BeginFrame(float r, float g, float b, float a) override;
		bool Present() override;
		void SetRenderTarget(ID3D11RenderTargetView* renderTargetView, int width, int height);

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_deviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		int m_width = 0;
		int m_height = 0;
	};
}