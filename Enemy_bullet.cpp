#include "Enemy_bullet.h"

void Enemy_bullet::Initialize_Rectangle()
{
	this->bullet_entity.setSize(sf::Vector2f(10, 20));
	this->bullet_entity.setFillColor(sf::Color::Red);
	this->bullet_bounds = bullet_entity.getLocalBounds();
	this->bullet_entity.setOrigin(bullet_bounds.width / 2, bullet_bounds.height / 2);
	this->bullet_entity.setPosition(this->position);
	this->bullet_entity.setRotation(this->angle);
	this->bullet_bounds = bullet_entity.getGlobalBounds();
}

void Enemy_bullet::Initialize_Position(sf::Vector2f position)
{
	this->position = position;
}

void Enemy_bullet::Initialize_Angle(float angle)
{
	this->angle = angle;
}

void Enemy_bullet::Initialize_Speed()
{
	this->speed.x = sin((angle * 3.14159265359) / 180) * 20;
	this->speed.y = -cos((angle * 3.14159265359) / 180) * 20;
}

Enemy_bullet::Enemy_bullet(sf::Vector2f position, float angle)
{
	Initialize_Position(position);
	Initialize_Angle(angle);
	Initialize_Speed();
	Initialize_Rectangle();
}

Enemy_bullet::~Enemy_bullet()
{
}

sf::Vector2f Enemy_bullet::Get_Position()
{
	return position;
}

sf::FloatRect Enemy_bullet::Get_Bounds()
{
	return bullet_bounds;
}

void Enemy_bullet::Movement()
{
	this->position = this->position + speed;
}

void Enemy_bullet::Adjust_Angle(sf::Vector2f& player_position)
{
}

float Enemy_bullet::Get_Angle()
{
	return angle;
}

void Enemy_bullet::Set_Shooting_State_Off()
{
}

bool Enemy_bullet::Get_Shooting_State()
{
	return false;
}

void Enemy_bullet::Decrease_Health()
{
	this->health--;
}

int Enemy_bullet::Get_Size()
{
	return -1;
}

int Enemy_bullet::Get_Health()
{
	return health;
}

void Enemy_bullet::Update()
{
	this->Movement();
	this->bullet_entity.setPosition(this->position);
	
}

void Enemy_bullet::Render(sf::RenderTarget& target)
{
	target.draw(bullet_entity);
}
