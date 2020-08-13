/*
class WorldOfObjects

holds and manages the objects in the virtual world
*/

#pragma once
#include <fstream>
#include <vector>
#include "StaticObject.h"
#include "MovableObject.h"
#include <memory>
#include <string>
#include <iostream>
#include "Ground.h"
#include "Step.h"
#include "RedBeard.h"
#include "CollisionHandling.h"
#include "Water.h"
#include "Ball.h"
#include "Spikes.h"
#include "gold.h"
#include "KeyTriangle.h"
#include "DisappearingStep.h"
#include "Monster.h"
#include "Utilities.h"
#include "Bulletin.h"

using std::shared_ptr;
using std::vector;
using std::ifstream;
using std::string;

const int WINDOW_WIDTHH = 1000;
const int WINDOW_HEIGHTT = 750;




class WorldOfObjects {

public:

	WorldOfObjects();

	bool setupLevel();
	
	sf::View& updateWorld(sf::View& view, sf::Time& deltaTime);

	sf::Vector2f getRedbeardPos() const { return m_redBeard->getPosition(); }

	int getRedbeardLives() const { return m_redBeard->getLives(); }

	int getTotalPoints() const { return m_totalPoints; }

	int getLevelPoints() const { return m_levelPoints; }

	void draw(sf::RenderWindow& window);

	void proceedToNextLevel();

	void restartLevel();

	int getLevel() const { return m_level; }
	
	void setRedbeardDirKey(sf::Keyboard::Key key) { m_redBeard->setDirectionKey(key); }

	bool& justStarted() { return m_justStarted; }

	bool wonGame() const { return m_wonGame; }

	bool gameOver() const { return m_gameOver; }

	void updateStep(std::weak_ptr<Step>& step);

private:

	ifstream m_fh;
	vector<std::unique_ptr<StaticObject>> m_statics;
	vector<shared_ptr<MovableObject>> m_movables;
	vector<std::weak_ptr<Step>> m_steps;
	sf::Sprite m_background;
	std::unique_ptr<RedBeard> m_redBeard;
	std::unique_ptr<Water> m_water;
	std::string m_levelName;
	std::string m_levelCodesName;
	Bulletin m_bulletin;
	int m_totalPoints = 0;
	int m_levelPoints = 0;
	sf::Clock m_pointsClock;
	bool m_gameOver;
	bool m_wonGame;
	int m_level;
	bool m_justStarted = true;
};


void readFileCodes(std::map<char, std::string>& map, std::string file);


