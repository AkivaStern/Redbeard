/*
Multi-Methods for collision handling
*/

#pragma once

#include "GameObject.h"
#include <iostream>
#include <typeinfo>


class Water;
class RedBeard;


struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObject& a, GameObject& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {}
};

bool collided(GameObject& object1, GameObject& object2);

void processCollision(GameObject& object1, GameObject& object2);

void checkIfSubmerged(Water& water, RedBeard& redbeard);
