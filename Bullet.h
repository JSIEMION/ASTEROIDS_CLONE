#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>

class Bullet
{
private:
	float angle;

	sf::Vector2f speed;

	sf::RectangleShape bullet_entity;

	sf::FloatRect bullet_bounds;

	sf::Vector2f position;

	void Initialize_Rectangle();
	void Initialize_Position(sf::Vector2f position);
	void Initialize_Angle(float angle);
	void Initialize_Speed();
	void Movement();
public:
	Bullet(sf::Vector2f position, float angle);
	~Bullet();

	sf::Vector2f Get_Position();
	sf::FloatRect Get_Bounds();
	void Update();
	void Render(sf::RenderTarget& target);

};

