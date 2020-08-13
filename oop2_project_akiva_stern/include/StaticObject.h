/*
class StaticObject:

for static game objects
*/
#pragma once
#include "GameObject.h"
#include "Utilities.h"

class StaticObject : public GameObject {
public:

	StaticObject() = default;

	StaticObject(sf::Texture* texture, sf::Vector2f pos)
		: GameObject(texture, pos) {}

	StaticObject(sf::Color color, sf::Vector2f pos, float rad = DEFAULT_RADIUS, int points = DEFAULT_BALL_POINTS)
		: GameObject(color, pos, rad, points) {}

private:
};