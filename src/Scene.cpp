#include "Scene.h"


Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Delete(Scene* scene)
{
	delete scene;
}

void Scene::Change(Scene* &current, Scene* next)
{
	Scene::Delete(current);
	current = next;
}
