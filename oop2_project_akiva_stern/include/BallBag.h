/*
class BallBag:
Holds info regaring Balls collected/needed to collect
*/

#pragma once
#include <map>
#include <memory>
#include <vector>
#include "Ball.h"
#include "Utilities.h"

using std::vector;
using std::map;
using std::shared_ptr;


class BallBag {

public:
	BallBag();
	
	void setBallsNeededForColor(sf::Color color, int needed) { m_bag[convertColorToKey(color)].second = needed; }
	
	void setBallBag(std::string line);

	void add(Ball* ball) { m_bag[convertColorToKey(ball->getDrawable()->getColor())].first.emplace_back(ball); }
	
	void dropAll();

	bool hasCollectedAllForColor(sf::Color color) { return m_bag[convertColorToKey(color)].first.size() >= m_bag[convertColorToKey(color)].second; }
	
private:

	map<char, std::pair<vector<Ball*>, int>> m_bag;
};