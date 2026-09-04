#pragma once

namespace Engine
{
	class IRenderContext
	{
	public:
		virtual ~IRenderContext() = default;

		virtual void Clear(float r, float g, float b, float a) = 0;
		virtual void Present() = 0;
	};
}