#include <RHI/DX11/D3D11RenderContext.h>

namespace Engine
{
	D3D11RenderContext::D3D11RenderContext(
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
		IDXGISwapChain* swapChain,
		ID3D11RenderTargetView* backBufferRTV
	)
		:
		m_context(context),
		m_swapChain(swapChain),
		m_backBufferRTV(backBufferRTV)
	{
	}

	D3D11RenderContext::~D3D11RenderContext()
	{
	}

	void D3D11RenderContext::Clear(float r, float g, float b, float a)
	{
		const float clearColor[4] = { r, g, b, a };
		m_context->ClearRenderTargetView(m_backBufferRTV, clearColor);
	}

	void D3D11RenderContext::Present()
	{
		m_swapChain->Present(1, 0);
	}
}