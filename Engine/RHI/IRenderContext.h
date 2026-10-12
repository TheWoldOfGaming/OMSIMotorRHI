#pragma once

namespace Engine
{
	class IRenderContext
	{
	public:
		virtual ~IRenderContext() = default;

		virtual bool BeginFrame(float r, float g, float b, float a) = 0;

		virtual bool Present() = 0;
	};
}