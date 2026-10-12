#include <RHI/Backends/D3D11/D3D11RenderDevice.h>

namespace Engine
{
	D3D11RenderDevice::~D3D11RenderDevice()
	{
		Shutdown();
	}

	bool D3D11RenderDevice::Initialize(const RenderDeviceDesc& desc)
	{
		if (!desc.hwnd || desc.width <= 0 || desc.height <= 0)
			return false;

		m_hwnd = static_cast<HWND>(desc.hwnd);
		m_width = desc.width;
		m_height = desc.height;

		UINT flags = 0;

#if defined(_DEBUG)
		flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		DXGI_SWAP_CHAIN_DESC swapChainDesc{};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = static_cast<UINT>(m_width);
		swapChainDesc.BufferDesc.Height = static_cast<UINT>(m_height);
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = m_hwnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			flags,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			m_swapChain.GetAddressOf(),
			m_device.GetAddressOf(),
			nullptr,
			m_immediateContext.GetAddressOf()
		);

		if (FAILED(hr))
		{
			Shutdown();
			return false;
		}

		if (!CreateBackBuffer())
		{
			Shutdown();
			return false;
		}

		m_context = std::make_unique<D3D11RenderContext>(
			m_immediateContext.Get(),
			m_swapChain.Get(),
			m_renderTargetView.Get(),
			m_width,
			m_height
		);

		return true;
	}

	bool D3D11RenderDevice::CreateBackBuffer()
	{
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

		HRESULT hr = m_swapChain->GetBuffer(
			0,
			IID_PPV_ARGS(backBuffer.GetAddressOf())
		);

		if (FAILED(hr))
			return false;

		hr = m_device->CreateRenderTargetView(
			backBuffer.Get(),
			nullptr,
			m_renderTargetView.GetAddressOf()
		);

		return SUCCEEDED(hr);
	}

	void D3D11RenderDevice::ReleaseBackBuffer()
	{
		m_renderTargetView.Reset();
	}

	IRenderContext* D3D11RenderDevice::GetContext()
	{
		return m_context.get();
	}

	void D3D11RenderDevice::Resize(int width, int height)
	{
		// Implemented in the resize step below.
	}

	void D3D11RenderDevice::Shutdown()
	{
		m_context.reset();
		ReleaseBackBuffer();

		m_swapChain.Reset();
		m_immediateContext.Reset();
		m_device.Reset();

		m_hwnd = nullptr;
		m_width = 0;
		m_height = 0;
	}
}