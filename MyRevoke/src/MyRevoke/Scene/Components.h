#pragma once
#include "SceneCamera.h"
#include "ScriptEntity.h"

#include <string>
#include <glm/glm.hpp>

namespace Revoke
{
	struct NameCpmponent
	{
		std::string Name;

		NameCpmponent() = default;
		NameCpmponent(const NameCpmponent&) = default;
		NameCpmponent(const std::string& name)
			:Name(name) {}
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			:Transform(transform) {}
		operator glm::mat4&() { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color )
			:Color(color) {}
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool isMain = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
		
	};

	struct NativeScriptComponent
	{
		ScriptEntity* Instance = nullptr;

		ScriptEntity* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}