#include "World.h"
#include "TinyEngine.h"
#include "Entity.h"

World::World()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
		ObjectList[i] = nullptr;
}

World::~World()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (ObjectList[i] != nullptr)
		{
			delete ObjectList[i];
			ObjectList[i] = nullptr;
		}
	}
}

void World::Update()
{

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (ObjectList[i] == nullptr)
			continue;

		ObjectList[i]->Update();
	}
}

void World::Draw()
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (ObjectList[i] == nullptr)
			continue;

		ObjectList[i]->Draw();
	}
}

void World::SpawnEntity(Entity* InEntity)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (ObjectList[i] == nullptr)
		{
			ObjectList[i] = InEntity;
			break;
		}
	}

	InEntity->MyWorld = this;
}

void World::DestroyEntity(Entity* InEntity)
{
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if (ObjectList[i] == InEntity)
		{
			ObjectList[i] = nullptr;
			delete InEntity;

			break;
		}
	}
}