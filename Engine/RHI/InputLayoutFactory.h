#pragma once
#include <RHI/IInputLayout.h>
#include <RHI/IRenderDevice.h>
#include <RHI/IVertexShader.h>

namespace Engine
{
	IInputLayout* FactoryCreateInputLayout(IRenderDevice* device, IVertexShader* vertexShader);
}