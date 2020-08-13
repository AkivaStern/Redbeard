#include "CircleObject.h"

const int OUTLINE_THICKNESS = 2;



void CircleObject::setQualities(sf::Color color, sf::Vector2f pos, float radius, int points) 
{
	m_obj = sf::CircleShape(radius, points);

	m_obj.setFillColor(color); 

	m_obj.setOutlineThickness(OUTLINE_THICKNESS);

	m_obj.setOutlineColor(sf::Color::Black);

	initializePos(pos);
}

void CircleObject::setColor(sf::Color color, bool draw) 
{
	if (draw)
	{
		m_obj.setFillColor(color);
		m_obj.setOutlineColor(sf::Color::Black);
	}

	else
	{
		m_obj.setFillColor(sf::Color::Transparent);
		m_obj.setOutlineColor(sf::Color::Transparent);
	}
}


void CircleObject::draw(sf::RenderWindow& window) 
{
	if (m_obj.getFillColor() != sf::Color::Transparent)
		window.draw(m_obj);
}