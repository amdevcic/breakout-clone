#include "Ball.h"

Ball::Ball() : Object(BALL_SPRITE_SIZE, BALL_SPRITE_SIZE) 
{
	sprite = al_load_bitmap(BALL_SPRITE_PATH);
	Object::setSprite(sprite);
	direction = Vector(0.5, -0.5);
	radius = BALL_SPRITE_SIZE / 2;
}

Ball::~Ball() 
{
	al_destroy_bitmap(sprite);
}

void Ball::update() 
{
	position = position + direction * BALL_SPEED;
	if (direction.y < 0.1 && direction.y > -0.1 && direction.x != 0) {
		direction.y = 0.25;
	}
}

void Ball::flipX() 
{
	direction.x = -direction.x;
}

void Ball::flipY() 
{
	direction.y = -direction.y;
}
bool Ball::checkCollision(Object* other, Vector* normal) 
{
	Vector center(position + Vector(radius, radius));
	Vector aabb_half(other->width / 2, other->height / 2);
	Vector aabb_center(other->position + aabb_half);
	Vector diff = center - aabb_center;
	Vector clamped(
		fmin(aabb_half.x, fmax(-aabb_half.x, diff.x)),
		fmin(aabb_half.y, fmax(-aabb_half.y, diff.y)));
	Vector closest = aabb_center + clamped;
	diff = center - closest;
	*normal = diff.normalized();
	return diff.length() < radius;
}
