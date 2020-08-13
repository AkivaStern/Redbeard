/*
class Ball:
represents colored Ball in game
*/

#pragma once
#include "StaticObject.h"


class Ball : public StaticObject {
public:

	Ball(sf::Color color, sf::Vector2f pos) : StaticObject(color, pos), m_myColor(color) {}

	void collect() { m_isCollected = true; }

	void drop() { m_isCollected = false; }

	bool isCollected() const { return m_isCollected; }

	sf::Color getDefaultColor() const { return m_myColor; }

private:

	bool m_isCollected = false;
	sf::Color m_myColor;
	static bool m_registerit;
};