#pragma once
#include <cstddef>
#include <RHI/Vertex.h>

namespace Engine
{
	struct WindowDesc
	{
		int width = 1280;
		int height = 720;
		const wchar_t* title = L"OMSIEngine Version 1.0";
		bool resizeable = true;
		bool fullscreen = false;
	};

	struct RenderDeviceDesc
	{
		void* hwnd = nullptr;
		int width = 1280;
		int height = 720;
	};

	struct VertexBufferDesc
	{
		const Vertex* vertices = nullptr;
		size_t vertexCount = 0;
	};
}