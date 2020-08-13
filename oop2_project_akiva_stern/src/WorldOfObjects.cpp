#include "WorldOfObjects.h"
#include "Factory.h"
#include "MediaResources.h"
#include <map>
#include <sstream>


WorldOfObjects::WorldOfObjects() 
	: m_levelName(FIRST_LEVEL_NAME), m_levelCodesName(FIRST_LEVEL_CODES), m_level(1), m_redBeard(std::make_unique<RedBeard>())
{
	m_background.setOrigin(MediaResources::instance().backgroundTexture()->getSize().x / 2, MediaResources::instance().backgroundTexture()->getSize().y / 2);
	m_background.setTexture(*MediaResources::instance().backgroundTexture());
}

bool WorldOfObjects::setupLevel()
{
	m_fh.open(m_levelName);

	if (!m_fh)
		return false;

	m_wonGame = false;
	m_gameOver = false;
	
	std::string line;
	std::map<char, std::string> codesMap;

	readFileCodes(codesMap, m_levelCodesName);

	int counter = 1;

	while (std::getline(m_fh, line))
	{
		float airOffset = MediaResources::instance().groundTexture()->getSize().x;
		counter++;

		for (int i = 0; i < line.size(); i++)
		{
			auto movableObj = Factory::createMovable(line[i], codesMap[line[i+1]], sf::Vector2f(i * airOffset, counter * airOffset));
			if (movableObj)
			{
				auto st = std::dynamic_pointer_cast<Step>(movableObj); 
				if (st)
				{
					m_steps.emplace_back(st);
				}
				auto red = std::dynamic_pointer_cast<RedBeard>(movableObj);
				if (red)
				{ 
					m_redBeard = std::make_unique<RedBeard>(sf::Vector2f(i * airOffset, counter * airOffset), m_redBeard->getLives(), codesMap[BALL]);
				}				
				else
					m_movables.emplace_back(movableObj);

				continue;
			}
			auto staticObj = Factory::createStatic(line[i], codesMap[line[i + 1]], sf::Vector2f(i * airOffset, counter * airOffset));
			if (staticObj)
			{
				m_statics.emplace_back(staticObj.release());
				continue;
			}
		}
	}

	if (!m_redBeard->isInitialized())
		throw std::runtime_error("must position REDBEARD in world");

	m_water = std::make_unique<Water>(MediaResources::instance().waterTexture(), 
		sf::Vector2f(m_redBeard->getPosition().x, m_redBeard->getPosition().y + MediaResources::instance().waterTexture()->getSize().y /1.5), *m_redBeard, codesMap[WATER]);

	m_background.setPosition(m_redBeard->getPosition());

	 m_bulletin = Bulletin(codesMap[BALL], m_redBeard->getPosition());

	 m_totalPoints += m_levelPoints;

	 m_levelPoints = POINTS + (rand() % POINTS);

	 m_pointsClock.restart();
	 
	 return true;
}


sf::View& WorldOfObjects::updateWorld(sf::View& view, sf::Time& deltaTime)
{
	view.setCenter(m_redBeard->getPosition());

	m_redBeard->setView(view);

	m_background.setPosition(view.getCenter());

	if (m_levelPoints != 0)
	{
		if (m_pointsClock.getElapsedTime().asSeconds() > POINTS_CLOCK)
		{
			m_levelPoints--;
			m_pointsClock.restart();
		}
	}

	m_redBeard->move(deltaTime);

	for (auto& i : m_statics)
	{
		if (collided(*m_redBeard, *i))
			processCollision(*m_redBeard, *i);
	}

	for (auto& i : m_steps)
	{
		updateStep(i);
	}

	for (auto& i : m_movables)
	{
		i->move(deltaTime);

		if (collided(*m_redBeard, *i))
			processCollision(*m_redBeard, *i);

	}

	m_water->move(deltaTime);

	checkIfSubmerged(*m_water, *m_redBeard);

	if (m_redBeard->lostLevel())
	{	
		if (!m_redBeard->getLives())
		{
			m_gameOver = true;
			MediaResources::instance().dry();
			return view;
		}

		restartLevel();
	}


	if (m_redBeard->gotGold())
		proceedToNextLevel();

	return view;
}


void WorldOfObjects::draw(sf::RenderWindow& window)
{
	window.draw(m_background);

	for (auto& i : m_movables)
		i->draw(window);

	for (auto& i : m_statics)
		i->draw(window);

	m_bulletin.draw(window);

	m_redBeard->draw(window);

	m_water->draw(window);
}



void readFileCodes(std::map<char, std::string> & map, std::string file)
{
	ifstream lcHandler(file);
	if (!lcHandler)
		exit(1);

	std::string line;
	while (lcHandler)
	{
		std::getline(lcHandler, line);

		map[line[0]] = line;
	}
}

void WorldOfObjects::restartLevel()
{
	m_redBeard->dropAllBalls();

	m_redBeard->returnKeys();

	m_redBeard = std::make_unique<RedBeard>(m_redBeard->getStartPos(), m_redBeard->getLives(), m_redBeard->ballColors());

	m_background.setPosition(m_redBeard->getPosition());

	m_water = std::make_unique<Water>(MediaResources::instance().waterTexture(), sf::Vector2f(m_redBeard->getPosition().x, m_redBeard->getPosition().y + 
		MediaResources::instance().waterTexture()->getSize().y / 1.5), *m_redBeard, m_water->speed());
}



void WorldOfObjects::proceedToNextLevel()
{
	int currLevel = m_levelName[LEVEL_NUMBER_IN_FILE_NAME] - '0';

	m_levelName[LEVEL_NUMBER_IN_FILE_NAME] = currLevel + '0' + 1;

	m_levelCodesName[LEVEL_NUMBER_IN_FILE_NAME] = currLevel + '0' + 1;

	m_level++;

	m_statics.clear();

	m_movables.clear();

	m_steps.clear();

	m_fh.close();

	if (!setupLevel())
		m_wonGame = true;
	else
		m_justStarted = true;

	m_redBeard->setInitialization(false);
}





void WorldOfObjects::updateStep(std::weak_ptr<Step>& step)
{
	if (auto myStep = step.lock())
	{
		if (m_redBeard->hasNeededBalls(myStep->getDrawable()->getColor()))
		{
			if (!myStep->isActive())
				myStep->activate();
		}
		else
		{
			if (myStep->isActive())
				myStep->disActivate();
		}
	}
}