#include "Player.h"

Player::Player() : Object(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT) {
    sprite = al_load_bitmap(PLAYER_SPRITE_PATH);
    Object::setSprite(sprite);
}

Player::~Player() {
    al_destroy_bitmap(sprite);
}

void Player::Move(float d) {
	position.x = fmin(1080-width, fmax(position.x + d, 0));
}

void Player::Update() {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);
    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
        Move(PLAYER_SPEED);
    if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
        Move(-PLAYER_SPEED);
}