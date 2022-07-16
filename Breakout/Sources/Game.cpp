#include "Game.h"

Game::Game(Level* level, int levelIndex, ALLEGRO_DISPLAY* display) {

	this->display = display;
	screenWidth = al_get_display_width(this->display);
	screenHeight = al_get_display_height(this->display);

	player = new Player();
	player->setPosition(screenWidth / 2 - 64, screenHeight - 90);
	ball = new Ball();
	ball->setPosition(screenWidth / 2, screenHeight / 2);

	currentLevel = level;
	this->levelIndex = levelIndex;
	gameState = BEGIN;
	score = 0;
	lives = STARTING_LIVES;

	uiBar = al_load_bitmap("Resources/bar.png");
	uiFont = al_load_ttf_font("Resources/AGENCYR.ttf", 28, 0);

	playerHitSound = al_load_sample(PLAYER_HIT_SOUND);
	wallHitSound = al_load_sample(WALL_HIT_SOUND);

	uiText = formatUIText();
}

Game::~Game() {
	al_destroy_bitmap(uiBar);
	al_destroy_font(uiFont);

	al_destroy_sample(playerHitSound);
	al_destroy_sample(wallHitSound);
}

void Game::drawAll() 
{
	al_clear_to_color(al_map_rgb(128, 200, 200));
	currentLevel->drawBackground(screenWidth, screenHeight);
	currentLevel->drawBricks();
	player->Draw();
	ball->Draw();
	al_draw_bitmap(uiBar, 0, screenHeight - 48, 0);
	al_draw_text(uiFont, al_map_rgb(255, 255, 255), 20, screenHeight - 40, 0, uiText.c_str());
	al_flip_display();
}

void Game::update() 
{
	player->Update();
	ball->Update();

	Vector collisionNormal;

	if (ball->checkCollision(player, &collisionNormal)) {
		ball->direction = ball->direction.normalized().mirror(collisionNormal).normalized();
		al_play_sample(playerHitSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	if (ball->position.y < 0) {
		ball->flipY();
		al_play_sample(wallHitSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	if (ball->position.x < 0 || ball->position.x > screenWidth - ball->width) {
		ball->flipX();
		al_play_sample(wallHitSound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
	}
	if (ball->position.y > screenHeight - ball->height) {
		loseLife();
	}

	for (std::vector<Brick>& row : currentLevel->bricks) {
		for (Brick& b : row) {
			if (b.active && ball->checkCollision((Object*)&b, &collisionNormal)) {
				bool broken = b.hit();
				ball->direction = ball->direction.normalized().mirror(collisionNormal).normalized();
				if (broken) {
					al_play_sample(b.data->breakSample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
					score += b.data->breakScore;
					uiText = formatUIText();
					currentLevel->bricksRemaining--;
					if (currentLevel->bricksRemaining <= 0)
						gameState = EXIT;
				}
				else {
					al_play_sample(b.data->hitSample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				}
			}
		}
	}
}

void Game::run() 
{
	while (gameState != EXIT) {
		drawAll();
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE))
			gameState = EXIT;
		switch (gameState)
		{
		case RUNNING:
			update();
			break;
		case BEGIN:
			player->Update();
			attachBallToPlayer();
			if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
				launchBall();
			break;
		case LOSE:
			//if (al_key_down(&keyState, ALLEGRO_KEY_SPACE)) {
			//	player->setPosition(screenWidth / 2 - 64, screenHeight - 90);
			//	score = 0;
			//	lives = STARTING_LIVES;
			//	resetBall();
			//}
			break;
		case PAUSE:
			break;
		case EXIT:
			break;
		default:
			break;
		}
	}
}

std::string Game::formatUIText() {
	std::ostringstream uiText;
	uiText << "Score: " << score << "   Lives: " << lives << "  Level: " << levelIndex;
	return uiText.str();
}

void Game::loseLife() {
	lives--;
	if (lives < 0)
		gameState = EXIT;
	else {
		resetBall();
		uiText = formatUIText();
	}
}

void Game::resetBall() {
	gameState = BEGIN;
	ball->direction = Vector();
}

void Game::launchBall() {
	gameState = RUNNING;
	int xDirection = 1; // TODO: random direction
	ball->direction = Vector(xDirection, -1).normalized();
}

void Game::attachBallToPlayer() {
	ball->setPosition(player->position.x + (player->width - ball->width) / 2, player->position.y - ball->height - 10);
}