#include "Player.h"

void Player::Initialize_Texture()
{
	if (!this->texture.loadFromFile("Textures/Player_Ship.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Player::Initialize_Sprite()
{
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(sf::Vector2f(0.05, 0.05));
	this->player_bounds = sprite.getLocalBounds();
	this->sprite.setOrigin(player_bounds.width / 2, player_bounds.height / 2);
	this->sprite.setPosition(position);
	this->sprite.setRotation(angle);
	this->player_bounds = sprite.getGlobalBounds();
}

void Player::Initialize_Position()
{
	this->position = { 500, 500 };

}

void Player::Initialize_Angle()
{
	this->angle = { 0.f };
}

void Player::Initialize_Speed()
{
	speed = 10;
}

void Player::Rotate_Player_Left()
{
	if (angle <= 0) {
		angle = 355;
	}
	else {
		angle = angle - 5;
	}
}

void Player::Rotate_Player_Right()
{
	if (angle >= 355) {
		angle = 0;
	}
	else {
		angle = angle + 5;
	}
}

void Player::Move_Player()
{
	sf::Vector2f vector_of_speed = { 0,0 };
	vector_of_speed.x = sin((angle * 3.14159265359)/180) * speed;
	vector_of_speed.y = -cos((angle * 3.14159265359) / 180) * speed;
	//std::cout << vector_of_speed.x << " " << vector_of_speed.y << " " << speed << " " << angle << "\n";
	position = position + vector_of_speed;
	if (position.x > 1000) {
		position.x = 1000;
	}
	if (position.x < 0) {
		position.x = 0;
	}
	if (position.y > 1000) {
		position.y = 1000;
	}
	if (position.y < 0) {
		position.y = 0;
	}
}


Player::Player()
{
	this->Initialize_Angle();
	this->Initialize_Position();
	this->Initialize_Speed();
	this->Initialize_Texture();
	this->Initialize_Sprite();
}

Player::~Player()
{
}

sf::FloatRect Player::Get_Bounds()
{
	return player_bounds;
}

sf::Vector2f Player::Get_Position()
{
	return position;
}

float Player::Get_Angle()
{
	return angle;
}

void Player::Movement(int direction)
{
	switch (direction) {
	case 1:
		Rotate_Player_Left();
		break;
	case 2:
		Rotate_Player_Right();
		break;
	case 3:
		Move_Player();
		break;
	}
}

void Player::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		Movement(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		Movement(2);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		Movement(3);
	}
	this->sprite.setPosition(position);
	this->sprite.setRotation(angle);
}

void Player::Render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
