#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#include "Vector.h"

class Object {
public:
	Object(int w = 0, int h = 0);
	Object(ALLEGRO_BITMAP *sprite, int w, int h);

	Vector position;
	int width, height;

	virtual void update() {};
	virtual bool checkCollision(Object* other);
	void draw();
	void setPosition(float x, float y);
	void setSprite(ALLEGRO_BITMAP* sprite);
private:
	ALLEGRO_BITMAP *sprite;
	int spriteWidth, spriteHeight;
};