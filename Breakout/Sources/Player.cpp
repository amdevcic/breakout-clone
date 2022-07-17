#include "Player.h"

Player::Player() : Object(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT) 
{
	sprite = al_load_bitmap(PLAYER_SPRITE_PATH);
	Object::setSprite(sprite);
}

Player::~Player() 
{
	al_destroy_bitmap(sprite);
}

void Player::move(float d) 
{
	position.x = fmin(1080 - width, fmax(position.x + d, 0));
}

void Player::update() 
{
	ALLEGRO_KEYBOARD_STATE keyState;
	al_get_keyboard_state(&keyState);
	if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
		move(PLAYER_SPEED);
	}
	if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
		move(-PLAYER_SPEED);
	}
}