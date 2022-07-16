#pragma once
#include "Object.h"
#include <math.h>
#define BALL_SPRITE_PATH	"Resources/ball2.png"
#define BALL_SPRITE_SIZE	32

class Ball : public Object {
public:
	Ball();
	~Ball();
	void Update();
	void flipX();
	void flipY();
	bool checkCollision(Object* other, Vector* normal);
	Vector direction;
private:
	ALLEGRO_BITMAP* sprite;
	float speed;
	float radius;
};