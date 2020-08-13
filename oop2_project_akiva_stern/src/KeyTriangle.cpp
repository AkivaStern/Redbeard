#include "KeyTriangle.h"
#include "Factory.h"
#include "Utilities.h"


const int KEY_OFFSET = 5;


bool KeyTriangle::m_registerit = Factory::registeritStatic(TRIANGLE_KEY, [](std::string str, sf::Vector2f pos) -> std::unique_ptr<StaticObject>
	{
		if (str.empty())
			throw std::runtime_error("missing triangle keys color");

		char c = str[0];
		return std::make_unique<KeyTriangle>(convertKeyToColor(c), pos);
	});

KeyTriangle::KeyTriangle(sf::Color color, sf::Vector2f pos) : StaticObject(color, pos, TRIANGLE_SIDE_SIZE, TRIANGLE_POINTS), m_color(color)
{
	m_key.setTexture(*MediaResources::instance().keyTexture());

	m_key.setOrigin(m_key.getGlobalBounds().width / 2, m_key.getGlobalBounds().height / 2);

	m_key.setPosition(getDrawable()->getPosition() + sf::Vector2f(KEY_OFFSET, KEY_OFFSET));
}


void KeyTriangle::draw(sf::RenderWindow& window) 
{
	getDrawable()->draw(window);

	window.draw(m_key);
}

void KeyTriangle::collectKey()
{
	m_key.setTextureRect(sf::IntRect(0, 0, 0, 0));

	getDrawable()->setColor(sf::Color(0, 0, 0, 1), 1); //transparent for fill and outline

	m_isCollected = true;
}


void KeyTriangle::returnKey()
{
	m_isCollected = false;

	m_key.setTextureRect(sf::IntRect(0, 0, MediaResources::instance().keyTexture()->getSize().x, MediaResources::instance().keyTexture()->getSize().y));

	getDrawable()->setColor(m_color, 1);
}