#pragma once
#include <RHI/IRenderDevice.h>
#include <RHI/DX11/D3D11RenderContext.h>
#include <memory>
#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	class D3D11RenderDevice : public IRenderDevice
	{
	public:
		D3D11RenderDevice();
		~D3D11RenderDevice() override;

		bool Initialize(void* hwnd, int width, int height) override;
		void Shutdown() override;

		IRenderContext* GetContext() override;

		void* GetNativeDevice() override;

		void Resize(int width, int height) override;

		void RefreshBackBufferRTV();

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> m_device;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_backBufferRTV;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_immediateContext;

		std::unique_ptr<D3D11RenderContext> m_context;
	};
}