#include <RHI/DX11/D3D11RenderDevice.h>
#include <wrl/client.h>

namespace Engine
{
	D3D11RenderDevice::D3D11RenderDevice()
	{

	}

	bool D3D11RenderDevice::Initialize(void* hwnd, int width, int height)
	{
		DXGI_SWAP_CHAIN_DESC scd{};
		scd.BufferCount = 2;
		scd.BufferDesc.Width = width;
		scd.BufferDesc.Height = height;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = static_cast<HWND>(hwnd);
		scd.SampleDesc.Count = 1;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0,
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&scd,
			&m_swapChain,
			&m_device,
			nullptr,
			&m_immediateContext
		);

		if (FAILED(hr))
		{
			return false;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

		hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);

		if (FAILED(hr))
		{
			return false;
		}

		hr = m_device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_backBufferRTV);

		if (FAILED(hr))
		{
			return false;
		}

		m_context = std::make_unique<D3D11RenderContext>(m_immediateContext, m_swapChain.Get(), m_backBufferRTV.Get());

		return true;
	}

	IRenderContext* D3D11RenderDevice::GetContext()
	{
		return m_context.get();
	}

	void D3D11RenderDevice::Resize(int width, int height)
	{
		//TODO: Implement resize logic
		/* Resize SwapChain and its resources
		   Release old resource
		   Initialize new ones  */
	}

	void D3D11RenderDevice::Shutdown()
	{
		m_context.reset();
		m_backBufferRTV.Reset();
		m_swapChain.Reset();
		m_immediateContext.Reset();
		m_device.Reset();
	}

	D3D11RenderDevice::~D3D11RenderDevice()
	{
		Shutdown();
	}
}