/*
class RedBeard:

serves as main player of game
*/

#pragma once
#include "MovableObject.h"
#include "KeyboardMove.h"
#include "Step.h"
#include <unordered_map>
#include "Utilities.h"
#include "KeyTriangle.h"
#include "Animation.h"
#include "BallBag.h"

class WaterMove;



class RedBeard : public MovableObject {

public:

	RedBeard() : m_lives(REDBEARD_LIVES) {}

	RedBeard(sf::Vector2f pos, int lives, std::string ballColors);

	void addToBag(Ball* ball){ m_ballBag.add(ball); }

	void submerge();

	Step* getStepStandingOn() const { return m_step_standing_on; }

	void removeStepStandingOn() { m_step_standing_on = nullptr; }
	
	void dryOff() { m_submerged = false; }
	
	bool hasNeededBalls(sf::Color color) { return m_ballBag.hasCollectedAllForColor(color); }
	
	void setBallsNeededForColor(sf::Color color, int needed) { m_ballBag.setBallsNeededForColor(color, needed); }
	
	void setInitialization(bool val) { m_initialized = val; }

	bool isInitialized() const { return m_initialized; }

	void setBallBag(std::string line) { m_ballBag.setBallBag(line); }
	
	void setDirectionKey(sf::Keyboard::Key keyCode);

	void updateDirection();

	void setStandingStep(Step* s) { m_step_standing_on = s; }
	
	void setOnGround(bool val) { m_onGround = val; }
	
	void setMidJump(bool val) { m_midJump = val; }
	
	void setMidFall(bool val) { m_midFall = val; }
	
	void setDisableFall(bool val) { m_disableFall = val; }
	
	void setDisableRight(bool val) { m_disableRight = val; }
	
	void setDisableLeft(bool val) { m_disableLeft = val; }
	
	bool isDisableLeft() const { return m_disableLeft; }
	
	bool isDisableRight() const { return m_disableRight; }
	
	bool isMidJump() const { return m_midJump; }

	bool isMidFall() const { return m_midFall; }

	void setView(sf::View& view) { m_view = view; }
	
	sf::View& getView() { return m_view; }
	
	sf::Color getCurrentCollectionColor() const { return m_currentColorCollected; }

	void setCurrentCollectionColor(sf::Color color) { m_currentColorCollected = color; }

	void dropAllBalls() { m_ballBag.dropAll(); }
	
	bool lostLevel() const { return m_roundOver; }

	int getLives() { return m_lives; }

	void draw(sf::RenderWindow& window) override;

	float getBeforeJumpY() const { return m_beforeJumpY; }

	sf::Clock& getJumpClock() { return m_peakHeightTimer; }

	bool isDead() { return m_dead; }

	void kill();

	void addKey(KeyTriangle* key) { m_keys.push_back(key); }

	void returnKeys();

	sf::Vector2f getStartPos() { return m_startPos; }

	std::string ballColors() const { return m_ballColors; }

	void collectGold() { m_gotGold = true; }
	
	bool gotGold() const { return m_gotGold; }
	
	sf::Text& getText()  { return m_underWaterTime; }

private:    

	bool m_onGround = false;
	bool m_midJump = false;
	bool m_midFall = false;
	float m_beforeJumpY;
	bool m_disableFall = false;
	bool m_disableLeft = false;
	bool m_disableRight = false;
	sf::Clock m_peakHeightTimer;
	sf::Keyboard::Key m_keyDir = sf::Keyboard::Key::BackSpace;
	Step* m_step_standing_on = nullptr;
	sf::Sprite* m_background = nullptr;
	sf::View m_view;
	BallBag m_ballBag;
	sf::Color m_currentColorCollected = sf::Color::Transparent;
	static bool m_registerit;
	Animation m_animation;
	bool m_dead = false;
	bool m_roundOver = false;
	bool m_submerged = false;
	sf::Clock m_underWaterClock;
	int m_lives;
	sf::Vector2f m_startPos;
	std::string m_ballColors;
	std::vector<KeyTriangle*> m_keys;
	bool m_gotGold = false;
	sf::Text m_underWaterTime;
	bool m_initialized = false;
};



