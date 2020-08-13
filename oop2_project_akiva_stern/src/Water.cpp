#include "Water.h"

const int TRANSPARENCY = 120;

Water::Water(sf::Texture* texture, sf::Vector2f pos, RedBeard& redBeard, std::string speed) : MovableObject(texture, pos), m_speed(speed)
{
	getDrawable()->setColor(sf::Color(0, 250, 240, TRANSPARENCY), true);

	std::string parsedSpeed;

	std::stringstream line(speed);

	if (!(line >> parsedSpeed))
		throw::std::runtime_error("missing water ('w') key in map");

	if (!(line >> parsedSpeed))
		throw::std::runtime_error("missing water speed");

	m_myMove = std::make_unique<WaterMove>(redBeard, std::stof(parsedSpeed));
}