#include "Ufo.h"


void Ufo::Movement()
{
	position = position + vector_of_speed;
	sprite.setPosition(position);
}

void Ufo::Initialize_Texture()
{
	if (!this->texture.loadFromFile("Textures/UFO.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Ufo::Initialize_Sprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(sf::Vector2f(0.08 * size, 0.08 * size));
	this->ufo_bounds = sprite.getLocalBounds();
	this->sprite.setOrigin(ufo_bounds.width / 2, ufo_bounds.height / 2);
	this->sprite.setPosition(position);
	this->sprite.setRotation(0);
	this->ufo_bounds = sprite.getGlobalBounds();
}

void Ufo::Initialize_Position(std::random_device& random_device)
{
	std::uniform_int_distribution<int> distr_of_side(1, 4);
	int side = distr_of_side(random_device);
	this->angle = 0;
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

void Ufo::Initialize_Destination(std::random_device& random_device)
{
	std::uniform_real_distribution<float> distr_of_dest(0.0, 1000.0);
	this->destination.x = distr_of_dest(random_device);
	this->destination.y = distr_of_dest(random_device);
	sf::Vector2f displacement = destination - position;
	if (displacement.x > 0) {
		angle = 90 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);
		this->is_traveling = 1;
	}
	else if (displacement.x < 0) {
		angle = 270 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);
		this->is_traveling = 1;
	}
	else {
		if (displacement.y > 0) {
			angle = 180;
			this->is_traveling = 1;
		}
		else if (displacement.y < 0) {
			angle = 0;
			this->is_traveling = 1;
		}
	}


}

void Ufo::Initialize_Speed(std::random_device& random_device)
{
	std::uniform_real_distribution<float> distr_of_speed(2.0, 5.0);
	this->speed = distr_of_speed(random_device);
	this->vector_of_speed.x = sin((this->angle * 3.14159265359) / 180) * this->speed;
	this->vector_of_speed.y = -cos((this->angle * 3.14159265359) / 180) * this->speed;
}

void Ufo::Initialize_Health()
{
	health = 3;
}

void Ufo::Initialize_Size(std::random_device& random_device)
{
	size = 1;
}

void Ufo::Adjust_Angle(sf::Vector2f& player_position)
{
	return;
}

float Ufo::Get_Angle()
{
	return angle;
}

void Ufo::Set_Shooting_State_Off()
{
	return;
}

bool Ufo::Get_Shooting_State()
{
	return false;
}

void Ufo::Decrease_Health()
{
	this->health = this->health - 1;
}

int Ufo::Get_Size()
{
	return size;
}

int Ufo::Get_Health()
{
	return health;
}

sf::Vector2f Ufo::Get_Position()
{
	return this->position;
}

sf::FloatRect Ufo::Get_Bounds()
{
	return this->ufo_bounds;
}

Ufo::Ufo()
{
	std::random_device random_device;
	Initialize_Health();
	Initialize_Size(random_device);
	Initialize_Position(random_device);
	Initialize_Destination(random_device);
	Initialize_Speed(random_device);
	Initialize_Texture();
	Initialize_Sprite();
}

Ufo::~Ufo()
{
}

void Ufo::Render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Ufo::Update()
{
	if (!is_traveling) {
		std::random_device random_device;
		Initialize_Destination(random_device);
		Initialize_Speed(random_device);
	}
	else {
		if (position.x >= destination.x - 10 && position.x <= destination.x + 10 && 
			position.y >= destination.y - 10 && position.y <= destination.y + 10) {
			is_traveling = 0;
		}
	}
	Movement();
}
