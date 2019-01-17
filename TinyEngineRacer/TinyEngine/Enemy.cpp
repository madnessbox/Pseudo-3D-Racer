#include "Enemy.h"
#include "Color.h"

void Enemy::Update()
{
	DrawVectorFrom(Direction * 80.f, position + Vector(16,16), YELLOW);
}

