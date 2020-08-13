/*
class RectObject:

functionality for sf::rect that we want specifically
*/

#pragma once
#include "TemplateDrawableObject.h"

const float RECT_HEIGHT = 10;


class RectObject : public TemplateDrawableObject<sf::RectangleShape>
{
public:

	void setQualities(sf::Color color, float width, sf::Vector2f pos) override;

	virtual void setColor(sf::Color color, bool fill) override;

	virtual sf::Color getColor() const override { return m_myColor; }
	
private:

	sf::Color m_myColor;
};