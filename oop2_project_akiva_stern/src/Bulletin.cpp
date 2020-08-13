#include "Bulletin.h"
const int FONT_SIZE = 25;
const int OFFSET = 35;
const int HEIGHT_OFFSET = 14;
const int INITIAL_LEFT_OFFSET = -4;
const int BLUE_POS = 2;
const int PURPLE_POS = 4;
const int RED_POS = 6;
const int YEL_POS = 8;

Bulletin::Bulletin(std::string ballColors, sf::Vector2f pos)
{
	if (ballColors.size() != NUM_OF_COLORS * 2 + 1)
		throw std::runtime_error("missing ball bag numbers, or improper format");

	auto currPos = pos + sf::Vector2f(MediaResources::instance().groundTexture()->getSize().x, INITIAL_LEFT_OFFSET);

	m_bulletin = sf::Sprite(*MediaResources::instance().bulletinTexture());

	m_bulletin.setPosition(currPos);

	sf::Text text("", *MediaResources::instance().font(), FONT_SIZE);

	text.setColor(sf::Color::Black);

	text.setString(std::to_string(ballColors[BLUE_POS] - '0'));

	currPos += sf::Vector2f(OFFSET, HEIGHT_OFFSET);

	text.setPosition(currPos);

	m_bulletinNums.push_back(text);

	text.setString(std::to_string(ballColors[RED_POS] - '0'));

	currPos += sf::Vector2f(0, OFFSET);

	text.setPosition(currPos);

	m_bulletinNums.push_back(text);

	text.setString(std::to_string(ballColors[YEL_POS] - '0'));

	currPos += sf::Vector2f(OFFSET * 2, 0);

	text.setPosition(currPos);

	m_bulletinNums.push_back(text);

	text.setString(std::to_string(ballColors[PURPLE_POS] - '0'));

	currPos += sf::Vector2f(0, -OFFSET);

	text.setPosition(currPos);

	m_bulletinNums.push_back(text);
}


void Bulletin::draw(sf::RenderWindow& window)
{
	window.draw(m_bulletin);

	for (auto& i : m_bulletinNums)
		window.draw(i);
}