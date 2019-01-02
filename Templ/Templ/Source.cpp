#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <iostream>
#include <math.h> 
#include <stdlib.h>
#include <time.h>
#include "gameManager.h"

#define _SPEED 5
#define BALL_START_SPEED 5
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862

void function(bool& wFlag, bool& sFlag, bool& upFlag, bool& downFlag, sf::RenderWindow& window, gameManagerControl& gameManager, float& deg, float &ballSpeed) {


	if (wFlag) {
		if (gameManager.getPlayer1().getPlayerBody().getPosition().y - _SPEED - gameManager.getPlayer1().getPlayerBody().getSize().x / 2 >= 0) {
			gameManager.getPlayer1().getPlayerBody().sf::Transformable::move(sf::Vector2f(0.f, -_SPEED));
		}
	}
	if (sFlag) {
		if (window.getSize().y >= gameManager.getPlayer1().getPlayerBody().getPosition().y + _SPEED + gameManager.getPlayer1().getPlayerBody().getSize().x / 2) {
			gameManager.getPlayer1().getPlayerBody().sf::Transformable::move(sf::Vector2f(0.f, _SPEED));
		}
	}
	if (upFlag) {
		if (gameManager.getPlayer2().getPlayerBody().getPosition().y - _SPEED - gameManager.getPlayer2().getPlayerBody().getSize().x / 2 >= 0) {
			gameManager.getPlayer2().getPlayerBody().sf::Transformable::move(sf::Vector2f(0.f, -_SPEED));
		}
	}
	if (downFlag) {
		if (window.getSize().y >= gameManager.getPlayer2().getPlayerBody().getPosition().y + _SPEED + gameManager.getPlayer2().getPlayerBody().getSize().x / 2) {
			gameManager.getPlayer2().getPlayerBody().sf::Transformable::move(sf::Vector2f(0.f, _SPEED));
		}
	}

	float angle = deg * PI / 180.f;
	if (window.getSize().x >= gameManager.getBall().getBallBody().getPosition().x + cos(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().x / 2 &&
		window.getSize().y >= gameManager.getBall().getBallBody().getPosition().y + sin(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().y / 2 &&
		gameManager.getBall().getBallBody().getPosition().x + cos(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().x / 2 >= 0 &&
		gameManager.getBall().getBallBody().getPosition().y + sin(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().y / 2 >= 0) {

		gameManager.getBall().getBallBody().sf::Transformable::move(sf::Vector2f(cos(angle) * ballSpeed, sin(angle) * ballSpeed));
	}
	else {
		if (deg > 360) deg -= 360;
		if (deg < 0) deg += 360;
		if (window.getSize().x < gameManager.getBall().getBallBody().getPosition().x + cos(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().x / 2) {
			gameManager.getScoreBoard().getPlayer1Score().addScore();
			gameManager.getBall().getBallBody().setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
			reset(window, gameManager);
			deg = customRand() - 90.f;
		}
		else if (gameManager.getBall().getBallBody().getPosition().x + cos(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().x / 2 < 0) {
			gameManager.getScoreBoard().getPlayer2Score().addScore();
			gameManager.getBall().getBallBody().setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
			reset(window, gameManager);
			deg = customRand() - 90.f;
		}
		else if (window.getSize().y < gameManager.getBall().getBallBody().getPosition().y + sin(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().y / 2) {
			if (deg > 0 && deg < 90) {
				deg = deg - (180 - (90 - deg) * 2);
			}
			else if (deg > 90 && deg < 180) {
				deg = deg + (180 - (deg - 90) * 2);
			}
			else if (deg == 90) {
				std::cout << "90deg\n";
				//deg += 1;
			}
		}
		else if (gameManager.getBall().getBallBody().getPosition().y + sin(angle) * ballSpeed + gameManager.getBall().getBallBody().getSize().y / 2 < 0) {
			if (deg > 270 && deg < 360) {
				deg = deg + (360 - deg) * 2;
			}
			else if (deg > 180 && deg < 270) {
				deg = deg - ((deg - 180) * 2);
			}
		}
		angle = deg * PI / 180;
		gameManager.getBall().getBallBody().sf::Transformable::move(sf::Vector2f(cos(angle) * ballSpeed, sin(angle) * ballSpeed));

	}

	//Draw everything
	gameManager.draw(window);

	//check collision
	if (gameManager.getPlayer1().checkCollision(gameManager.getBall().getBallBody()) || gameManager.getPlayer2().checkCollision(gameManager.getBall().getBallBody())) {
		deg = deg + (180 - 2 * (deg));
		ballSpeed++;
	}

}

int main()
{

	//define a window, it's size and type
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 700), "Pong", sf::Style::Default);

	//Set AntiAliasing to 8
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	//Set fps rate to 60
	window.setFramerateLimit(60);
	
	//Define game manager, it controls players, the map, and drawing
	gameManagerControl gameManager(window);

	bool wFlag = false;
	bool sFlag = false;
	bool upFlag = false;
	bool downFlag = false;
	float ballSpeed = BALL_START_SPEED;

	srand(time(NULL));
	float deg = customRand() - 90.f;

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					wFlag = true;
					break;
				case sf::Keyboard::S:
					sFlag = true;
					break;
				case sf::Keyboard::Up:
					upFlag = true;
					break;
				case sf::Keyboard::Down:
					downFlag = true;
					break;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					wFlag = false;
					break;
				case sf::Keyboard::S:
					sFlag = false;
					break;
				case sf::Keyboard::Up:
					upFlag = false;
					break;
				case sf::Keyboard::Down:
					downFlag = false;
					break;
				}
			}
		}

		function( wFlag,  sFlag, upFlag,  downFlag, window, gameManager, deg, ballSpeed);

		window.display();
	}



	return 0;
}