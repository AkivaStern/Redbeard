#include "Factory.h"
#include "StaticObject.h"
#include "MovableObject.h"

std::shared_ptr<MovableObject> Factory::createMovable(const char name, std::string& line, sf::Vector2f pos) {
	auto it = Factory::getMovableMap().find(name);
	if (it == Factory::getMovableMap().end())
		return nullptr;

	return it->second(line, pos);
}

std::unique_ptr<StaticObject> Factory::createStatic(const char name, std::string& line, sf::Vector2f pos) {
	auto it = Factory::getStaticMap().find(name);
	if (it == Factory::getStaticMap().end())
		return nullptr;

	return it->second(line, pos);
}

bool Factory::registeritStatic(const char name, pFncStatic f) {
	Factory::getStaticMap().emplace(name, f);
	return true;
}

bool Factory::registeritMovable(const char name, pFncMovable f) {
	Factory::getMovableMap().emplace(name, f);
	return true;
}

void interpretMovablesParams(std::stringstream& line, float& lbnd, float& rbnd, float& xDir, float& yDir)
{
	std::string data;
	if (line >> data)
	{
		lbnd = std::stof(data);
	}
	else
		throw std::runtime_error("missing movables pram");

	if (line >> data)
	{
		rbnd = std::stof(data);
	}
	else
		throw std::runtime_error("missing movables pram");

	if (line >> data)
	{
		xDir = std::stof(data);
	}
	else
		throw std::runtime_error("missing movables pram");
	if (line >> data)
	{
		yDir = std::stof(data);
	}
	else
		throw std::runtime_error("missing movables pram");
}


