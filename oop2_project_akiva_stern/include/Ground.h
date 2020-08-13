/*
class Ground
*/

#pragma once
#include "StaticObject.h"

class Ground : public StaticObject {
public:

	Ground(sf::Texture* texture, sf::Vector2f pos) : StaticObject(texture, pos) {}

private:

	static bool m_registerit;
};




