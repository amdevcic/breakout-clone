#pragma once

#include <allegro5/allegro_image.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <vector>
#include <map>
#include <sstream>
#include <string>

#include "tinyxml2.h"
#include "Brick.h"

#define DEFAULT_HIT_SOUND		"Resources/Sounds/4359__noisecollector__pongblipf4.wav"
#define DEFAULT_BRICK_SPRITE	"Resources/block.png"

class Level {
public:
	Level(const char* levelFilePath, int screenWidth, int screenHeight);
	Level() = default;
	~Level();

	std::vector<std::vector<Brick>> bricks;
	int bricksRemaining;
	
	void drawBackground(int screenWidth, int screenHeight);
	void drawBricks();
private:
	ALLEGRO_BITMAP* background;
	std::vector<std::vector<char>> brickLayout;
	std::map<char, BrickType> brickTypes;
	int bgWidth, bgHeight, rowCount, colCount, rowSpacing, colSpacing, brickWidth, brickHeight;
	
	void loadXml(const char* levelFilePath);
};