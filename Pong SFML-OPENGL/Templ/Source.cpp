#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <iostream>
#include <math.h> 
#include <stdlib.h>
#include <time.h>
#include "gameManager.h"
#include "utility.h"
#include "gameElements.h"

#define _SPEED 5
#define BALL_START_SPEED 7
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862

enum State {
	STATE_MENU,
	STATE_GAME_MODE_COOP
};

int main()
{

	//define a window, it's size and type
	sf::RenderWindow window;
	window.create(sf::VideoMode(1200, 700), "Pong", sf::Style::Default);

	//Settings
	sf::ContextSettings settings;
	//Set AntiAliasing to 8
	settings.antialiasingLevel = 8;
	//Set fps rate to 60
	window.setFramerateLimit(60);
	
	//Define game manager, it controls players, the map, and drawing
	gameManagerControl gameManager(window);

	bool wFlag = false;
	bool sFlag = false;
	bool upFlag = false;
	bool downFlag = false;
	gameManager.setBallSpeed(BALL_START_SPEED);

	srand(time(NULL));
	float deg = customRand() - 90.f;
	State gameState = STATE_MENU;

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (gameState) {
			case STATE_MENU:
				if (event.type == sf::Event::KeyPressed) {
					switch (event.key.code) {
					case sf::Keyboard::Num1:
						gameState = STATE_GAME_MODE_COOP;
						break;
					case sf::Keyboard::Num2:
						window.close();
						break;
					}
				}
				break;
			case STATE_GAME_MODE_COOP:
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
				break;
			}
			
		}

		if (gameState == STATE_GAME_MODE_COOP) {
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
			if (window.getSize().x >= gameManager.getBall().getBallBody().getPosition().x + cos(angle) * gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().x / 2 &&
				window.getSize().y >= gameManager.getBall().getBallBody().getPosition().y + sin(angle) * gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().y / 2 &&
				gameManager.getBall().getBallBody().getPosition().x + cos(angle) * gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().x / 2 >= 0 &&
				gameManager.getBall().getBallBody().getPosition().y + sin(angle) * gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().y / 2 >= 0) {

				gameManager.getBall().getBallBody().sf::Transformable::move(sf::Vector2f(cos(angle) * gameManager.getBallSpeed(), sin(angle) * gameManager.getBallSpeed()));
			}
			else {
				if (deg > 360) deg -= 360;
				if (deg < 0) deg += 360;
				if (window.getSize().x < gameManager.getBall().getBallBody().getPosition().x + cos(angle) *	gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().x / 2) {
					gameManager.getScoreBoard().getPlayer1Score().addScore();
					gameManager.getBall().getBallBody().setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
					gameManager.restartCountdown(window);
					gameManager.controlBallSpeed();
					deg = customRand() - 90.f;
				}
				else if (gameManager.getBall().getBallBody().getPosition().x + cos(angle) * gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().x / 2 < 0) {
					gameManager.getScoreBoard().getPlayer2Score().addScore();
					gameManager.getBall().getBallBody().setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
					gameManager.restartCountdown(window);
					gameManager.controlBallSpeed();
					deg = customRand() - 90.f;
				}
				else if (window.getSize().y < gameManager.getBall().getBallBody().getPosition().y + sin(angle) * gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().y / 2) {
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
				else if (gameManager.getBall().getBallBody().getPosition().y + sin(angle) * gameManager.getBallSpeed() + gameManager.getBall().getBallBody().getSize().y / 2 < 0) {
					if (deg > 270 && deg < 360) {
						deg = deg + (360 - deg) * 2;
					}
					else if (deg > 180 && deg < 270) {
						deg = deg - ((deg - 180) * 2);
					}
				}
				angle = deg * PI / 180;
				gameManager.getBall().getBallBody().sf::Transformable::move(sf::Vector2f(cos(angle) * gameManager.getBallSpeed(), sin(angle) * gameManager.getBallSpeed()));

			}

			//Draw everything
			gameManager.draw(window);

			//check collision
			if (gameManager.getPlayer1().checkCollision(gameManager.getBall().getBallBody()) || gameManager.getPlayer2().checkCollision(gameManager.getBall().getBallBody())) {
				deg = deg + (180 - 2 * (deg));
				gameManager.setNumberBounces(gameManager.getNumberBounces() + 1);
				gameManager.bounceControl();
			}

		}
		else if (gameState == STATE_MENU) {
			sf::Font arialFont;
			sf::Text playButton;
			sf::Text exitButton;
			if (!arialFont.loadFromFile("arial.ttf")) {
				//log("Error loading font");
			}
			playButton.setFont(arialFont);
			playButton.setString("1.Play");
			playButton.setCharacterSize(60.f);
			playButton.setFillColor(sf::Color::White);
			playButton.setOrigin(playButton.getLocalBounds().left + playButton.getLocalBounds().width / 2, playButton.getLocalBounds().top + playButton.getLocalBounds().height / 2);
			playButton.setPosition(sf::Vector2f(window.getSize().x / 2, 200));

			exitButton.setFont(arialFont);
			exitButton.setString("2.Exit");
			exitButton.setCharacterSize(60.f);
			exitButton.setFillColor(sf::Color::White);
			exitButton.setOrigin(exitButton.getLocalBounds().left + exitButton.getLocalBounds().width / 2, exitButton.getLocalBounds().top + exitButton.getLocalBounds().height / 2);
			exitButton.setPosition(sf::Vector2f(window.getSize().x / 2, 270));

			window.draw(exitButton);
			window.draw(playButton);
		}


		window.display();
	}



	return 0;
}