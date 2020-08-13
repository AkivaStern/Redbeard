/*
class LevelDataDisplayer:
for displaying stats, like points, lives, level num
*/

#pragma once
#include "MediaResources.h"
#include "Utilities.h"


class LevelDataDisplayer {

public:

	LevelDataDisplayer();

	void updateAndDraw(sf::Vector2f pos, sf::Vector2f redPos, int lives, sf::RenderWindow& window, int totalPoints, int levelPoints, int level, bool& justStarted);

private:

	sf::Sprite m_heart;
	sf::Text m_lives;
	sf::Text m_points;
	sf::Text m_level;
	sf::Text m_newLevelStarted;
	sf::Clock m_newLevelStartClock;
};