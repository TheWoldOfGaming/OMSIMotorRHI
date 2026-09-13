#pragma once

namespace Engine
{
	class IVertexBuffer;
	class IVertexShader;
	class IPixelShader;
	class IInputLayout;

	class IRenderContext
	{
	public:
		virtual ~IRenderContext() = default;

		virtual void Clear(float r, float g, float b, float a) = 0;
		virtual void Present() = 0;
		virtual void Draw(size_t vertexCount) = 0;

		virtual void SetVertexBuffer(IVertexBuffer* buffer) = 0;
		virtual void SetVertexShader(IVertexShader* shader) = 0;
		virtual void SetPixelShader(IPixelShader* shader) = 0;
		virtual void SetInputLayout(IInputLayout* layout) = 0;
	};
}