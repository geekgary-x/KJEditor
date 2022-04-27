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
			glm::vec3 Ambient = { 0.0215, 0.1745, 0.0215 };
			glm::vec3 Diffuse = { 0.07568, 0.61424, 0.07568 };
			glm::vec3 Specular = { 0.633, 0.727811, 0.633 };
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