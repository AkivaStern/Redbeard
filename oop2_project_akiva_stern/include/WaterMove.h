/*
class WaterMove
*/

#pragma once
#include "MoveHandling.h";
class RedBeard;

const int WAVES_SPEED = 80;

class WaterMove : public MoveHandling {

public:

	WaterMove(RedBeard& red, float speed);

	void move(sf::Time deltaTime, MovableObject& obj) override;

private:

	RedBeard& m_red; 
	float m_speed;
	sf::Clock m_wavesClock;
	sf::Vector2f m_dir = sf::Vector2f(WAVES_SPEED, 0);
};