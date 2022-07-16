#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include "Vector.h"

class Object 
{
public:
	Object();
	Object(int w, int h);
	Object(ALLEGRO_BITMAP *sprite, int w, int h);
	virtual void Update();
	virtual bool checkCollision(Object* other);
	void Draw();
	void setPosition(float x, float y);
	Vector position;
	int width, height;
	void setSprite(ALLEGRO_BITMAP* sprite);
private:
	ALLEGRO_BITMAP *sprite;
	int spriteWidth, spriteHeight;
};