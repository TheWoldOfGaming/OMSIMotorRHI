#include <RHI/DX11/D3D11RenderContext.h>
#include <RHI/DX11/D3D11RenderDevice.h>
#include <RHI/IVertexBuffer.h>
#include <RHI/IVertexShader.h>
#include <RHI/IPixelShader.h>

namespace Engine
{
	D3D11RenderContext::D3D11RenderContext(
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> context,
		IDXGISwapChain* swapChain,
		ID3D11RenderTargetView* backBufferRTV,
		D3D11RenderDevice* owningDevice
	)
		:
		m_context(context),
		m_swapChain(swapChain),
		m_backBufferRTV(backBufferRTV),
		m_owningDevice(owningDevice)
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
		m_owningDevice->RefreshBackBufferRTV();
	}

	void D3D11RenderContext::Draw(size_t vertexCount)
	{
		m_context->Draw(static_cast<UINT>(vertexCount), 0);
	}

	void D3D11RenderContext::SetVertexBuffer(IVertexBuffer* buffer)
	{
		auto nativeBuffer = static_cast<ID3D11Buffer*>(buffer->GetNativeBuffer());
		auto stride = static_cast<UINT>(sizeof(Vertex));
		UINT offset = 0;

		m_context->IASetVertexBuffers(0, 1, &nativeBuffer, &stride, &offset);

		m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void D3D11RenderContext::SetVertexShader(IVertexShader* shader)
	{
		ID3D11VertexShader* vShader = static_cast<ID3D11VertexShader*>(shader->GetShaderPointer());

		m_context->VSSetShader(vShader, nullptr, 0);
	}

	void D3D11RenderContext::SetPixelShader(IPixelShader* shader)
	{
		ID3D11PixelShader* pShader = static_cast<ID3D11PixelShader*>(shader->GetShaderPointer());

		m_context->PSSetShader(pShader, nullptr, 0);
	}

	void D3D11RenderContext::SetInputLayout(IInputLayout* layout)
	{
		ID3D11InputLayout* iLayout = static_cast<ID3D11InputLayout*>(layout->GetLayoutPointer());

		m_context->IASetInputLayout(iLayout);
	}
}