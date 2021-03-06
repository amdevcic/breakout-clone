#pragma once

#include <math.h>

#include "Object.h"

#define BALL_SPRITE_PATH	"Resources/ball.png"
#define BALL_SPRITE_SIZE	32

#define BALL_SPEED			4

class Ball : public Object {
public:
	Ball();
	~Ball();

	Vector direction;

	void update();
	void flipX();
	void flipY();
	bool checkCollision(Object* other, Vector* normal);
private:
	ALLEGRO_BITMAP* sprite;
	float radius;
};