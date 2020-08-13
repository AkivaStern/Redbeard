#include "WaterMove.h"
#include "RedBeard.h"

const int WAVES_HORIZONTAL_TIME = 5;

WaterMove::WaterMove(RedBeard& red, float speed) : m_red(red), m_speed(speed)
{
	m_wavesClock.restart();
}


void WaterMove::move(sf::Time deltaTime, MovableObject& obj) 
{
	if (m_wavesClock.getElapsedTime().asSeconds() > WAVES_HORIZONTAL_TIME)
	{
		m_wavesClock.restart();
		m_dir = -m_dir;
	}

	if (m_red.getDirection() != sf::Vector2f(0, 0) && (!m_red.isDisableLeft() && !m_red.isDisableRight()))
		obj.getDrawable()->move((m_red.getDirection() + sf::Vector2f(0, -m_speed)) * deltaTime.asSeconds());

	else
		obj.getDrawable()->move(sf::Vector2f(0, -m_speed) * deltaTime.asSeconds());

	if (m_red.getStepStandingOn())
	{
		obj.getDrawable()->move(sf::Vector2f(m_red.getStepStandingOn()->getDirection().x, 0) * deltaTime.asSeconds());
	}

	obj.getDrawable()->move(m_dir * deltaTime.asSeconds());
}