#include <RHI/InputLayoutFactory.h>
#include <RHI/IVertexShader.h>

#include <d3d11.h>

namespace Engine
{
	IInputLayout* FactoryCreateInputLayout(IRenderDevice* device, IVertexShader* vertexShader)
	{
		IInputLayout* inputLayout = nullptr;
		return inputLayout;
	}
}