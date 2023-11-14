#include "rvpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Revoke {
	//Temp
	static GLenum ShaderDataTypeToOpenGLDataType(ShaderDataTypes type)
	{
		switch (type)
		{
		case Revoke::ShaderDataTypes::Float:	return GL_FLOAT;
		case Revoke::ShaderDataTypes::Float2:	return GL_FLOAT;
		case Revoke::ShaderDataTypes::Float3:	return GL_FLOAT;
		case Revoke::ShaderDataTypes::Float4:	return GL_FLOAT;
		case Revoke::ShaderDataTypes::Mat3:		return GL_FLOAT;
		case Revoke::ShaderDataTypes::Mat4:		return GL_FLOAT;
		case Revoke::ShaderDataTypes::Int:		return GL_INT;
		case Revoke::ShaderDataTypes::Int2:		return GL_INT;
		case Revoke::ShaderDataTypes::Int3:		return GL_INT;
		case Revoke::ShaderDataTypes::Int4:		return GL_INT;
		case Revoke::ShaderDataTypes::Bool:		return GL_BOOL;
		default:
			RV_CORE_ASSERT(false, "Unknown Shader Data Type");
			return 0;
		}
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLVertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0	);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}

	//***********************************************************************************
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void OpenGLIndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	

	//**********************************************************************************

	OpenGLVertexArrey::OpenGLVertexArrey()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArrey::~OpenGLVertexArrey()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArrey::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArrey::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArrey::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuff) 
	{
		glBindVertexArray(m_RendererID);
		vertexBuff->Bind();

		const auto& layout = vertexBuff->GetLayout();

		uint32_t location = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLDataType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(element.Offset));

			location++;
		}
		m_VertexBuff.push_back(vertexBuff);

	}

	void OpenGLVertexArrey::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuff) 
	{
		glBindVertexArray(m_RendererID);
		indexBuff->Bind();
		
		m_IndexBuff = indexBuff;
	}



}