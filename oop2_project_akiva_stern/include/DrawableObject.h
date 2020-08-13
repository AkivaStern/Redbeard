/*
class DrawableObject:
serves as base class for different Drawable types.
*/

#pragma once
#include <SFML/Graphics.hpp>


class DrawableObject {

public:

	virtual void setTexture(sf::Texture* t, sf::Vector2f pos, sf::IntRect = sf::IntRect(0, 0, 0, 0)) {}

	virtual void setQualities(sf::Color, float , sf::Vector2f) {}

	virtual void setQualities(sf::Color color, sf::Vector2f pos, float, int) {}

	virtual void draw(sf::RenderWindow&) = 0;

	virtual void move(sf::Vector2f movement) = 0;

	virtual sf::Vector2f getPosition() const = 0;

	virtual sf::FloatRect getGlobalBounds() const = 0;

	virtual void setColor(sf::Color color, bool) {}

	virtual sf::Color getColor() const = 0;

	virtual void setIntRect(sf::IntRect) {}

	virtual void flipObj(int dir) {}

	virtual ~DrawableObject() = default;

private:

};