#pragma once
#include <Platform/IWindow.h>
#include <Core/Common.h>

namespace Engine
{
	IWindow* FactoryCreateWindow(const WindowDesc& desc);
}