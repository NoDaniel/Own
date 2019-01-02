#include <iostream>
#include "gameManager.h"

template<typename T>
void log(T t) {
	std::clog << t;
}

template<typename T, typename ...Args>
void log(T t, Args... arg) {
	std::clog << t;
	log(arg...);
}

int customRand() {

	int deg;
	int brench = rand()%2 + 1;
	if (brench == 1) {
		deg = rand() % 90 + 45;
	}
	else {
		deg = rand() % 90 + 225;
	}

	return deg;
}

void reset(sf::RenderWindow& window, gameManagerControl& gameManager) {

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
	gameManager.draw(window);
	window.display();

	//Second 3
	textStr = "3";
	window.clear();
	gameManager.draw(window);
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
	gameManager.draw(window);
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
	gameManager.draw(window);
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
	gameManager.draw(window);
	window.draw(restartBox);
	text.setString(textStr);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
	text.setPosition(sf::Vector2f(restartBox.getPosition().x, restartBox.getPosition().y)); 
	window.draw(text);
	window.display();
	Sleep(1000);
}

void line::setLine(sf::RenderWindow& window) {

	for (int i = 0; i <= window.getSize().y / 15; i++) {
		sf::RectangleShape line;
		vec.push_back(line);
		vec[i].setSize(sf::Vector2f(10.f, 2.f));
		vec[i].setOrigin(sf::Vector2f(vec[i].getSize().x / 2, vec[i].getSize().y / 2));
		vec[i].setPosition(sf::Vector2f(600.f, i * 20.f));
		vec[i].setRotation(90.f);
		vec[i].setOrigin(vec[i].getSize().x / 2, vec[i].getSize().y / 2);
	}

}

void line::drawLine(sf::RenderWindow& window) {

	for (int i = 0; i <= window.getSize().y / 15; i++) {
		window.draw(vec[i]);
	}

}

void player::setPlayer(sf::RenderWindow& window, float sizex, float sizey, float posx, float posy) {
	_player.setSize(sf::Vector2f(sizex, sizey));
	_player.setPosition(sf::Vector2f(posx, posy));
	_player.setRotation(90.f);
	_player.setOrigin(50.f, 3.5f);
}

void player::drawPlayer(sf::RenderWindow& window) {
	window.draw(_player);
}

bool player::checkCollision(sf::RectangleShape& ball) {

	if (_player.getGlobalBounds().intersects(ball.getGlobalBounds())) {
		return true;
	}
	return false;
}

void ball::setBall(sf::RenderWindow& window) {
	_ball.setSize(sf::Vector2f(10.f, 10.f));
	_ball.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	_ball.setOrigin(_ball.getSize().x / 2, _ball.getSize().y / 2);
}

void ball::drawBall(sf::RenderWindow& window) {
	window.draw(_ball);
}

void score::setScore(sf::RenderWindow& window, float posx,	float posy, float fontSize) {

	text = "0";

	if (!font.loadFromFile("arial.ttf")) {
		log("Error loading font");
	}
	score.setFont(font);
	score.setString(text);
	score.setCharacterSize(70);
	score.setFillColor(sf::Color::White);
	score.setOrigin(score.getLocalBounds().left + score.getLocalBounds().width / 2, score.getLocalBounds().top + score.getLocalBounds().height / 2);
	score.setPosition(sf::Vector2f(posx, posy));
}

void score::addScore() {

	text = std::to_string(stoi(text) + 1);
	score.setString(text);

}

void score::drawScore(sf::RenderWindow& window) {
	window.draw(score);
}

void scoreBoard::drawScoreBoard(sf::RenderWindow& window) {
	player1Score.drawScore(window);
	player2Score.drawScore(window);
}

void scoreBoard::setScoreBoard(sf::RenderWindow& window) {
	player1Score.setScore(window, 500, 100, 70);
	player2Score.setScore(window, 700, 100, 70);
}

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
}