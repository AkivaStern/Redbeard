/*
class MovableObject:

serves as gameobject that has movehandling
*/

#pragma once
#include "GameObject.h"
#include "MoveHandling.h"



class MovableObject : public GameObject {

public:

	MovableObject() = default;

	MovableObject(sf::Texture* texture, sf::Vector2f pos, sf::IntRect intRect = sf::IntRect(0, 0, 0, 0))
		: GameObject(texture, pos, intRect) {}

	MovableObject(sf::Color color,  float width, sf::Vector2f pos)
		: GameObject(color, width, pos) {}

	virtual void move(sf::Time deltaTime) { m_myMove->move(deltaTime, *this); }

	sf::Vector2f& getDirection() { return m_direction; }

protected:

	std::unique_ptr<MoveHandling> m_myMove;

private:

	sf::Vector2f m_direction;
};