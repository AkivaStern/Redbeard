#include "Gold.h"
#include "Factory.h"

const int GOLD_OFFSET = 8;

bool Gold::m_registerit = Factory::registeritStatic(GOLD, [](std::string str, sf::Vector2f pos) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Gold>(MediaResources::instance().goldTexture(), sf::Vector2f(pos.x, pos.y - GOLD_OFFSET));
	});