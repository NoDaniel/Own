#pragma once
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <vector>
#define NOMINMAX
#include <windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include "gameElements.h"

class gameManagerControl {
private:
	line middleLine;
	player player1;
	player player2;
	ball _ball;
	scoreBoard scoreTable;
	float ballSpeed;
	float numberBounces;
public:
	//Constructor
	gameManagerControl(sf::RenderWindow& window);

	//Main objects of the game
	player& getPlayer1() { return player1; };
	player& getPlayer2() { return player2; };
	ball& getBall() { return _ball; };
	scoreBoard& getScoreBoard() { return scoreTable; };
	line& getMiddleLine() { return middleLine; };

	//WIP
	void draw(sf::RenderWindow& window);
	void controlBallSpeed();
	void currentSpeedDisplay(sf::RenderWindow& window);
	void bounceControl();
	void restartCountdown(sf::RenderWindow& window);

	//getters & setters
	void setBallSpeed(float _speed) { this->ballSpeed = _speed; };
	float getBallSpeed() { return ballSpeed; };
	void setNumberBounces(float bounce) { this->numberBounces = bounce; };
	float getNumberBounces() { return numberBounces; };
};

#endif _GAMEMANANGER_H_