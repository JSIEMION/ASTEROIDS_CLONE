#include "Asteroid.h"

void Asteroid::Movement()
{
		position = position + vector_of_speed;
		if(entered_screen){
			if (position.x > 1020) {
				position.x = -20;
			}
			if (position.x < -20) {
				position.x = 1020;
			}
			if (position.y > 1020) {
				position.y = -20;
			}
			if (position.y < -20) {
				position.y = 1020;
			}
		}
		sprite.setPosition(position);
}

void Asteroid::Initialize_Texture()
{
	if (!this->texture.loadFromFile("Textures/Asteroid_Texture.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Asteroid::Initialize_Sprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(sf::Vector2f(0.03*size, 0.03*size));
	this->asteroid_bounds = sprite.getLocalBounds();
	this->sprite.setOrigin(asteroid_bounds.width / 2, asteroid_bounds.height / 2);
	this->sprite.setPosition(position);
	this->sprite.setRotation(angle);
	this->asteroid_bounds = sprite.getGlobalBounds();
}

void Asteroid::Initialize_Position(std::random_device& random_device)
{
	std::uniform_int_distribution<int> distr_of_side(1,4);
	int side = distr_of_side(random_device);
	entered_screen = 0;
	switch (side) {
	case 1:
	{
		std::uniform_real_distribution<float> distr_of_position_x_a(0.0, 1000.0);
		std::uniform_real_distribution<float> distr_of_position_y_a(-50.0, -20.0);
		this->position.x = distr_of_position_x_a(random_device);
		this->position.y = distr_of_position_y_a(random_device);
	}
		break;
	case 2:
	{
		std::uniform_real_distribution<float> distr_of_position_x_b(20.0, 50.0);
		std::uniform_real_distribution<float> distr_of_position_y_b(0.0, 1000.0);
		this->position.x = -distr_of_position_x_b(random_device);
		this->position.y = distr_of_position_y_b(random_device);
	}
		break;
	case 3:
	{
		std::uniform_real_distribution<float> distr_of_position_x_c(0.0, 1000.0);
		std::uniform_real_distribution<float> distr_of_position_y_c(1020.0, 1050.0);
		this->position.x = distr_of_position_x_c(random_device);
		this->position.y = distr_of_position_y_c(random_device);
	}
		break;
	case 4:
	{
		std::uniform_real_distribution<float> distr_of_position_x_d(1020.0, 1050.0);
		std::uniform_real_distribution<float> distr_of_position_y_d(0.0, 1000.0);
		this->position.x = distr_of_position_x_d(random_device);
		this->position.y = distr_of_position_y_d(random_device);
	}
		break;
	}
}

void Asteroid::Initialize_Angle(std::random_device& random_device)
{
	if (position.x >= 500 && position.y < 500) {
		std::uniform_real_distribution<float> disrt_of_angle(200.0, 250.0);
		this->angle = disrt_of_angle(random_device);
	}
	else if (position.x < 500 && position.y <= 500) {
		std::uniform_real_distribution<float> disrt_of_angle(110.0, 160.0);
		this->angle = disrt_of_angle(random_device);
	}
	else if (position.x <= 500 && position.y > 500) {
		std::uniform_real_distribution<float> disrt_of_angle(20.0, 70.0);
		this->angle = disrt_of_angle(random_device);
	}
	else if (position.x > 500 && position.y >= 500) {
		std::uniform_real_distribution<float> disrt_of_angle(290.0, 340.0);
		this->angle = disrt_of_angle(random_device);
	}
	else if (position.x == 500 && position.y == 500) {
		std::uniform_real_distribution<float> disrt_of_angle(0.0, 359.9);
		this->angle = disrt_of_angle(random_device);
	}
}

void Asteroid::Initialize_Speed(std::random_device& random_device)
{
	std::uniform_real_distribution<float> distr_of_speed(2.0, 5.0);
	this->speed = distr_of_speed(random_device);
	this->vector_of_speed.x = sin((this->angle * 3.14159265359) / 180) * this->speed;
	this->vector_of_speed.y = -cos((this->angle * 3.14159265359) / 180) * this->speed;
}

void Asteroid::Initialize_Health()
{
	health = 1;
}

void Asteroid::Initialize_Size(std::random_device& random_device)
{
	std::uniform_int_distribution<int> distr_of_size(1,3);
	size = distr_of_size(random_device);
}

void Asteroid::When_Size_Given(int& size)
{
	this->size = size - 1;
}

void Asteroid::When_Position_Given(sf::Vector2f& origin_position)
{
	this->position = origin_position;
}

void Asteroid::Adjust_Angle(sf::Vector2f& player_position)
{
	return;
}

float Asteroid::Get_Angle()
{
	return angle;
}

void Asteroid::Set_Shooting_State_Off()
{
	return;
}

bool Asteroid::Get_Shooting_State()
{
	return false;
}

void Asteroid::Decrease_Health()
{
	this->health = this->health - 1;
}

int Asteroid::Get_Size()
{
	return size;
}

int Asteroid::Get_Health()
{
	return health;
}

sf::Vector2f Asteroid::Get_Position()
{
	return this->position;
}

sf::FloatRect Asteroid::Get_Bounds()
{
	return this->asteroid_bounds;
}

Asteroid::Asteroid()
{
	std::random_device random_device;
	Initialize_Health();
	Initialize_Size(random_device);
	Initialize_Position(random_device);
	Initialize_Angle(random_device);
	Initialize_Speed(random_device);
	Initialize_Texture();
	Initialize_Sprite();
}

Asteroid::Asteroid(sf::Vector2f& origin_position, int& size)
{
	std::random_device random_device;
	Initialize_Health();
	When_Size_Given(size);
	When_Position_Given(origin_position);
	Initialize_Angle(random_device);
	Initialize_Speed(random_device);
	Initialize_Texture();
	Initialize_Sprite();
}

Asteroid::~Asteroid()
{
}

void Asteroid::Render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Asteroid::Update()
{
	if (!entered_screen && position.x >= 0 && position.x <= 1000 && position.y >= 0 && position.y <= 1000) {
		entered_screen = 1;
	}
	Movement();
}
