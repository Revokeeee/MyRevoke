#pragma once

#include "glm/glm.hpp"

#include "MyRevoke/Renderer/Buffer.h"

namespace Revoke
{

	class RendererAPI
	{
	
	public:
		enum class API
		{
			None = 0,
			OpenGL = 1
		};
	public:
		virtual void SetClearColor(const glm::vec4 color) = 0;
		virtual void Clear() = 0;
		virtual void DrawElements(const Shared<VertexArray>& vertrexArray, uint32_t count = 0) = 0;
		virtual void EnableBlending() = 0;
		virtual void Init() = 0;
		virtual void WindowResize(float width, float height) = 0;

		inline static API GetAPI() { return s_API; };
	private:
		static API s_API;
	};
}