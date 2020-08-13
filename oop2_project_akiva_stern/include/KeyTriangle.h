/*
class KeyTriangle:
if collected , unlocks all steps of that color for rest of round
*/

#pragma once
#include "StaticObject.h"
#include "MediaResources.h"



class KeyTriangle : public StaticObject {
public:

	KeyTriangle(sf::Color color, sf::Vector2f pos);

	void draw(sf::RenderWindow& window) override;

	void collectKey();

	sf::FloatRect getKeyGlobalBounds() const { return m_key.getGlobalBounds(); }
	
	void returnKey();

	bool m_isCollected = false;

private:

	static bool m_registerit;
	sf::Sprite m_key;
	sf::Color m_color;
};