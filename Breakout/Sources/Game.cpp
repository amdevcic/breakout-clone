#include "Game.h"

Game::Game(std::vector<std::string> levelPaths, ALLEGRO_DISPLAY* display) : levelPaths(levelPaths), display(display)
{
	lives = STARTING_LIVES;

	screenWidth = al_get_display_width(this->display);
	screenHeight = al_get_display_height(this->display);

	player = new Player();
	ball = new Ball();

	uiFont = al_load_ttf_font(FONT_PATH, 28, 0);

	playerHitSound = al_load_sample(PLAYER_HIT_SOUND);
	wallHitSound = al_load_sample(WALL_HIT_SOUND);

	uiText = formatUIText();
}

bool Game::loadLevel(unsigned int levelIndex)
{
	if (levelIndex >= levelPaths.size())
		return false;

	delete currentLevel;
	currentLevel = new Level(levelPaths[levelIndex].c_str(), screenWidth, screenHeight);

	player->setPosition((screenWidth - PLAYER_SPRITE_WIDTH) / 2, screenHeight - UI_BAR_HEIGHT - PLAYER_SPRITE_HEIGHT - 10);
	uiText = formatUIText();
	gameState = GameState::BEGIN;
	return true;
}

void Game::run()
{
	levelIndex = 0;
	while (levelIndex < levelPaths.size() && gameState != GameState::EXIT)
		runLevel(levelIndex);

}

Game::~Game()
{
	delete player, ball, currentLevel;

	al_destroy_font(uiFont);

	al_destroy_sample(playerHitSound);
	al_destroy_sample(wallHitSound);
}

void Game::drawAll()
{
	al_clear_to_color(al_map_rgb(128, 200, 200));
	currentLevel->drawBackground(screenWidth, screenHeight);
	currentLevel->drawBricks();
	player->draw();
	ball->draw();

	al_draw_filled_rectangle(0, screenHeight - UI_BAR_HEIGHT, screenWidth, screenHeight,
		al_map_rgba_f(0, 0, 0, UI_TRANSPARENCY));

	al_draw_text(uiFont, al_map_rgb(255, 255, 255), 20, screenHeight - 40, 0, uiText.c_str());
}

void Game::update()
{
	player->update();
	ball->update();

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
	if (ball->position.y > screenHeight) {
		loseLife();
	}

	for (Brick& b : currentLevel->bricks) {

		if (b.active && ball->checkCollision((Object*)&b, &collisionNormal)) {
			
			bool broken = b.hit();
			ball->direction = ball->direction.normalized().mirror(collisionNormal).normalized();

			if (broken) {
				al_play_sample(b.data->breakSample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
				score += b.data->breakScore;
				uiText = formatUIText();
				currentLevel->bricksRemaining--;
				if (currentLevel->bricksRemaining <= 0) {
					levelIndex++;
					if (levelIndex >= levelPaths.size())
						gameState = GameState::WINGAME;
					else
						gameState = GameState::WINLEVEL;
				}
			}
			else {
				al_play_sample(b.data->hitSample, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
			}
		}
	}

	player->position.x = fmin(screenWidth - player->width, fmax(player->position.x, 0));
}

void Game::runLevel(int levelIndex)
{
	bool levelLoaded = loadLevel(levelIndex);
	if (!levelLoaded) {
		gameState = GameState::EXIT;
		return;
	}

	ALLEGRO_TIMER* timer;
	ALLEGRO_EVENT_QUEUE* event_queue;
	timer = al_create_timer(1.0f / FRAMES_PER_SECOND);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_start_timer(timer);

	bool running = true;
	while (running) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			gameState = GameState::EXIT;
		}

		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_ESCAPE)) {
			gameState = GameState::EXIT;
		}

		drawAll();

		switch (gameState)
		{
		case GameState::RUNNING:

			update();
			break;

		case GameState::BEGIN:

			player->update();
			player->position.x = fmin(screenWidth - player->width, fmax(player->position.x, 0));
			attachBallToPlayer();
			if (al_key_down(&keyState, ALLEGRO_KEY_SPACE)) {
				launchBall();
			}
			break;

		case GameState::WINLEVEL:

			running = false;
			break;

		case GameState::WINGAME:
			al_draw_filled_rectangle(0, 0, screenWidth, screenHeight,
				al_map_rgba_f(0, 0, 0, UI_TRANSPARENCY));
			al_draw_text(uiFont, al_map_rgb_f(1, 1, 1), screenWidth / 2, screenHeight / 2 - 50, ALLEGRO_ALIGN_CENTER,
				"YOU WIN!");
			al_draw_textf(uiFont, al_map_rgb_f(1, 1, 1), screenWidth / 2, screenHeight / 2, ALLEGRO_ALIGN_CENTER,
				"Score: %d", score);
			al_draw_text(uiFont, al_map_rgb_f(1, 1, 1), screenWidth / 2, screenHeight / 2 + 50, ALLEGRO_ALIGN_CENTER,
				"Press Esc to exit");
			break;

		case GameState::LOSE:
			al_draw_filled_rectangle(0, 0, screenWidth, screenHeight,
				al_map_rgba_f(0, 0, 0, UI_TRANSPARENCY));
			al_draw_text(uiFont, al_map_rgb_f(1, 1, 1), screenWidth / 2, screenHeight / 2 - 50, ALLEGRO_ALIGN_CENTER,
				"GAME OVER");
			al_draw_textf(uiFont, al_map_rgb_f(1, 1, 1), screenWidth / 2, screenHeight / 2, ALLEGRO_ALIGN_CENTER,
				"Score: %d", score);
			al_draw_text(uiFont, al_map_rgb_f(1, 1, 1), screenWidth / 2, screenHeight / 2 + 50, ALLEGRO_ALIGN_CENTER,
				"Press R to restart, Esc to exit");
			if (al_key_down(&keyState, ALLEGRO_KEY_R)) {
				this->levelIndex = 0;
				score = 0;
				lives = STARTING_LIVES;
				running = false;
			}
			break;

		case GameState::EXIT:

			running = false;
			break;

		default:

			break;

		}

		al_flip_display();
	}
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
}

std::string Game::formatUIText()
{
	std::ostringstream uiText;
	uiText << "Score: " << score << "   Lives: " << lives << "  Level: " << levelIndex + 1;
	return uiText.str();
}

void Game::loseLife()
{
	lives--;
	if (lives < 0) {
		gameState = GameState::LOSE;
	}
	else {
		resetBall();
		uiText = formatUIText();
	}
}

void Game::resetBall()
{
	gameState = GameState::BEGIN;
	ball->direction = Vector();
}

void Game::launchBall()
{
	gameState = GameState::RUNNING;
	int xDirection = rand() % 2 ? 1 : -1;
	ball->direction = Vector(xDirection, -1).normalized();
}

void Game::attachBallToPlayer()
{
	ball->setPosition(
		player->position.x + (player->width - ball->width) / 2,
		player->position.y - ball->height - 10
	);
}