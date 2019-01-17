#include "Entity.h"
#include "TinyEngine.h"

Entity::Entity(const Vector& position, unsigned int Color) :
	position(position),
	BoundingBox(position.x, position.y, 32, 32),
	Color(Color)
{

}

void Entity::Draw()
{
	engSetColor(Color);
	engDrawRect(position.x, position.y, BoundingBox.Width, BoundingBox.Height);
}

void Entity::SetColor(unsigned int Color)
{
	this->Color = Color;
}
