#pragma once
#include "Interface.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Ufo.h"
#include "Hostile_ship.h"
#include "Enemy_bullet.h"
#include "Game.h"
#include <thread>

class In_game_interface :
    public Interface
{
private:
	std::thread bullet_thread, enemy_thread;

	sf::Texture background_texture;
	sf::Sprite background;

	//In game objects
	Player* player;

	std::vector<Bullet*> bullet_vector;

	std::vector<Enemy*> enemy_vector;

	//Font
	sf::Font font;

	//Logic variables
	int wave;
	
	int score;
	sf::Text score_text;

	int shooting_frequency_counter;

	int lifes;
	sf::Texture life_texture;
	sf::Sprite life_sprite[3];
	int opacity_and_colour[3];

	sf::Event event;

	void Initialize_Player();
	void Initialize_Font();
	void Initialize_Variables();
	void Initialize_Score();
	void Initialize_Background();
	void Initialize_Lifes();
	
	void Create_Bullet();
	
	void Start_Wave();
	void Create_Asteroid();
	void Create_UFO();
	void Create_Enemy_Ship();
	void Create_Enemy_Bullet(Enemy*& enemy);

	void Update_Score();
	void Update_Lifes();
	bool Check_If_Player_Targeted(Enemy* enemy);

	void Bullet_Update();
	void Enemy_Update();
public:
	In_game_interface();
	~In_game_interface();

	int Get_Score();
	int Get_Wave();
	void Render(sf::RenderWindow*& target);
	void Update(sf::RenderWindow*& target);
	void Update_Events(sf::RenderWindow*& target, State& state);
};

