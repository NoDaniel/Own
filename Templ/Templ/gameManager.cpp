#include <iostream>
#include "gameManager.h"
#include "utility.h"

gameManagerControl::gameManagerControl(sf::RenderWindow& window) {

	player1.setPlayer(window, 100.f, 7.f, 40.f, 300.f);
	player2.setPlayer(window, 100.f, 7.f, 1160.f, 300.f);
	_ball.setBall(window);
	middleLine.setLine(window);
	scoreTable.setScoreBoard(window);
}

void gameManagerControl::draw(sf::RenderWindow& window) {
	window.clear();
	getPlayer1().drawPlayer(window);
	getPlayer2().drawPlayer(window);
	getScoreBoard().drawScoreBoard(window);
	getMiddleLine().drawLine(window);
	getBall().drawBall(window);
	currentSpeedDisplay(window);
}

void gameManagerControl::currentSpeedDisplay(sf::RenderWindow& window) {

	std::string currentSpeed = std::to_string(ballSpeed);
	std::string currentNumberBounces = std::to_string(10 - static_cast<int>(numberBounces));
	currentSpeed.resize(4);
	sf::Font arialFont;
	sf::Text currentSpeedText;
	sf::Text currentSpeedValue;
	sf::Text numberBouncesText;
	sf::Text numberBouncesText2;	
	sf::Text numberBouncesValue;

	if (!arialFont.loadFromFile("arial.ttf")) {
		log("Error loading font");
	}
	currentSpeedText.setFont(arialFont);
	currentSpeedText.setString("Ball speed : ");
	currentSpeedText.setCharacterSize(20);
	currentSpeedText.setFillColor(sf::Color::White);
	currentSpeedText.setPosition(sf::Vector2f(5.f, 5.f));

	currentSpeedValue.setFont(arialFont);
	currentSpeedValue.setString(currentSpeed);
	currentSpeedValue.setCharacterSize(20);
	currentSpeedValue.setFillColor(sf::Color::White);
	currentSpeedValue.setPosition(sf::Vector2f(5.f + currentSpeedText.getLocalBounds().width, 5.f));

	numberBouncesText.setFont(arialFont);
	numberBouncesText.setString("Increase speed in ");
	numberBouncesText.setCharacterSize(20);
	numberBouncesText.setFillColor(sf::Color::White);
	numberBouncesText.setPosition(sf::Vector2f(930.f, 5.f));

	numberBouncesValue.setFont(arialFont);
	numberBouncesValue.setString(currentNumberBounces);
	numberBouncesValue.setCharacterSize(20);
	numberBouncesValue.setFillColor(sf::Color::White);
	numberBouncesValue.setPosition(sf::Vector2f(930.f + numberBouncesText.getLocalBounds().width, 5.f));

	numberBouncesText2.setFont(arialFont);
	numberBouncesText2.setString(" bounces");
	numberBouncesText2.setCharacterSize(20);
	numberBouncesText2.setFillColor(sf::Color::White);
	numberBouncesText2.setPosition(sf::Vector2f(930.f + numberBouncesText.getLocalBounds().width + numberBouncesValue.getLocalBounds().width, 5.f));

	window.draw(currentSpeedText);
	window.draw(currentSpeedValue);
	window.draw(numberBouncesText);
	window.draw(numberBouncesValue);
	window.draw(numberBouncesText2);

}

void gameManagerControl::controlBallSpeed() {

	if (ballSpeed <= 20) {
		ballSpeed += 0.5;
	}
	else if (ballSpeed < 50) {
		ballSpeed += 1;
	}
	else if (ballSpeed < 100) {
		ballSpeed += 2;
	}
	else {
		ballSpeed += 5;
	}
}

void gameManagerControl::bounceControl() {

	if (numberBounces == 10) {
		numberBounces = 0;
		ballSpeed += 0.5;
	}

}

void gameManagerControl::restartCountdown(sf::RenderWindow& window) {

	sf::Text text;
	sf::Font font;
	std::string textStr;

	sf::RectangleShape restartBox;
	restartBox.setSize(sf::Vector2f(300.f, 150.f));
	restartBox.setPosition(sf::Vector2f(600.f, 200.f));
	restartBox.setOrigin(sf::Vector2f(restartBox.getSize().x / 2, restartBox.getSize().y / 2));
	restartBox.setFillColor(sf::Color::Black);
	restartBox.setOutlineColor(sf::Color::White);
	restartBox.setOutlineThickness(1.f);

	if (!font.loadFromFile("arial.ttf")) {
		log("Error loading font");
	}
	//std::cout << text.getCharacterSize();
	text.setFont(font);
	text.setCharacterSize(70);
	text.setFillColor(sf::Color::White);

	//Clear
	window.clear();
	draw(window);
	window.display();

	//Second 3
	textStr = "3";
	window.clear();
	draw(window);
	window.draw(restartBox);
	text.setString(textStr);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(restartBox.getPosition().x, restartBox.getPosition().y));
	window.draw(text);
	window.display();
	Sleep(1000);

	//Second 3
	textStr = "2";
	window.clear();
	draw(window);
	window.draw(restartBox);
	text.setString(textStr);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(restartBox.getPosition().x, restartBox.getPosition().y));
	window.draw(text);
	window.display();
	Sleep(1000);

	//Second 1
	textStr = "1";
	window.clear();
	draw(window);
	window.draw(restartBox);
	text.setString(textStr);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(restartBox.getPosition().x, restartBox.getPosition().y));
	window.draw(text);
	window.display();
	Sleep(1000);

	//GO
	textStr = "GO";
	window.clear();
	draw(window);
	window.draw(restartBox);
	text.setString(textStr);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(restartBox.getPosition().x, restartBox.getPosition().y));
	window.draw(text);
	window.display();
	Sleep(1000);
}