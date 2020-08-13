#include "Animation.h"



void Animation::update(DrawableObject& drawable, int mod, int offset)
{
	drawable.setIntRect(m_intRects[(m_animCounter % mod) + offset]);

	m_animCounter++;

	m_animationClock.restart();
}

void Animation::addRects(sf::IntRect rect, int num)
{
	for (int i = 0; i < num; i++)
		m_intRects.push_back(sf::IntRect(rect.left * i, rect.top, rect.width, rect.height));
}