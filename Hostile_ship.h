#pragma once
#include "Enemy.h"
#include "In_game_interface.h"
#include "Player.h"

class Hostile_ship :
    public Enemy
{
private:

	sf::Texture texture;
	sf::Sprite sprite;

	sf::FloatRect ship_bounds;

	sf::Vector2f position;

	float angle;

	float speed;
	sf::Vector2f vector_of_speed;

	sf::Vector2f destination;

	int health;
	int size;

	bool is_traveling;
	bool is_shooting;

	void Movement();
	void Initialize_Texture();
	void Initialize_Sprite();
	void Initialize_Position(std::random_device& random_device);
	void Initialize_Destination(std::random_device& random_device);
	void Initialize_Speed(std::random_device& random_device);
	void Initialize_Health();
	void Initialize_Size(std::random_device& random_device);

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
	Hostile_ship();
	~Hostile_ship();
	void Render(sf::RenderTarget& target);
	void Update();
};

