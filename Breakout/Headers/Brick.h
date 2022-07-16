#pragma once
#include <allegro5/allegro_audio.h>
#include "Object.h"

struct BrickType {
	ALLEGRO_BITMAP* texture;
	int hitPoints;
	bool indestructible;
	ALLEGRO_SAMPLE* hitSample;
	ALLEGRO_SAMPLE* breakSample;
	int breakScore;
};

class Brick : public Object {
public:
	BrickType* data;
	Brick(BrickType* data, int x, int y, int w, int h);
	bool hit();
	bool active;
private:
	int hp;
};