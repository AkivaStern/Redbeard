#include "Monster.h"
#include "Factory.h"

const sf::Vector2f MONSTER_OFFSET = sf::Vector2f(0, -8);
const float MONSTER_FRAME_SWITCH = 0.15;
const int MONSTER_HEIGHT = 100;
const int MONSTER_WIDTH = 139;
const int MONSTERS_LINE1_SP_SHT = 5;
const int MONSTERS_LINE2_SP_SHT = 2;


bool Monster::m_registerit = Factory::registeritMovable(MONSTER, [](std::string str, sf::Vector2f pos) -> std::shared_ptr<MovableObject>
	{
		float lbnd, rbnd, xDir, yDir;

		std::stringstream line(str);

		std::string data;

		line >> data;

		interpretMovablesParams(line, lbnd, rbnd, xDir, yDir);

		return std::make_shared<Monster>(MediaResources::instance().monsterTexture(), sf::Vector2f(lbnd, rbnd), sf::Vector2f(xDir, yDir), pos);
	});


Monster::Monster(sf::Texture* texture, sf::Vector2f bounds, sf::Vector2f constDir, sf::Vector2f pos)
	: MovableObject(texture, pos + MONSTER_OFFSET, sf::IntRect(0, 0, MONSTER_WIDTH, MONSTER_HEIGHT)), m_movingDir(constDir)
{
	m_myMove = std::make_unique<BorderedMove>(bounds, constDir, *this);

	getDirection() = m_movingDir;

	m_animation.addRects(sf::IntRect(MONSTER_WIDTH, 0, MONSTER_WIDTH, MONSTER_HEIGHT), MONSTERS_LINE1_SP_SHT);

	m_animation.addRects(sf::IntRect(MONSTER_WIDTH, MONSTER_HEIGHT, MONSTER_WIDTH, MONSTER_HEIGHT), MONSTERS_LINE2_SP_SHT);
}


void Monster::draw(sf::RenderWindow& window) 
{
	if (int(m_animation.getElapsed() > MONSTER_FRAME_SWITCH))
	{
		m_animation.update(*getDrawable(), MONSTERS_LINE1_SP_SHT + MONSTERS_LINE2_SP_SHT);
	}

	if (getDirection().x < 0)
		getDrawable()->flipObj(-1);
	else 
		getDrawable()->flipObj(1);

	getDrawable()->draw(window);
}
