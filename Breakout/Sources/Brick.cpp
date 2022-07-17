#include "Brick.h"

Brick::Brick(BrickType* data, int x, int y, int w, int h) : Object(data->texture, w, h), data(data) 
{
	Object::setPosition(x, y);
	this->hp = data->hitPoints;
	this->active = true;
}

bool Brick::hit() 
{
	if (!data->indestructible && hp >= 0) {
		hp--;
		if (hp <= 0) {
			active = false;
			return true;
		}
	}
	return false;
}