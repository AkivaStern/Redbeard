#include "LevelDataDisplayer.h"

const int FONT_SIZE = 60;
const int NEW_LEVEL_TEXT_TIME = 2;

LevelDataDisplayer::LevelDataDisplayer()
{
	m_heart = sf::Sprite(*MediaResources::instance().livesTexture());
	m_lives = sf::Text(std::to_string(REDBEARD_LIVES), *MediaResources::instance().font());
	m_points = sf::Text("", *MediaResources::instance().font());
	m_level = sf::Text("", *MediaResources::instance().font());
	m_newLevelStarted = sf::Text("", *MediaResources::instance().font(), FONT_SIZE);

	m_heart.setOrigin(m_heart.getGlobalBounds().width / 2, m_heart.getGlobalBounds().height / 2);
	m_lives.setOrigin(m_lives.getGlobalBounds().width / 2, m_lives.getGlobalBounds().height / 2);
	m_points.setOrigin(m_points.getGlobalBounds().width / 2, m_points.getGlobalBounds().height / 2);
	m_level.setOrigin(m_level.getGlobalBounds().width / 2, m_level.getGlobalBounds().height / 2);

	m_points.setColor(sf::Color::Black);
	m_level.setColor(sf::Color::White);
	m_newLevelStarted.setColor(sf::Color::Red);
}



void LevelDataDisplayer::updateAndDraw(sf::Vector2f pos, sf::Vector2f redPos, int lives, sf::RenderWindow& window, int totalPoints, int levelPoints, int level, bool& justStarted)
{
	m_heart.setPosition(pos + sf::Vector2f(WINDOW_WIDTH / 2 - 50, -WINDOW_HEIGHT / 2 + 34));

	m_lives.setString(std::to_string(lives));
	m_lives.setPosition(pos + sf::Vector2f(WINDOW_WIDTH / 2 - 53, -WINDOW_HEIGHT / 2 + 22));

	m_points.setString(std::to_string(totalPoints) + " + " + std::to_string(levelPoints));
	m_points.setPosition(pos + sf::Vector2f(WINDOW_WIDTH / 2 - 240, -WINDOW_HEIGHT / 2 + 10));

	if (justStarted)
	{
		m_newLevelStarted.setString("LEVEL " + std::to_string(level) + "!");

		m_newLevelStarted.setPosition(redPos + sf::Vector2f(0, -100));

		m_newLevelStartClock.restart();

		justStarted = false;
	}

	else 
	{
		if (m_newLevelStartClock.getElapsedTime().asSeconds() > NEW_LEVEL_TEXT_TIME)
		{
			m_newLevelStarted.setString("");
		}
	}

	m_level.setString("Level " + std::to_string(level));
	m_level.setPosition(pos + sf::Vector2f(WINDOW_WIDTH / 2 - 370, -WINDOW_HEIGHT / 2 + 10));

	window.draw(m_heart);
	window.draw(m_lives);
	window.draw(m_points);
	window.draw(m_level);
	window.draw(m_newLevelStarted);
}