/*
class GameObject:
serves as base class for all game objects in virtual world
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "DrawableObject.h"
#include "SpriteObject.h"
#include "RectObject.h"
#include "CircleObject.h"
#include "MediaResources.h"

using std::vector;
using std::shared_ptr;


class GameObject {
public:
	GameObject() = default;
	
	GameObject(sf::Texture* texture, sf::Vector2f pos, sf::IntRect intRect = sf::IntRect(0, 0, 0, 0));

	GameObject(sf::Color color, float width, sf::Vector2f pos);

	GameObject(sf::Color color, sf::Vector2f pos, float r, int points);

	virtual void draw(sf::RenderWindow& window) { m_drawable->draw(window); }

	std::unique_ptr<DrawableObject>& getDrawable() { return m_drawable; }
	
	sf::Vector2f getPosition() const { return m_drawable->getPosition(); }
	
	virtual ~GameObject() = default;

private:

	std::unique_ptr<DrawableObject> m_drawable;
};