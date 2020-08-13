/*
class Spikes
*/

#pragma once
#include "StaticObject.h"


class Spikes : public StaticObject {
public:

	Spikes(sf::Texture* texture, sf::Vector2f pos) : StaticObject(texture, pos) {}

private:

	static bool m_registerit;
};