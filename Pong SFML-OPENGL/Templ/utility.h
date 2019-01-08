#pragma once
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
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

int customRand();
void reset(sf::RenderWindow& window, gameManagerControl& gameManager);

#endif _UTILITY_H_