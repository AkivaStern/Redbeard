/*
class Water
*/

#pragma once
#include "MovableObject.h"
#include "WaterMove.h"
#include <sstream>


class Water : public MovableObject {

public:
	Water() = default;

	Water(sf::Texture* texture, sf::Vector2f pos, RedBeard& redBeard, std::string speed);

	std::string speed() const { return m_speed; }

private:
	std::string m_speed;
};