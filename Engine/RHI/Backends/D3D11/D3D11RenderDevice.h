#pragma once

#include <RHI/IRenderDevice.h>
#include <RHI/Backends/D3D11/D3D11RenderContext.h>

#include <memory>
#include <wrl/client.h>
#include <d3d11.h>
#include <dxgi.h>

namespace Engine
{
	class D3D11RenderDevice final : public IRenderDevice
	{
	public:
		D3D11RenderDevice() = default;
		~D3D11RenderDevice() override;

		bool Initialize(const RenderDeviceDesc& desc) override;
		void Shutdown() override;
		IRenderContext* GetContext() override;

		void Resize(int width, int height) override;

	private:
		bool CreateBackBuffer();
		void ReleaseBackBuffer();

		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immediateContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

		std::unique_ptr<D3D11RenderContext> m_context;

		HWND m_hwnd = nullptr;
		int m_width = 0;
		int m_height = 0;
	};
}