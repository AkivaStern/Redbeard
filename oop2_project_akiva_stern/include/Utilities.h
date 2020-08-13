/*
Utilities.h

for consts / enums 
*/


#pragma once
#include <SFML/Graphics.hpp>



const std::string WINDOW_STR = "REDBEARD 2020";

const std::string FIRST_LEVEL_NAME = "level1.txt";
const std::string FIRST_LEVEL_CODES = "level1codes.txt";

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 750;

const int UNDERWATER_ALLOWED_TIME = 5;

const int MUSIC_VOL = 85;
const int UNDERWATER_MUS_VOL = 15;	

const int REDBEARD_LIVES = 5;

const int DEFAULT_RADIUS = 10;
const int DEFAULT_BALL_POINTS = 30;

const int TRIANGLE_SIDE_SIZE = 65;
const int TRIANGLE_POINTS = 3;

const int POINTS = 3500;
const float POINTS_CLOCK = 0.1;

const int LEVEL_NUMBER_IN_FILE_NAME = 5;

const int NUM_OF_COLORS = 4;


enum OBJECT_CHARS { REDBEARD = '/', BALL = 'o', GOLD = '*', GROUND = '#', TRIANGLE_KEY = '@',
	MONSTER = '!', SPIKES = '^', STEP = '+', DISAPPEARING_STEP = '-', WATER = 'w' };


enum Color { RED = 'r', BLUE = 'b', PURPLE = 'p' , YELLOW = 'y'};


namespace {

	Color convertColorToKey(sf::Color color)
	{
		if (color == sf::Color::Red)
			return RED;

		if (color == sf::Color::Blue)
			return BLUE;

		if (color == sf::Color::Magenta)
			return PURPLE;

		if (color == sf::Color::Yellow)
			return YELLOW;

		throw std::exception("color not registered");
	}

	sf::Color convertKeyToColor(char c)
	{
		switch (c)
		{
		case RED:
			return sf::Color::Red;
			break;
		case BLUE:
			return sf::Color::Blue;
			break;
		case PURPLE:
			return sf::Color::Magenta;
			break;
		case YELLOW:
			return sf::Color::Yellow;
			break;
		}
		return sf::Color::Transparent;
	}
}