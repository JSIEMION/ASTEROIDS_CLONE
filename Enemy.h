#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>
#include <chrono>
#include <cstdlib>
#include <random>

class Enemy
{
private:


public:
	virtual void Adjust_Angle(sf::Vector2f& player_position) = 0;
	virtual float Get_Angle() = 0;
	virtual void Set_Shooting_State_Off() = 0;
	virtual bool Get_Shooting_State() = 0;
	virtual void Decrease_Health() = 0;
	virtual int Get_Size() = 0;
	virtual int Get_Health() = 0;
	virtual sf::Vector2f Get_Position() = 0;
	virtual sf::FloatRect Get_Bounds()= 0;
	virtual void Render(sf::RenderTarget& target) = 0;
	virtual void Update() = 0;
};

