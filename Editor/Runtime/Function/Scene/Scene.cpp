#include "Scene.h"
#include "Components.h"
namespace Soarscape
{
	SceneObject Scene::CreateObject(const std::string& name)
	{
		SceneObject entity = { m_Registry.create(), this};
		entity.AddComponent<TransformComponent>();
		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
}

