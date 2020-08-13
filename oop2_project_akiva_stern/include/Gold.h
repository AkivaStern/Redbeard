/*
class Gold:
*/

#pragma once
#include "StaticObject.h"


class Gold : public StaticObject {
public:

	Gold(sf::Texture* texture, sf::Vector2f pos) : StaticObject(texture, pos) {}

private:
	static bool m_registerit;

};