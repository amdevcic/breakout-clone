#pragma once
#include "Object.h"
#include <math.h>
#define PLAYER_SPRITE_PATH	"Resources/paddle.png"
#define PLAYER_SPRITE_HEIGHT	32
#define PLAYER_SPRITE_WIDTH		128
#define PLAYER_SPEED			1.2

class Player : public Object {
public:
	Player();
	~Player();
	void Update();
	void Move(float x);
	ALLEGRO_BITMAP* sprite;
};