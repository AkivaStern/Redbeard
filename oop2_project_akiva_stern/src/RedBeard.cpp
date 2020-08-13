#include "RedBeard.h"
#include "Factory.h"


const int REDBEARD_HEIGHT = 93;
const int REDBEARD_WIDTH = 70;
const int REDBEARDS_PER_LINE_SP_SHEET = 21;
const float RED_FRAME_SWITCH = 0.1;
const int DEAD_NUM_FRAMES = 7;
const int DEAD_OFFSET = 14;
const int DROWN_NUM_FRAMES = 2;
const int DROWN_OFFSET = 11;
const int STAND_NUM_FRAMES = 6;
const int RUN_NUM_FRAMES = 4;
const int RUN_OFFSET = 6;
const int IN_AIR_NUM_FRAMES = 2;
const int IN_AIR_OFFSET = 12;




bool RedBeard::m_registerit = Factory::registeritMovable(REDBEARD, [](std::string str, sf::Vector2f pos) -> std::shared_ptr<MovableObject>
	{
		return std::make_shared<RedBeard>();
	});


RedBeard::RedBeard(sf::Vector2f pos, int lives, std::string ballColors) 
	: MovableObject(MediaResources::instance().redbeardTexture(), pos, sf::IntRect(0, 0, REDBEARD_WIDTH, REDBEARD_HEIGHT)), m_lives(lives), m_ballColors(ballColors)
{
	m_myMove = std::make_unique<KeyboardMove>();
	
	setBallBag(ballColors);

	m_animation.addRects(sf::IntRect(REDBEARD_WIDTH, 0, REDBEARD_WIDTH, REDBEARD_HEIGHT), REDBEARDS_PER_LINE_SP_SHEET);

	m_startPos = pos;

	m_underWaterTime.setFont(*MediaResources::instance().font());
	m_underWaterTime.setColor(sf::Color::Black);
	m_underWaterTime.setPosition(getPosition() + sf::Vector2f(0, -getDrawable()->getGlobalBounds().height));

	m_initialized = true;
}


void RedBeard::submerge()
{
	if (!m_submerged)
	{
		m_underWaterClock.restart();
		m_submerged = true;
	}
}

void RedBeard::setDirectionKey(sf::Keyboard::Key keyCode)
{
	m_keyDir = keyCode;
	updateDirection();
}


void RedBeard::updateDirection()
{
	switch (m_keyDir)
	{
	case sf::Keyboard::Key::Right:

		getDirection() = sf::Vector2f(REDBEARD_SPEED, 0);
		break;
	case sf::Keyboard::Key::Left:

		getDirection() = sf::Vector2f(-REDBEARD_SPEED, 0);
		break;
	case sf::Keyboard::Key::Space:
	{
		if (!m_onGround)
			return;

		MediaResources::instance().jumpSound();

		m_onGround = false;
		m_midJump = true;
		m_beforeJumpY = getPosition().y; 
	}

	break;
	case sf::Keyboard::Key::BackSpace:
		getDirection() = sf::Vector2f(0, 0);
		break;
	}
}



void RedBeard::draw(sf::RenderWindow& window) 
{

	if (m_dead)
	{
		if (int(m_animation.getElapsed() > RED_FRAME_SWITCH))
		{
			m_animation.update(*getDrawable(), DEAD_NUM_FRAMES, DEAD_OFFSET);

			if ((m_animation.getCounter() % DEAD_NUM_FRAMES) + DEAD_OFFSET == REDBEARDS_PER_LINE_SP_SHEET - 1)
			{
				m_roundOver = true;
				return;
			}
		}

		getDrawable()->draw(window);
		return;
	}

	if (m_submerged)
	{
		if (int(m_animation.getElapsed() > RED_FRAME_SWITCH))
		{
			m_animation.update(*getDrawable(), DROWN_NUM_FRAMES, DROWN_OFFSET);
			m_underWaterTime.setString(std::to_string(UNDERWATER_ALLOWED_TIME - int(m_underWaterClock.getElapsedTime().asSeconds())));
		}

		if (m_underWaterClock.getElapsedTime().asSeconds() > UNDERWATER_ALLOWED_TIME)
			this->kill();
	}

	else 
	{
		m_underWaterTime.setString("");

		bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
		bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

		if (int(m_animation.getElapsed() > RED_FRAME_SWITCH) && m_onGround && !leftPressed && !rightPressed)
		{
			m_animation.update(*getDrawable(), STAND_NUM_FRAMES);
		}

		if (int(m_animation.getElapsed() > RED_FRAME_SWITCH) && (leftPressed || rightPressed) && !m_midFall && !m_midJump)
		{
			m_animation.update(*getDrawable(), RUN_NUM_FRAMES, RUN_OFFSET);
		}
		else if (int(m_animation.getElapsed() > RED_FRAME_SWITCH) && (m_midFall || m_midJump))
		{
			m_animation.update(*getDrawable(), IN_AIR_NUM_FRAMES, IN_AIR_OFFSET);
		}
	}

	if (m_keyDir == sf::Keyboard::Key::Left)
		getDrawable()->flipObj(-1);
	if (m_keyDir == sf::Keyboard::Key::Right)
		getDrawable()->flipObj(1);

	getDrawable()->draw(window);
	window.draw(m_underWaterTime);
}


void RedBeard::kill()
{
	if (m_dead)
		return;

	m_dead = true;

	m_animation.makeCounterZero();

	m_lives--;

	MediaResources::instance().kill();
}


void RedBeard::returnKeys()
{
	for (auto& i : m_keys)
		i->returnKey();

	m_keys.clear();
}