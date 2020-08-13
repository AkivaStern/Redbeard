/*
Class CircleObject:
specific Functionality for sf::CircleShape
*/

#pragma once
#include "TemplateDrawableObject.h"

const float r = 10;




class CircleObject : public TemplateDrawableObject<sf::CircleShape>
{
public:

	void setQualities(sf::Color color, sf::Vector2f pos, float radius, int points) override;

	sf::Color getColor() const override { return m_obj.getFillColor(); }

	virtual void setColor(sf::Color color, bool draw) override;

	void draw(sf::RenderWindow& window) override;

};