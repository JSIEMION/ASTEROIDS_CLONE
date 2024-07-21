#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "State.h"

class Interface
{
public:
	virtual int Get_Score() = 0;
	virtual void Render(sf::RenderWindow*& target) = 0;
	virtual void Update(sf::RenderWindow*& target) = 0;
	virtual void Update_Events(sf::RenderWindow*& target, State& state) = 0;
};

