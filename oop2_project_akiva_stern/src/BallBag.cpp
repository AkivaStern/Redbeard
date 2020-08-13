#include "BallBag.h"

BallBag::BallBag()
{
	m_bag[BLUE] = std::make_pair(vector<Ball*>(), 0); 
	m_bag[PURPLE] = std::make_pair(vector<Ball*>(), 0);
	m_bag[RED] = std::make_pair(vector<Ball*>(), 0);
	m_bag[YELLOW] = std::make_pair(vector<Ball*>(), 0);
}

void BallBag::setBallBag(std::string line)
{
	if (line.size() != NUM_OF_COLORS * 2 + 1)
		throw std::runtime_error("missing ball bag numbers, or improper format");

	map<char, std::pair < vector<Ball*>, int>>::iterator it;

	int j;
	for (it = m_bag.begin(), j = 2; it != m_bag.end(); it++, j += 2)
	{
		it->second.second = line[j] - '0';
	}
}

void BallBag::dropAll()
{
	for (auto& [key, val] : m_bag)
	{
		for (auto& i : val.first)
		{
			i->getDrawable()->setColor(i->getDefaultColor(), 1);

			i->drop();
		}

		val.first.clear();
	}
}