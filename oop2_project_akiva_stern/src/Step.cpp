#include "Step.h"
#include "Factory.h"
#include "Utilities.h"


bool Step::m_registerit = Factory::registeritMovable(STEP, [](std::string str, sf::Vector2f pos) -> std::shared_ptr<MovableObject>
	{
		std::string data;
		std::stringstream line(str);

		line >> data;

		sf::Color color;

		if (line >> data)
		{
			color = convertKeyToColor(data[0]);
		}
		else
			throw(std::runtime_error("missing params for step: " + std::to_string(str[0] - '0')));

		float lbnd;
		float rbnd;
		float xDir;
		float yDir;
		float width;

		interpretMovablesParams(line, lbnd, rbnd, xDir, yDir);
		if (line >> data)
		{
			width = std::stof(data);
		}
		else
			throw(std::runtime_error("missing params for step: " + std::to_string(str[0] - '0')));

		return std::make_shared<Step>(color, sf::Vector2f(lbnd, rbnd), sf::Vector2f(xDir, yDir), width, pos);
	});


Step::Step(sf::Color color, sf::Vector2f bounds, sf::Vector2f constDir, float width, sf::Vector2f pos)
	: MovableObject(color, width, pos), m_movingDir(constDir)
{
	m_myMove = std::make_unique<BorderedMove>(bounds, constDir, *this);
}

void Step::activate()
{
	getDirection() = m_movingDir;
	m_isActive = true;
}

void Step::disActivate()
{
	if (m_isActive)
	{
		m_movingDir = getDirection();

		getDirection() = sf::Vector2f(0, 0);
	}
	m_isActive = false;
}