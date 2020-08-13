#include "Ground.h"
#include "Factory.h"

bool Ground::m_registerit = Factory::registeritStatic(GROUND, [](std::string str, sf::Vector2f pos) -> std::unique_ptr<StaticObject>
	{
		return std::make_unique<Ground>(MediaResources::instance().groundTexture(), pos);
	});

