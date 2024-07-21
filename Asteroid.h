#pragma once
#include "Enemy.h"
class Asteroid :
    public Enemy
{
private:

	sf::Texture texture;
	sf::Sprite sprite;

	sf::FloatRect asteroid_bounds;

	sf::Vector2f position;

	float angle;

	float speed;
	sf::Vector2f vector_of_speed;

	bool entered_screen;

	int health;
	int size;

	void Movement();
	void Initialize_Texture();
	void Initialize_Sprite();
	void Initialize_Position(std::random_device& random_device);
	void Initialize_Angle(std::random_device& random_device);
	void Initialize_Speed(std::random_device& random_device);
	void Initialize_Health();
	void Initialize_Size(std::random_device& random_device);
	void When_Size_Given(int& size);
	void When_Position_Given(sf::Vector2f& origin_position);
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
	Asteroid();
	Asteroid(sf::Vector2f& origin_position, int& size);
	~Asteroid();
	void Render(sf::RenderTarget& target);
	void Update();

};

