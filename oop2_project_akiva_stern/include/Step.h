/*
class Step
*/

#pragma once
#include "MovableObject.h"
#include "BorderedMove.h"

class Step : public MovableObject {
public:

	Step(sf::Color color, sf::Vector2f bounds, sf::Vector2f constDir, float width, sf::Vector2f pos);

	bool isActive() const { return m_isActive; }

	virtual void activate();

	virtual void disActivate();

protected:

	bool m_isActive = false;

private:

	 sf::Vector2f m_movingDir;
	 static bool m_registerit;
};