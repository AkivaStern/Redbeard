#pragma once
#include <SFML/Graphics.hpp>
class MovableObject;

class MoveHandling {
public:

	virtual void move(sf::Time, MovableObject&) = 0;

	virtual ~MoveHandling() = default;
};