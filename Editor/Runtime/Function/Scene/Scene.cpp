#include "Scene.h"
#include "Resource/Components/Tag.h"

#include "Function/Event/EventSystem.h"
#include "Function/Scene/EditCamera.h"
namespace Soarscape
{
	Scene::Scene()
	{
		m_CurrentCamera = &PublicSingletonInstance(EditorCamera);
	}
	void Scene::renderTick()
	{
		m_CurrentCamera->bind();
	}
	void Scene::initialize()
	{
	}
	SceneObject Scene::CreateObject(const std::string& name)
	{
		SceneObject entity = { m_Registry.create(), this};
		auto& Tag = entity.AddComponent<TagComponent>();
		Tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}
}
