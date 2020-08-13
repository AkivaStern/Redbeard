/*
class BorderedMove:
contains method (to be called virtually in our game) to move according to set borders
*/

#pragma once
#include "MoveHandling.h";
#include "MovableObject.h" 

const int EPS = 3;



class BorderedMove : public MoveHandling {
	
public:

	BorderedMove(sf::Vector2f borders, sf::Vector2f constDir, MovableObject& obj);

	void move(sf::Time deltaTime, MovableObject& obj) override;

private:

	float m_a;
	float m_b;
	float m_leftBorder; 
	float m_rightBorder;
	const sf::Vector2f m_constDir;
};