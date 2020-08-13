/*
class Animation:
for use of spritesheets
*/


#pragma once
#include <SFML/graphics.hpp>
#include "DrawableObject.h"


class Animation {
public:

	void update(DrawableObject& drawable, int mod, int offset = 0);

	void makeCounterZero() { m_animCounter = 0; }

	int getCounter() const { return m_animCounter; }

	float getElapsed() const { return m_animationClock.getElapsedTime().asSeconds(); }

	void addRects(sf::IntRect rect, int num);

private:

	sf::Clock m_animationClock;
	std::vector<sf::IntRect> m_intRects;
	int m_animCounter = 0;
};