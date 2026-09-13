#include <RHI/IPixelShader.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace Engine
{
	class D3D11PixelShader : public IPixelShader
	{
	public:
		D3D11PixelShader() = default;
		~D3D11PixelShader() override;

		bool Create(void* nativeDevice, std::wstring shaderSourcePath, std::string entryPoint) override;
		void Destroy() override;

		void* GetShaderPointer() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	};
}