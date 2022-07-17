#include "Object.h"

Object::Object(ALLEGRO_BITMAP* sprite, int w, int h) 
{
	this->sprite = sprite;
	position = Vector();
	width = w; height = h;
	spriteWidth = al_get_bitmap_width(sprite);
	spriteHeight = al_get_bitmap_height(sprite);
}

Object::Object(int w, int h) : width(w), height(h), spriteWidth(0), spriteHeight(0) 
{
	sprite = NULL;
	position = Vector();
}

void Object::draw() 
{
	if (sprite != NULL) {
		al_draw_scaled_bitmap(sprite, 0, 0, spriteWidth, spriteHeight, position.x, position.y, width, height, 0);
	}
}

void Object::setPosition(float x, float y) 
{
	this->position = Vector(x, y);
}

bool Object::checkCollision(Object* other) 
{
	if ((position.x + width) < other->position.x) { return false; }
	if (position.x > (other->position.x + other->width)) { return false; }
	if ((position.y + height) < other->position.y) { return false; }
	if (position.y > (other->position.y + other->height)) { return false; }
	return true;
}

void Object::setSprite(ALLEGRO_BITMAP* sprite) 
{
	this->sprite = sprite;

	spriteWidth = al_get_bitmap_width(sprite);
	spriteHeight = al_get_bitmap_height(sprite);
}