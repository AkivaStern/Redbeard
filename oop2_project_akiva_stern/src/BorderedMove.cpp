#include "BorderedMove.h"


BorderedMove::BorderedMove(sf::Vector2f borders, sf::Vector2f constDir, MovableObject& obj)
	: m_constDir(constDir), m_a(borders.x), m_b(borders.y)
{

	float x;

	if (m_constDir.y != 0)
		x = obj.getDrawable()->getPosition().y;

	else
		x = obj.getDrawable()->getPosition().x;

	m_leftBorder = x - (obj.getDrawable()->getGlobalBounds().width * borders.x);

	m_rightBorder = x + (obj.getDrawable()->getGlobalBounds().width * borders.y);
}


void BorderedMove::move(sf::Time deltaTime, MovableObject& obj) 
{
	if (obj.getDirection() == sf::Vector2f(0, 0))
		return;

	obj.getDrawable()->move(obj.getDirection() * deltaTime.asSeconds());

	if (obj.getDirection().y != 0)
	{
		if (abs(obj.getDrawable()->getPosition().y - m_rightBorder) < EPS)
			obj.getDirection() = -m_constDir;

		else
			if (abs(m_leftBorder - obj.getDrawable()->getPosition().y) < EPS)
				obj.getDirection() = m_constDir;
	}
	else
	{
		if (abs(obj.getDrawable()->getPosition().x - m_rightBorder) < EPS)
			obj.getDirection() = -m_constDir;

		else
			if (abs(m_leftBorder - obj.getDrawable()->getPosition().x) < EPS)
				obj.getDirection() = m_constDir;
	}
}
