#pragma once
#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <vector>
#include <map>
#include "Brick.h"

#define DEFAULT_HIT_SOUND "Resources/Sounds/4359__noisecollector__pongblipf4.wav"

class Level {
public:
	Level(const char* levelFilePath, int screenWidth, int screenHeight);
	~Level();
	std::vector<std::vector<Brick>> bricks;
	void drawBackground(int screenWidth, int screenHeight);
	void drawBricks();
	int bricksRemaining;
private:
	ALLEGRO_BITMAP* background;
	int bgWidth, bgHeight;
	int rowcount, colcount, rowspacing, colspacing, brickwidth, brickheight;
	std::map<char, BrickType> brickTypes;
	void loadXml(const char* levelFilePath);
	std::vector<std::vector<char>> brickLayout;
};