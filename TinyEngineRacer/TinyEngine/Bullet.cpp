#include "Bullet.h"
#include "TinyEngine.h"
#include "World.h"
#include "Type.h"
#include "IDamageable.h"
#include "Enemy.h"

void Bullet::Update()
{
	position += direction * 500.f * engDelta();

	BoundingBox.X = position.x;
	BoundingBox.Y = position.y;

	Enemy* HitEnemy = MyWorld->GetCollision<Enemy>(BoundingBox);
	if (HitEnemy != nullptr)
	{
		Vector Dif = (position + Vector(8,8)) - (HitEnemy->position + Vector(16,16));
		float Dist = Dot(Dif, HitEnemy->Direction);

		if (Dist < 0.f)
		{
		MyWorld->DestroyEntity(HitEnemy);
		}

		MyWorld->DestroyEntity(this);
		return;
	}

	LifeTime -= engDelta();
	if (LifeTime <= 0.f)
	{
		MyWorld->DestroyEntity(this);
		return;
	}
}