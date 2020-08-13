/*
class TemplateDrawableObject

derives from base class DrawableObject, and hold specific type T object, which is a drawable
*/


#pragma once
#include "DrawableObject.h"


template <typename T>
class TemplateDrawableObject : public DrawableObject {
public:

	void initializePos(sf::Vector2f pos) 
	{
		m_obj.setOrigin(m_obj.getGlobalBounds().width / 2, m_obj.getGlobalBounds().height / 2);
		m_obj.setPosition(pos);
	}

	void draw(sf::RenderWindow& window) override { window.draw(m_obj); }

	virtual void move(sf::Vector2f movement) override { m_obj.move(movement); }

	sf::Vector2f getPosition() const override { return m_obj.getPosition(); }

	sf::FloatRect getGlobalBounds() const override { return m_obj.getGlobalBounds(); }
	
protected:
	T m_obj;
};