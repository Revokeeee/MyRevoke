#include "rvpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "MyRevoke/Platform/OpenGL/OpenGLTexture2D.h"

namespace Revoke
{
    Shared<Texture2D> Texture2D::Create(const std::string& path)
	{
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            RV_CORE_ASSERT(false, "RendererAPI None is not supported"); return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);
            break;
        }
        RV_CORE_ASSERT(false, "RendererAPI is not correct")
            return nullptr;
	}
    Shared<Texture2D> Texture2D::Create(int width, int height)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            RV_CORE_ASSERT(false, "RendererAPI None is not supported"); return nullptr;
            break;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(width, height);
            break;
        }
        RV_CORE_ASSERT(false, "RendererAPI is not correct")
            return nullptr;
    }
}
