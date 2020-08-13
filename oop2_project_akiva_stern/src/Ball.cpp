#include "Ball.h"
#include "Factory.h"
#include "Utilities.h"


bool Ball::m_registerit = Factory::registeritStatic(BALL, [](std::string str, sf::Vector2f pos) -> std::unique_ptr<StaticObject>
	{
		char c = str[0];
		return std::make_unique<Ball>(convertKeyToColor(c), pos);
	});