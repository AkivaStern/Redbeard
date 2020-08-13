#include "DisappearingStep.h"
#include "Factory.h"
#include "Utilities.h"


bool DisappearingStep::m_registerit = Factory::registeritMovable(DISAPPEARING_STEP, [](std::string str, sf::Vector2f pos) -> std::shared_ptr<MovableObject>
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
			throw std::runtime_error("missing params for: " + std::to_string(str[0] -'0'));


		float width;
		if (line >> data)
		{
			width = std::stof(data);
		}
		else
			throw std::runtime_error("missing params for: " + std::to_string(str[0] - '0'));

		return std::make_shared<DisappearingStep>(color, width, pos);
	});



DisappearingStep::DisappearingStep(sf::Color color, float width, sf::Vector2f pos) 
	: Step(color, sf::Vector2f(0, 0), sf::Vector2f(0, 0), width, pos)
{
	getDrawable()->setColor(color, false);

	getDirection() = sf::Vector2f(0, 0);
}

void DisappearingStep::activate() 
{
	getDrawable()->setColor(this->getDrawable()->getColor(), true);

	m_isActive = true;
}


void DisappearingStep::disActivate() 
{
	getDrawable()->setColor(this->getDrawable()->getColor(), false);

	m_isActive = false;
}