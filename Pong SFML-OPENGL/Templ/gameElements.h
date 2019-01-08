#pragma once
#ifndef _GAMEELEMENTS_H_
#define _GAMEELEMENTS_H_

#include <vector>
#define NOMINMAX
#include <windows.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

class line {
private:
	std::vector<sf::RectangleShape> vec;
public:
	void setLine(sf::RenderWindow& window);
	void drawLine(sf::RenderWindow& window);
};

class player {
private:
	sf::RectangleShape _player;
public:
	void setPlayer(sf::RenderWindow& window, float sizex, float sizey, float posx, float posy);
	sf::RectangleShape& getPlayerBody() { return _player; };
	void drawPlayer(sf::RenderWindow& window);
	bool checkCollision(sf::RectangleShape& ball);
};

class ball {
private:
	sf::RectangleShape _ball;
public:
	void setBall(sf::RenderWindow& window);
	sf::RectangleShape& getBallBody() { return _ball; };
	void drawBall(sf::RenderWindow& window);
};

class score {
private:
	std::string text;
	sf::Text score;
	sf::Font font;
public:
	void setScore(sf::RenderWindow& window, float posx, float posy, float fontSize);
	void addScore();
	sf::Text getScoreBody() { return score; };
	void drawScore(sf::RenderWindow& window);
};

class scoreBoard {
private:
	score player1Score;
	score player2Score;
public:
	void setScoreBoard(sf::RenderWindow& window);
	void drawScoreBoard(sf::RenderWindow& window);
	score& getPlayer1Score() { return player1Score; };
	score& getPlayer2Score() { return player2Score; };

};

#endif _GAMEELEMENTS_H_