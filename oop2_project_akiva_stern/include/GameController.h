/*
class GameController:
serves as main controller for entire game
*/

#pragma once
#include "WorldOfObjects.h"
#include "LevelDataDisplayer.h"
#include <SFML/Graphics.hpp>
#include "RedBeard.h"
#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;



class GameController {

public:

	GameController() = default;

	void run();

	void mainMenu(sf::RenderWindow& window);

	void finishedGame(sf::RenderWindow& window, sf::Texture* texture);

private:

	WorldOfObjects m_world;
	LevelDataDisplayer m_dataDisplayer;
	sf::View m_defaultView;
};