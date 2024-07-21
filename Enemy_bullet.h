#pragma once
#include "Enemy.h"
class Enemy_bullet :
    public Enemy
{
	float angle;

	sf::Vector2f speed;

	int health;

	sf::RectangleShape bullet_entity;

	sf::FloatRect bullet_bounds;

	sf::Vector2f position;

	void Initialize_Rectangle();
	void Initialize_Position(sf::Vector2f position);
	void Initialize_Angle(float angle);
	void Initialize_Speed();
	void Movement();
public:

	void Adjust_Angle(sf::Vector2f& player_position);
	float Get_Angle();
	void Set_Shooting_State_Off();
	bool Get_Shooting_State();
	void Decrease_Health();
	int Get_Size();
	int Get_Health();
	sf::Vector2f Get_Position();
	sf::FloatRect Get_Bounds();
	Enemy_bullet(sf::Vector2f position, float angle);
	~Enemy_bullet();
	void Render(sf::RenderTarget& target);
	void Update();
};

