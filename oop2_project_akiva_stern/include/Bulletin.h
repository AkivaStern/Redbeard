/*
class Bulletin:
Bulletin board object to display needed balls per color, in a current level
*/

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "MediaResources.h"
#include "Ball.h"



class Bulletin {

public:

	Bulletin() = default;

	Bulletin(std::string ballColors, sf::Vector2f pos);

	void draw(sf::RenderWindow& window);

private:

	sf::Sprite m_bulletin;
	std::vector<sf::Text> m_bulletinNums;
};