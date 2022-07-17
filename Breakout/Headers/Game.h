#pragma once

#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <sstream>

#include "Player.h"
#include "Ball.h"
#include "Level.h"

#define STARTING_LIVES		3
#define FRAMES_PER_SECOND	120

#define PLAYER_HIT_SOUND    "Resources/Sounds/350862__cabled-mess__blip-c-04.wav"
#define WALL_HIT_SOUND      "Resources/Sounds/350862__cabled-mess__blip-c-04.wav"

enum class GameState { RUNNING, BEGIN, WIN, LOSE, EXIT };

class Game {
public:
	Game(std::vector<Level*> levels, ALLEGRO_DISPLAY* display);
	Game(std::vector<std::string> levelPaths, ALLEGRO_DISPLAY* display);
	~Game();

	void run();
	void runLevel(int levelIndex);
private:
	Player* player;
	Ball* ball;
	Level* currentLevel;
	GameState gameState;
	std::vector<Level*> levels;
	std::vector<std::string> levelPaths;

	int score, lives, levelIndex;
	int screenWidth, screenHeight;

	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* uiBar;
	ALLEGRO_FONT* uiFont;
	ALLEGRO_SAMPLE* playerHitSound, *wallHitSound;

	std::string uiText;

	std::string formatUIText();
	void loseLife();
	void attachBallToPlayer();
	void drawAll();
	void update();
	void resetBall();
	void launchBall();
	bool loadLevel(int levelIndex);
};