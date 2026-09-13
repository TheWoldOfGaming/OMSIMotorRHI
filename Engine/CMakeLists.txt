add_library(Engine STATIC
	Core/Logger.cpp

	Platform/Win32Window.cpp
	Platform/WindowFactory.cpp

	Application/Application.cpp

	RHI/DX11/D3D11RenderDevice.cpp
	RHI/DX11/D3D11RenderContext.cpp
	RHI/DX11/D3D11VertexBuffer.cpp
	RHI/DX11/D3D11VertexShader.cpp
	RHI/DX11/D3D11PixelShader.cpp
	RHI/DX11/D3D11InputLayout.cpp

	RHI/RenderDeviceFactory.cpp
	RHI/VertexBufferFactory.cpp
	RHI/VertexShaderFactory.cpp
	RHI/PixelShaderFactory.cpp
	RHI/InputLayoutFactory.cpp
)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Engine PUBLIC 
	d3d11.lib
	d3dcompiler.lib
)