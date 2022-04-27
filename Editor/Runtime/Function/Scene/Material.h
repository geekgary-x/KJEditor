#pragma once
#include "Core/Base/macro.h"
#include "Core/Base/PublicSingleton.h"

#include "Function/Render/Interface/UniformBuffer.h"
#include <glm/glm.hpp>
#include <map>
namespace Soarscape
{
	class MaterialInterface
	{
	public:
		class UniformBlock
		{
			glm::vec3 Ambient = { 1.0f, 1.0f, 1.0f };
			glm::vec3 Diffuse = { 1.0f, 1.0f, 1.0f };
			glm::vec3 Specular = { 1.0f, 1.0f, 1.0f };
			float Shininess = 0.6f;
		};
		virtual void bind(uint32_t index){};
		virtual ~MaterialInterface() = default;
	};
	class BasicMaterial : public MaterialInterface
	{
	public:
		BasicMaterial();
		void bind(uint32_t index);
		void updateBuffer();
	private:
		std::shared_ptr<UniformBuffer> m_UniformBuffer;
		UniformBlock m_BlockData;
	};

	class MaterialPool : public PublicSingleton<MaterialPool>
	{
	public:
		MaterialPool();
		std::shared_ptr<MaterialInterface> getMaterial(const std::string& materialName);
	private:
		std::map<std::string, std::shared_ptr<MaterialInterface>> m_MapterialMap;

	};
}