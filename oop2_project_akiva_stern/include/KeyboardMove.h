/*
class KeyboardMove:
for movement of object according to keyboard
*/

#pragma once
#include "MoveHandling.h";

const int REDBEARD_SPEED = 460;
const int JUMP_SPEED = 620;
const int FALL_SPEED = 450;
const int JUMP_HEIGHT = 210;



class KeyboardMove : public MoveHandling {

public:
	
	void move(sf::Time deltaTime, MovableObject& controllableObject) override;

};