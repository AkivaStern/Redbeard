#include "GameObject.h"

GameObject::GameObject(sf::Texture* texture, sf::Vector2f pos, sf::IntRect intRect) 
{
	m_drawable = std::make_unique<SpriteObject>();
	m_drawable->setTexture(texture, pos, intRect);
}


GameObject::GameObject(sf::Color color, float width, sf::Vector2f pos) 
{
	m_drawable = std::make_unique<RectObject>();
	m_drawable->setQualities(color, width, pos);

}


GameObject::GameObject(sf::Color color, sf::Vector2f pos, float r, int points) 
{
	m_drawable = std::make_unique<CircleObject>();
	m_drawable->setQualities(color, pos, r, points);
}
