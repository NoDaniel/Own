#include "gameManager.h"
#include "utility.h"

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

void score::setScore(sf::RenderWindow& window, float posx, float posy, float fontSize) {

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
	player1Score.setScore(window, 500, 40, 70);
	player2Score.setScore(window, 700, 40, 70);
}