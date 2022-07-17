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

enum class GameState { RUNNING, BEGIN, LOSE, PAUSE, EXIT };

class Game {
public:
	Game(Level* level, int levelIndex, ALLEGRO_DISPLAY* display);
	~Game();

	void update();
	void resetBall();
	void launchBall();
	void run();
private:
	Player* player;
	Ball* ball;
	Level* currentLevel;
	GameState gameState;

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
};