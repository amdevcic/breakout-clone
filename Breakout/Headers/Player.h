#pragma once

#include "Object.h"

#include <math.h>

#define PLAYER_SPRITE_PATH		"Resources/paddle.png"
#define PLAYER_SPRITE_HEIGHT	32
#define PLAYER_SPRITE_WIDTH		128
#define PLAYER_SPEED			4.8

class Player : public Object {
public:
	Player();
	~Player();

	void update();
	void move(float x);

private:
	ALLEGRO_BITMAP* sprite;
};