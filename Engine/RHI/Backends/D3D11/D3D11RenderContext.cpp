#include <RHI/Backends/D3D11/D3D11RenderContext.h>	
#include <Core/Logger.h>

namespace Engine
{
	D3D11RenderContext::D3D11RenderContext(
		ID3D11DeviceContext* deviceContext,
		IDXGISwapChain* swapChain,
		ID3D11RenderTargetView* renderTargetView,
		int width,
		int height
	)
		: m_width(width)
		, m_height(height)
	{
		m_deviceContext = deviceContext;
		m_swapChain = swapChain;
		m_renderTargetView = renderTargetView;
	}

	bool D3D11RenderContext::BeginFrame(
		float r,
		float g,
		float b,
		float a

	)
	{
		if (!m_deviceContext)
		{
			Logger::Error(
				LogCategory::DX3D,
				"BeginFrame failed: D3D11 device context is null."
			);
			return false;
		}

		if (!m_renderTargetView)
		{
			Logger::Error(
				LogCategory::DX3D,
				"BeginFrame failed: render target view is null."
			);
			return false;
		}

		if (m_width <= 0 || m_height <= 0)
		{
			Logger::Error(
				LogCategory::DX3D,
				"BeginFrame failed: invalid viewport dimensions."
			);
			return false;
		}

		ID3D11RenderTargetView* rtv = m_renderTargetView.Get();

		m_deviceContext->OMSetRenderTargets(1, &rtv, nullptr);

		D3D11_VIEWPORT viewport{};
		viewport.Width = static_cast<float>(m_width);
		viewport.Height = static_cast<float>(m_height);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		m_deviceContext->RSSetViewports(1, &viewport);

		const float clearColor[4] = { r, g, b, a };

		m_deviceContext->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);

		return true;
	}

	bool D3D11RenderContext::Present()
	{
		if (!m_swapChain)
			return false;

		const HRESULT hr = m_swapChain->Present(1, 0);

		return SUCCEEDED(hr);
	}

	void D3D11RenderContext::SetRenderTarget(
		ID3D11RenderTargetView* renderTargetView,
		int width,
		int height
	)
	{
		m_renderTargetView = renderTargetView;
		m_width = width;
		m_height = height;
	}
}