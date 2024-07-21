#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <math.h>



class Player{
private:

	//Player data
	sf::Texture texture;
	sf::Sprite sprite;

	sf::FloatRect player_bounds;

	sf::Vector2f position;

	float angle;

	float speed;


	//Initialization
	void Initialize_Texture();
	void Initialize_Sprite();
	void Initialize_Position();
	void Initialize_Angle();
	void Initialize_Speed();

	void Rotate_Player_Left();
	void Rotate_Player_Right();
	void Move_Player();

public:
	Player();
	~Player();

	sf::FloatRect Get_Bounds();
	sf::Vector2f Get_Position();
	float Get_Angle();
	void Movement(int direction);
	void Update();
	void Render(sf::RenderTarget& target);
};

