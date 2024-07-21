#include "Bullet.h"

void Bullet::Initialize_Rectangle()
{
	this->bullet_entity.setSize(sf::Vector2f(5, 10));
	this->bullet_entity.setFillColor(sf::Color::White);
	this->bullet_bounds = bullet_entity.getLocalBounds();
	this->bullet_entity.setOrigin(bullet_bounds.width / 2, bullet_bounds.height / 2);
	this->bullet_entity.setPosition(this->position);
	this->bullet_entity.setRotation(this->angle);
	this->bullet_bounds = bullet_entity.getGlobalBounds();
}

void Bullet::Initialize_Position(sf::Vector2f position)
{
	this->position = position;
}

void Bullet::Initialize_Angle(float angle)
{
	this->angle = angle;
}

void Bullet::Initialize_Speed()
{
	this->speed.x = sin((angle * 3.14159265359) / 180) * 20;
	this->speed.y = -cos((angle * 3.14159265359) / 180) * 20;
}

Bullet::Bullet(sf::Vector2f position, float angle)
{
	Initialize_Position(position);
	Initialize_Angle(angle);
	Initialize_Speed();
	Initialize_Rectangle();
}

Bullet::~Bullet()
{
}

sf::Vector2f Bullet::Get_Position()
{
	return position;
}

sf::FloatRect Bullet::Get_Bounds()
{
	return bullet_bounds;
}

void Bullet::Movement()
{
	this->position = this->position + speed;
}

void Bullet::Update()
{
	this->Movement();
	this->bullet_entity.setPosition(this->position);
}

void Bullet::Render(sf::RenderTarget& target)
{
	target.draw(bullet_entity);
}
