/*
class Factory:
utilizes Factory design pattern for creating objects
*/


#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <SFML/graphics.hpp>
#include <sstream>



class StaticObject;
class MovableObject;




class Factory {
public:

	using pFncStatic = std::unique_ptr<StaticObject>(*)(std::string, sf::Vector2f);

	using pFncMovable = std::shared_ptr<MovableObject>(*)(std::string, sf::Vector2f);

	static std::shared_ptr<MovableObject> createMovable(const char name, std::string& line, sf::Vector2f);

	static std::unique_ptr<StaticObject> createStatic(const char name, std::string& line, sf::Vector2f);

	static bool registeritStatic(const char name, pFncStatic);

	static bool registeritMovable(const char name, pFncMovable);

private:

	static auto& getStaticMap() {
		static std::map<char, pFncStatic> map;
		return map;
	}
	static auto& getMovableMap() {
		static std::map<char, pFncMovable> map;
		return map;
	}
};


void interpretMovablesParams(std::stringstream& line, float& lbnd, float& rbnd, float& xDir, float& yDir);


