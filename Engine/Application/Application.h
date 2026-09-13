#pragma once
#include <memory>
#include <Platform/IWindow.h>
#include <Platform/WindowFactory.h>

#include <RHI/IRenderDevice.h>
#include <RHI/IVertexBuffer.h>
#include <RHI/IVertexShader.h>
#include <RHI/IPixelShader.h>
#include <RHI/IInputLayout.h>

#include <RHI/RenderDeviceFactory.h>
#include <RHI/VertexBufferFactory.h>
#include <RHI/VertexShaderFactory.h>
#include <RHI/PixelShaderFactory.h>
#include <RHI/InputLayoutFactory.h>


namespace Engine
{
	class Application
	{
	public:
		Application();
		~Application();

		bool Initialize();
		void Run();
		void Shutdown();

	private:
		std::unique_ptr<IWindow> m_window;
		std::unique_ptr<IRenderDevice> m_renderDevice;
		std::unique_ptr<IVertexBuffer> m_vertexBuffer;
		std::unique_ptr<IVertexShader> m_vertexShader;
		std::unique_ptr<IPixelShader> m_pixelShader;
		std::unique_ptr<IInputLayout> m_inputLayout;
	};
}