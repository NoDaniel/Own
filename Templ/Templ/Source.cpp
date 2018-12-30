#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <iostream>
#include <vector>
#include <math.h> 
#include <stdlib.h>
#include <time.h>

#define _SPEED 5
#define BALL_START_SPEED 10
#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862

template<typename T>
void log(T t) {
	std::clog << t;
}

template<typename T, typename ...Args>
void log(T t, Args... arg) {
	std::clog << t;
	log(arg...);
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

	//Define middle line
	std::vector<sf::RectangleShape> vec;
	for (int i = 0; i <= window.getSize().y/15; i++) {
		sf::RectangleShape line;
		vec.push_back(line);
		vec[i].setSize(sf::Vector2f(10.f, 2.f));
		vec[i].setPosition(sf::Vector2f(600.f, i * 20.f));
		vec[i].setRotation(90.f);
		vec[i].setOrigin(vec[i].getSize().x / 2, vec[i].getSize().y / 2);
	}

	//Define first player
	sf::RectangleShape player1(sf::Vector2f(100.f, 7.f));
	player1.setPosition(sf::Vector2f(40.f, 300.f));
	player1.setRotation(90.f);
	player1.setOrigin(50.f, 3.5f);

	//Define second player
	sf::RectangleShape player2(sf::Vector2f(100.f, 7.f));
	player2.setPosition(sf::Vector2f(1160.f, 300.f));
	player2.setRotation(90.f);
	player2.setOrigin(50.f, 3.5f);


	//Define ball
	sf::RectangleShape ball;
	ball.setSize(sf::Vector2f(10.f, 10.f));
	ball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	ball.setOrigin(ball.getSize().x / 2, ball.getSize().y / 2);

	//Define score table player 1
	std::string textPlayer1 = "0";
	sf::Text scorePlayer1;
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		log("Error loading font");
	}
	scorePlayer1.setOrigin(scorePlayer1.getLocalBounds().width / 2, scorePlayer1.getLocalBounds().height / 2);
	scorePlayer1.setPosition(sf::Vector2f(400.f, 30.f));
	scorePlayer1.setFont(font);
	scorePlayer1.setString(textPlayer1);
	scorePlayer1.setCharacterSize(70);
	scorePlayer1.setFillColor(sf::Color::White);

	//Define score table player 2
	std::string textPlayer2 = "0";
	sf::Text scorePlayer2;
	scorePlayer2.setOrigin(scorePlayer2.getLocalBounds().width / 2, scorePlayer2.getLocalBounds().height / 2);
	scorePlayer2.setPosition(sf::Vector2f(600.f, 30.f));
	scorePlayer2.setFont(font);
	scorePlayer2.setString(textPlayer2);
	scorePlayer2.setCharacterSize(70);
	scorePlayer2.setFillColor(sf::Color::White);

	bool wFlag = false;
	bool sFlag = false;
	bool upFlag = false;
	bool downFlag = false;
	bool ballFlag = false; // true = left, false = right
	srand(time(NULL));

	float deg = rand() % 360 - 90.f;

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

		if (wFlag) {
			if (player1.getPosition().y - _SPEED - player1.getSize().x / 2 >= 0) {
				player1.sf::Transformable::move(sf::Vector2f(0.f, -_SPEED));
			}
		}
		if (sFlag) {
			if (window.getSize().y >= player1.getPosition().y + _SPEED + player1.getSize().x / 2) {
				player1.sf::Transformable::move(sf::Vector2f(0.f, _SPEED));
			}
		}
		if (upFlag) {
			if (player2.getPosition().y - _SPEED - player2.getSize().x / 2 >= 0) {
				player2.sf::Transformable::move(sf::Vector2f(0.f, -_SPEED));
			}
		}
		if (downFlag) {
			if (window.getSize().y >= player2.getPosition().y + _SPEED + player2.getSize().x / 2) {
				player2.sf::Transformable::move(sf::Vector2f(0.f, _SPEED));
			}
		}

		float angle = deg * PI / 180.f;
		if (window.getSize().x >= ball.getPosition().x + cos(angle) * BALL_START_SPEED + ball.getSize().x / 2 &&
			window.getSize().y >= ball.getPosition().y + sin(angle) * BALL_START_SPEED + ball.getSize().y / 2 &&
			ball.getPosition().x + cos(angle) * BALL_START_SPEED + ball.getSize().x / 2 >= 0 &&
			ball.getPosition().y + sin(angle) * BALL_START_SPEED + ball.getSize().y / 2 >= 0) {

			ball.sf::Transformable::move(sf::Vector2f(cos(angle) * BALL_START_SPEED, sin(angle) * BALL_START_SPEED));
		}
		else {
			if (deg > 360) deg -= 360;
			if (deg < 0) deg += 360;
			if (window.getSize().x < ball.getPosition().x + cos(angle) * BALL_START_SPEED + ball.getSize().x / 2) {
				textPlayer1 = std::to_string(stoi(textPlayer1) + 1);
				scorePlayer1.setString(textPlayer1);
				ball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
				deg = rand() % 360 - 90.f;
				Sleep(1000);
				log("wait 1");
				Sleep(1000);
				log("wait 2");
				Sleep(1000);
				log("wait 3");
			}
			else if (ball.getPosition().x + cos(angle) * BALL_START_SPEED + ball.getSize().x / 2 < 0) {
				textPlayer2 = std::to_string(stoi(textPlayer2) + 1);
				scorePlayer2.setString(textPlayer2);
				ball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
				deg = rand() % 360 - 90.f;
				Sleep(1000);
				log("wait 1");
				Sleep(1000);
				log("wait 2");
				Sleep(1000);
				log("wait 3");
			}
			else if (window.getSize().y < ball.getPosition().y + sin(angle) * BALL_START_SPEED + ball.getSize().y / 2) {
				if (deg > 0 && deg < 90) {
					log("Degres in ", deg, " ------ ");
					deg = deg - (180 - (90 - deg) * 2);
					log("Degres out ", deg, "\n");
				}
				else if (deg > 90 && deg < 180) {
					log("Degres in ", deg, " ------ ");
					deg = deg + (180 - (deg - 90) * 2);
					log("Degres out ", deg, "\n");
				}
				else if (deg == 90) {
					std::cout << "90deg\n";
					//deg += 1;
				}
			}
			else if (ball.getPosition().y + sin(angle) * BALL_START_SPEED + ball.getSize().y / 2 < 0) {
				if (deg > 270 && deg < 360) {
					log("Degres in ", deg, " ------ ");
					deg = deg + (360 - deg) * 2;
					log("Degres out ", deg, "\n");
				}
				else if (deg > 180 && deg < 270) {
					log("Degres in ", deg, " ------ ");
					deg = deg - ((deg - 180) * 2);
					log("Degres out ", deg, "\n");
				}
			}
			angle = deg * PI / 180;
			ball.sf::Transformable::move(sf::Vector2f(cos(angle) * BALL_START_SPEED, sin(angle) * BALL_START_SPEED));

		}
		//ball.sf::Transformable::move(sf::Vector2f(cos(angle) * _SPEED, sin(angle) * _SPEED));

		window.clear();
		window.draw(player1);
		window.draw(player2);
		window.draw(ball);
		window.draw(scorePlayer1);
		window.draw(scorePlayer2);
		for (int i = 0; i <= window.getSize().y / 15; i++) {
			window.draw(vec[i]);
		}

		if (player1.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			deg = deg + (180 - 2 * (deg));
		}
		else if (player2.getGlobalBounds().intersects(ball.getGlobalBounds())) {
			deg = deg + (180 - 2 * (deg));
		}

		window.display();
	}



	return 0;
}