#include <Application/Application.h>
#include <Core/Common.h>
#include <RHI/IRenderContext.h>

#include <Core/Logger.h>

namespace Engine
{
	Application::Application()
	{
		Logger::Debug(LogCategory::General, "Application object constructed.");
	}

	Application::~Application()
	{
		Logger::Debug(LogCategory::General, "Application object destroyed.");
	}

	bool Application::Initialize()
	{
		Logger::Initialize("Logs.log");
		Logger::SetLogLevel(LogLevel::Trace);
		Logger::Info(LogCategory::General, "Application initialization started.");
		// Log start

		WindowDesc desc;
		desc.width = 1280;
		desc.height = 720;
		desc.title = L"OMSIEngine Version 1.0";

		Logger::Debug(LogCategory::General, "Creating application window.");

		m_window = std::unique_ptr<IWindow>( FactoryCreateWindow(desc) );

		if (!m_window)
		{
			Logger::Critical(LogCategory::General, "Failed to create window.");
			return false;
		}

		Logger::Info(
			LogCategory::General,
			"Application window created successfully."
		);

		RenderDeviceDesc renderDesc;
		renderDesc.hwnd = m_window->GetNativeHandle();
		renderDesc.width = desc.width;
		renderDesc.height = desc.height;

		Logger::Debug(
			LogCategory::DX3D,
			"Creating render device."
		);

		m_renderDevice = std::unique_ptr<IRenderDevice>(FactoryCreateRenderDevice(renderDesc));

		if (!m_renderDevice)
		{
			Logger::Critical(LogCategory::General, "Failed to create render device.");
			return false;
		}

		Logger::Info(
			LogCategory::DX3D,
			"Render device created successfully."
		);

		// TEMP

		Vertex triangle[3] =
		{
			{ Vec3(0.0f,  0.5f, 0.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f) },  // top, red
			{ Vec3(0.5f, -0.5f, 0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f) },  // bottom-right, green
			{ Vec3(-0.5f, -0.5f, 0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f) },  // bottom-left, blue
		};

		// TEMP END

		VertexBufferDesc vbd;
		vbd.vertexCount = 3;
		vbd.vertices = triangle;

		Logger::Debug(
			LogCategory::DX3D,
			"Creating vertex buffer."
		);

		m_vertexBuffer = std::unique_ptr<IVertexBuffer>(FactoryCreateVertexBuffer(vbd, m_renderDevice.get()));

		if (!m_vertexBuffer)
		{
			Logger::Critical(LogCategory::General, "Failed to create Vertex Buffer.");
			return false;
		}

		Logger::Info(
			LogCategory::DX3D,
			"Vertex buffer created successfully."
		);

		m_vertexShader = std::unique_ptr<IVertexShader>(FactoryCreateVertexShader(m_renderDevice.get()));

		if (!m_vertexShader)
		{
			Logger::Error(LogCategory::General, "Failed to create Vertex Shader.");
			return false;
		}

		Logger::Info(LogCategory::DX3D, "Vertex Shader created successfully.");

		m_pixelShader = std::unique_ptr<IPixelShader>(FactoryCreatePixelShader(m_renderDevice.get()));

		if (!m_pixelShader)
		{
			Logger::Error(LogCategory::General, "Failed to create Pixel Shader.");
			return false;
		}

		Logger::Info(LogCategory::DX3D, "Pixel Shader created successfully.");

		m_inputLayout = std::unique_ptr<IInputLayout>(FactoryCreateInputLayout(m_renderDevice.get(), m_vertexShader.get() ));

		if (!m_inputLayout)
		{
			Logger::Error(LogCategory::General, "Failed to create Input Layout.");
			return false;
		}

		Logger::Info(LogCategory::DX3D, "Input Layout created successfully.");




		Logger::Info(
			LogCategory::General,
			"Application initialization completed successfully."
		);

		return true;
	}

	void Application::Run()
	{
		Logger::Info(
			LogCategory::General,
			"Application main loop started."
		);

		while (!m_window->ShouldClose())
		{
			Logger::Trace(
				LogCategory::Game,
				"Frame started."
			);

			m_window->PumpMessage();

			Logger::Trace(
				LogCategory::Input,
				"Window messages pumped."
			);

			IRenderContext* ctx = m_renderDevice->GetContext();

			if (!ctx)
			{
				Logger::Error(
					LogCategory::DX3D,
					"Failed to acquire render context."
				);

				continue;
			}

			Logger::Trace(
				LogCategory::DX3D,
				"Render context acquired."
			);

			ctx->Clear(0.0f, 0.2f, 0.4f, 1.0f);

			Logger::Trace(
				LogCategory::DX3D,
				"Render target cleared."
			);

			ctx->SetInputLayout(m_inputLayout.get());

			Logger::Trace(
				LogCategory::DX3D,
				"Input Layout set."
			);

			ctx->SetVertexShader(m_vertexShader.get());

			Logger::Trace(
				LogCategory::DX3D,
				"Vertex Shader set."
			);

			ctx->SetPixelShader(m_pixelShader.get());

			Logger::Trace(
				LogCategory::DX3D,
				"Pixel Shader set."
			);

			ctx->SetVertexBuffer(m_vertexBuffer.get());

			Logger::Trace(
				LogCategory::DX3D,
				"Vertex buffer bound."
			);

			ctx->Draw(m_vertexBuffer->GetVertexCount());

			Logger::Trace(
				LogCategory::DX3D,
				"Draw call submitted. Vertex count: 3."
			);

			ctx->Present();

			Logger::Trace(
				LogCategory::DX3D,
				"Frame presented."
			);



			Logger::Trace(
				LogCategory::Game,
				"Frame ended."
			);
		}

		Logger::Info(
			LogCategory::General,
			"Application main loop ended."
		);
	}

	void Application::Shutdown()
	{
		Logger::Info(
			LogCategory::General,
			"Application shutdown started."
		);

		if (m_inputLayout)
		{
			Logger::Debug(
				LogCategory::DX3D,
				"Destroying Input Layout."
			);

			m_inputLayout->Destroy();
			m_inputLayout.reset();

			Logger::Info(
				LogCategory::DX3D,
				"Input Layout destroyed."
			);
		}

		if (m_vertexShader)
		{
			Logger::Debug(
				LogCategory::DX3D,
				"Destroying Vertex Shader."
			);

			m_vertexShader->Destroy();
			m_vertexShader.reset();

			Logger::Info(
				LogCategory::DX3D,
				"Vertex Shader destroyed."
			);
		}

		if (m_pixelShader)
		{
			Logger::Debug(
				LogCategory::DX3D,
				"Destroying Pixel Shader."
			);

			m_pixelShader->Destroy();
			m_pixelShader.reset();

			Logger::Info(
				LogCategory::DX3D,
				"Pixel Shader destroyed."
			);
		}

		if (m_vertexBuffer)
		{
			Logger::Debug(
				LogCategory::DX3D,
				"Destroying vertex buffer."
			);

			m_vertexBuffer->Destroy();
			m_vertexBuffer.reset();

			Logger::Info(
				LogCategory::DX3D,
				"Vertex buffer destroyed."
			);
		}

		if (m_renderDevice)
		{
			Logger::Debug(
				LogCategory::DX3D,
				"Destroying device."
			);

			m_renderDevice.reset();

			Logger::Info(
				LogCategory::DX3D,
				"Device destroyed."
			);
		}

		if (m_window)
		{
			Logger::Debug(
				LogCategory::General,
				"Destroying Window."
			);

			m_window->Destroy();
			m_window.reset();

			Logger::Info(
				LogCategory::General,
				"Window destroyed."
			);
		}
		
		Logger::Info(LogCategory::General, "OMSIEngine shutdown complete.");
	}
}