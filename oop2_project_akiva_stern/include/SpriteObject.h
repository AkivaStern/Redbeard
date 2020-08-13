/*
class SpriteObject:

for specific sprite funtionality

*/

#pragma once
#include "TemplateDrawableObject.h"

class SpriteObject : public TemplateDrawableObject<sf::Sprite> {
public:

	void setTexture(sf::Texture* t, sf::Vector2f pos, sf::IntRect intRect) override;

	void setIntRect(sf::IntRect portion) override { m_obj.setTextureRect(portion); }

	void flipObj(int dir) override { m_obj.setScale(dir, 1); }
	
	virtual void setColor(sf::Color color, bool) override { m_obj.setColor(color); }
	
	virtual sf::Color getColor() const override { return sf::Color::Transparent; }

private:
	
};