#include "Hostile_ship.h"


void Hostile_ship::Movement()
{
	position = position + vector_of_speed;
	sprite.setPosition(position);
}

void Hostile_ship::Initialize_Texture()
{
	if (!this->texture.loadFromFile("Textures/Hostile_Ship.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Hostile_ship::Initialize_Sprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(sf::Vector2f(0.08 * size, 0.08 * size));
	this->ship_bounds = sprite.getLocalBounds();
	this->sprite.setOrigin(ship_bounds.width / 2, ship_bounds.height / 2);
	this->sprite.setPosition(position);
	this->sprite.setRotation(angle);
	this->ship_bounds = sprite.getGlobalBounds();
}

void Hostile_ship::Initialize_Position(std::random_device& random_device)
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

void Hostile_ship::Initialize_Destination(std::random_device& random_device)
{
	std::uniform_real_distribution<float> distr_of_dest(0.0, 1000.0);
	this->destination.x = distr_of_dest(random_device);
	this->destination.y = distr_of_dest(random_device);
	sf::Vector2f displacement = destination - position;
	if (displacement.x > 0) {
		angle = 90 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);
		this->sprite.setRotation(angle);
		this->is_traveling = 1;
		this->is_shooting = 0;
	}
	else if (displacement.x < 0) {
		angle = 270 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);
		this->sprite.setRotation(angle);
		this->is_traveling = 1;
		this->is_shooting = 0;
	}
	else {
		if (displacement.y > 0) {
			angle = 180;
			this->sprite.setRotation(angle);
			this->is_traveling = 1;
			this->is_shooting = 0;
		}
		else if (displacement.y < 0) {
			angle = 0;
			this->sprite.setRotation(angle);
			this->is_traveling = 1;
			this->is_shooting = 0;
		}
	}


}

void Hostile_ship::Initialize_Speed(std::random_device& random_device)
{
	std::uniform_real_distribution<float> distr_of_speed(2.0, 5.0);
	this->speed = distr_of_speed(random_device);
	this->vector_of_speed.x = sin((this->angle * 3.14159265359) / 180) * this->speed;
	this->vector_of_speed.y = -cos((this->angle * 3.14159265359) / 180) * this->speed;
}

void Hostile_ship::Initialize_Health()
{
	health = 5;
}

void Hostile_ship::Initialize_Size(std::random_device& random_device)
{
	size = 1;
}


void Hostile_ship::Adjust_Angle(sf::Vector2f& player_position)
{

	sf::Vector2f displacement = player_position - this->position;
	int desired_angle;
	if (displacement.x > 0) {
		desired_angle = 90 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);
		if ((angle >= desired_angle && angle <= desired_angle + 180)) {
			angle -= 5;
		}
		else {
			angle += 5;
		}
	}
	else if (displacement.x < 0) {
		desired_angle = 270 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);
		if ((angle <= desired_angle && angle >= desired_angle - 180)) {
			angle += 5;
		}
		else {
			angle -= 5;
		}

	}
	else {
		if (displacement.y > 0) {
			desired_angle = 180;
			if (angle <= 180) {
				angle += 5;
			}
			else {
				angle -= 5;
			}

		}
		else if (displacement.y < 0) {
			desired_angle = 0;
			if (angle <= 180) {
				angle -= 5;
			}
			else {
				angle += 5;
			}

		}
	}
	if (angle >= 360) {
		angle = 0;
	}
	else if (angle < 0) {
		angle = 359;
	}
	this->sprite.setRotation(angle);
}

float Hostile_ship::Get_Angle()
{
	return angle;
}

void Hostile_ship::Set_Shooting_State_Off()
{
	is_shooting = 0;
}

bool Hostile_ship::Get_Shooting_State()
{
	return is_shooting;
}

void Hostile_ship::Decrease_Health()
{
	this->health = this->health - 1;
}

int Hostile_ship::Get_Size()
{
	return size;
}

int Hostile_ship::Get_Health()
{
	return health;
}

sf::Vector2f Hostile_ship::Get_Position()
{
	return this->position;
}

sf::FloatRect Hostile_ship::Get_Bounds()
{
	return this->ship_bounds;
}

Hostile_ship::Hostile_ship()
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

Hostile_ship::~Hostile_ship()
{

}

void Hostile_ship::Render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Hostile_ship::Update()
{
	if (!is_traveling && !is_shooting) {
		std::random_device random_device;
		Initialize_Destination(random_device);
		Initialize_Speed(random_device);
	}
	else if (is_traveling && !is_shooting) {
		if (position.x >= destination.x - 10 && position.x <= destination.x + 10 &&
			position.y >= destination.y - 10 && position.y <= destination.y + 10) {
			is_traveling = 0;
			is_shooting = 1;
		}
	Movement();
	}
}
