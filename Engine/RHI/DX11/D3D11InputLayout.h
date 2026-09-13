#include <RHI/IInputLayout.h>

#include <wrl/client.h>
#include <d3d11.h>

namespace Engine
{
	class D3D11InputLayout : public IInputLayout
	{
	public:
		D3D11InputLayout() = default;
		~D3D11InputLayout() override;

		bool Create(void* nativeDevice, void* shaderByteCode, size_t byteCodeSize) override;
		void Destroy() override;

		void* GetLayoutPointer() const override;

	private:
		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	};
}