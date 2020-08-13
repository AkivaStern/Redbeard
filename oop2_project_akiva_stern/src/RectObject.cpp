#include "RectObject.h"

void RectObject::setQualities(sf::Color color, float width, sf::Vector2f pos) 
{
	m_obj = sf::RectangleShape(sf::Vector2f(width, RECT_HEIGHT));
	m_obj.setOutlineThickness(3);
	m_obj.setOutlineColor(sf::Color::Black);
	m_obj.setFillColor(color);
	initializePos(pos);
	m_myColor = color;
}


void RectObject::setColor(sf::Color color, bool fill) 
{
	if (fill)
	{
		m_obj.setFillColor(m_myColor);
	}
	else
	{
		m_obj.setFillColor(sf::Color::Transparent);
		m_obj.setOutlineColor(color);
	}
}