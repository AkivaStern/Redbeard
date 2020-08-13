#include "KeyboardMove.h"
#include "RedBeard.h"
#include "MovableObject.h"


const float JUMP_LOCK_TIME = 0.1;

void KeyboardMove::move(sf::Time deltaTime, MovableObject& controllableObject)
{
		RedBeard* r = static_cast<RedBeard*>(&controllableObject); 

		if (r->isDead())
			return;

		if (r->getStepStandingOn())
		{
			r->getDrawable()->move(r->getStepStandingOn()->getDirection() * deltaTime.asSeconds());
			r->getView().move(r->getStepStandingOn()->getDirection() * deltaTime.asSeconds());
			r->getText().move(r->getStepStandingOn()->getDirection() * deltaTime.asSeconds());
		}
		r->removeStepStandingOn();

		if (!((r->isDisableRight() && r->getDirection() == sf::Vector2f(REDBEARD_SPEED, 0))
					|| (r->isDisableLeft() && r->getDirection() == sf::Vector2f(-REDBEARD_SPEED, 0))))
		{
			r->getDrawable()->move(r->getDirection() * deltaTime.asSeconds());
			r->getView().move(r->getDirection() * deltaTime.asSeconds());
			r->getText().move(r->getDirection() * deltaTime.asSeconds());
		}

		if (r->isMidJump())
		{
			r->setOnGround(false);

			if (r->getBeforeJumpY() - controllableObject.getPosition().y < JUMP_HEIGHT)
			{
				r->getDrawable()->move(sf::Vector2f(0, -JUMP_SPEED * deltaTime.asSeconds()));
				r->getView().move(sf::Vector2f(0, -JUMP_SPEED * deltaTime.asSeconds()));
				r->getText().move(sf::Vector2f(0, -JUMP_SPEED * deltaTime.asSeconds()));
			}
			else
			{
				r->getJumpClock().restart();
				r->setMidFall(true);
				r->setMidJump(false);
			}
		}

		if (r->getJumpClock().getElapsedTime().asSeconds() < JUMP_LOCK_TIME)
			return;

		if ((r->isMidFall()) && !(r->isMidJump()))
		{
			r->getDrawable()->move(sf::Vector2f(0, FALL_SPEED * deltaTime.asSeconds()));
			r->getView().move(sf::Vector2f(0, FALL_SPEED * deltaTime.asSeconds()));
			r->getText().move(sf::Vector2f(0, FALL_SPEED * deltaTime.asSeconds()));
			r->setOnGround(false);
		}

		r->setMidFall(true);
		r->setOnGround(false);
		r->setDisableLeft(false);
		r->setDisableRight(false);
		r->setDisableFall(false);
	}


