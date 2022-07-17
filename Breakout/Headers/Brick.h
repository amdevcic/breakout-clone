#pragma once

#include <allegro5/allegro_audio.h>

#include "Object.h"

struct BrickType {
	ALLEGRO_BITMAP* texture;
	ALLEGRO_SAMPLE* hitSample, *breakSample;
	int hitPoints, breakScore;
	bool indestructible;
};

class Brick : public Object {
public:
	Brick(BrickType* data, int x, int y, int w, int h);
	
	BrickType* data;
	bool active;
	
	bool hit();
private:
	int hp;
};