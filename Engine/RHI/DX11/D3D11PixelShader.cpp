#include <Core/Logger.h>

#include <RHI/DX11/D3D11PixelShader.h>

#include <d3dcompiler.h>

namespace Engine
{
	bool D3D11PixelShader::Create(void* nativeDevice, std::wstring shaderSourcePath, std::string entryPoint)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> byteCodeBlob;

		HRESULT hr = D3DCompileFromFile(
			shaderSourcePath.c_str(),
			nullptr,
			nullptr,
			entryPoint.c_str(),
			"ps_5_0",
			0,
			0,
			&byteCodeBlob,
			&errorBlob
		);

		if (FAILED(hr))
		{
			if (errorBlob)
			{
				Logger::Error(LogCategory::DX3D, static_cast<const char*>(errorBlob->GetBufferPointer()));
			}
			else
			{
				Logger::Error(LogCategory::DX3D, "Failed to compile Pixel Shader bytecode.");
			}
			return false;
		}

		ID3D11Device* device = static_cast<ID3D11Device*>(nativeDevice);

		hr = device->CreatePixelShader(
			byteCodeBlob->GetBufferPointer(),
			byteCodeBlob->GetBufferSize(),
			nullptr,
			&m_pixelShader
		);

		if (FAILED(hr))
		{
			Logger::Error(LogCategory::DX3D, "Failed to create Pixel Shader from bytecode.");
			return false;
		}

		return true;
	}

	void D3D11PixelShader::Destroy()
	{
		m_pixelShader.Reset();
	}

	D3D11PixelShader::~D3D11PixelShader()
	{
		Destroy();
	}

	void* D3D11PixelShader::GetShaderPointer() const
	{
		return m_pixelShader.Get();
	}
}