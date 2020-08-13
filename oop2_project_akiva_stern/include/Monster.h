/*
class Monster:
*/

#pragma once
#include "MovableObject.h"
#include "BorderedMove.h"
#include "Animation.h"



class Monster : public MovableObject {
public:

	Monster(sf::Texture* texture, sf::Vector2f bounds, sf::Vector2f constDir, sf::Vector2f pos);

	void draw(sf::RenderWindow& window) override;

private:
	const sf::Vector2f m_movingDir;
	static bool m_registerit;
	Animation m_animation;
};