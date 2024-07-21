#include "In_game_interface.h"

void In_game_interface::Initialize_Player()
{
	this->player = new Player;
}

void In_game_interface::Initialize_Font()
{
	if (!this->font.loadFromFile("Fonts/Games-XvD2.ttf")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void In_game_interface::Initialize_Variables()
{
	this->score = 0;
	this->lifes = 3;
	this->wave = 1;
	this->opacity_and_colour[0] = 255;
	this->opacity_and_colour[1] = 255;
	this->opacity_and_colour[2] = 255;
	this->shooting_frequency_counter = 0;
}

void In_game_interface::Initialize_Score()
{
	sf::FloatRect textRect;

	this->score_text.setFont(this->font);
	this->score_text.setFillColor(sf::Color::White);
	this->score_text.setString(std::to_string(score));
	this->score_text.setCharacterSize(80);
	textRect = score_text.getLocalBounds();
	this->score_text.setOrigin(textRect.left + textRect.width, textRect.top);
	this->score_text.setPosition(sf::Vector2f(980, 20));
}

void In_game_interface::Initialize_Background()
{
	if (!this->background_texture.loadFromFile("Textures/Background_Texture.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
	else{
		this->background.setTexture(this->background_texture);
	}
}

void In_game_interface::Initialize_Lifes()
{
	if (!this->life_texture.loadFromFile("Textures/Heart.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
	else {
		sf::FloatRect bounds;
		
		this->life_sprite[0].setTexture(this->life_texture);
		this->life_sprite[0].setScale(0.075,0.075);
		this->life_sprite[0].setPosition(57, 57);
		bounds = this->life_sprite[0].getLocalBounds();
		this->life_sprite[0].setOrigin(bounds.height/2, bounds.width/2);

		this->life_sprite[1].setTexture(this->life_texture);
		this->life_sprite[1].setScale(0.075, 0.075);
		this->life_sprite[1].setPosition(147, 57);
		bounds = this->life_sprite[1].getLocalBounds();
		this->life_sprite[1].setOrigin(bounds.height / 2, bounds.width / 2);

		this->life_sprite[2].setTexture(this->life_texture);
		this->life_sprite[2].setScale(0.075, 0.075);
		this->life_sprite[2].setPosition(237, 57);
		bounds = this->life_sprite[2].getLocalBounds();
		this->life_sprite[2].setOrigin(bounds.height / 2, bounds.width / 2);
	}
}

void In_game_interface::Create_Bullet()
{
	Bullet* a = new Bullet(this->player->Get_Position(), this->player->Get_Angle());
	bullet_vector.push_back(a);
}

void In_game_interface::Start_Wave()
{
	if (wave < 4) {
		for (int i = 1; i <= wave*2; i++) {
			Create_Asteroid();
		}
	}
	if (wave >= 4) {
		for (int i = 1; i <= wave; i++) {
			Create_Asteroid();
		}
	}
	if (wave % 4 == 0) {
		for (int i = 1; i <= wave/4; i++) {
			Create_UFO();
		}
	}
	if (wave % 5 == 0) {
		Create_Enemy_Ship();
	}
	this->wave++;
}

void In_game_interface::Create_Asteroid()
{
	Enemy* enemy = new Asteroid();
	enemy_vector.push_back(enemy);
}

void In_game_interface::Create_UFO()
{
	Enemy* enemy = new Ufo();
	enemy_vector.push_back(enemy);
}

void In_game_interface::Create_Enemy_Ship()
{
	Enemy* enemy = new Hostile_ship();
	enemy_vector.push_back(enemy);
}

void In_game_interface::Create_Enemy_Bullet(Enemy*& enemy)
{
	float angle = enemy->Get_Angle();
	sf::Vector2f position = enemy->Get_Position();
	Enemy* new_enemy = new Enemy_bullet(position, angle);
	enemy_vector.push_back(new_enemy);
}

void In_game_interface::Update_Score()
{
	sf::FloatRect textRect;
	this->score_text.setString(std::to_string(score));
	textRect = score_text.getLocalBounds();
	this->score_text.setOrigin(textRect.left + textRect.width, textRect.top);
	this->score_text.setPosition(sf::Vector2f(980, 20));
}

void In_game_interface::Update_Lifes()
{
	if (lifes < 3 && opacity_and_colour[2] != 0) {
		opacity_and_colour[2]-=15;
		this->life_sprite[2].setColor(sf::Color(255, 255, 255, opacity_and_colour[2]));
	}
	if (lifes < 2 && opacity_and_colour[1] != 0) {
		opacity_and_colour[1] -= 15;
		this->life_sprite[1].setColor(sf::Color(255, 255, 255, opacity_and_colour[1]));
		this->life_sprite[0].setColor(sf::Color(255, opacity_and_colour[1], opacity_and_colour[1], 255));

	}
	if (lifes < 1 && opacity_and_colour[0] != 0) {
		opacity_and_colour[0] -= 15;
		this->life_sprite[0].setColor(sf::Color(255, 0, 0, opacity_and_colour[0]));	
	}
}

bool In_game_interface::Check_If_Player_Targeted(Enemy* enemy)
{
	std::cout << (int)enemy->Get_Angle() <<'\n';
	sf::Vector2f displacement =  this->player->Get_Position() - enemy->Get_Position() ;
	int desired_angle;
	if (displacement.x > 0) {
		desired_angle = 90 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);


	}
	else if (displacement.x < 0) {
		desired_angle = 270 + (((atan(displacement.y / displacement.x)) * 180) / 3.14159265359);


	}
	else {
		if (displacement.y > 0) {
			desired_angle = 180;


		}
		else if (displacement.y < 0) {
			desired_angle = 0;


		}
	}
	return ((int)enemy->Get_Angle() <= desired_angle + 3 && (int)enemy->Get_Angle() >= desired_angle - 3);
}

void In_game_interface::Bullet_Update()
{
	for (auto i = bullet_vector.begin(); i != bullet_vector.end(); i++) {
		(*i)->Update();

		//bullet out of bounds
		if ((*i)->Get_Position().x > 1000 || (*i)->Get_Position().x < 0 || (*i)->Get_Position().y > 1000 || (*i)->Get_Position().y < 0) {
			delete (*i);
			bullet_vector.erase(i);
			return;
		}
	}
}

void In_game_interface::Enemy_Update()
{
	for (auto i = enemy_vector.begin(); i != enemy_vector.end(); i++) {
		(*i)->Update();

		//enemy ship shooting
		if ((*i)->Get_Shooting_State() == 1 && shooting_frequency_counter == 180) {
			(*i)->Set_Shooting_State_Off();
			shooting_frequency_counter = 0;
		}
		else if ((*i)->Get_Shooting_State() == 1 && shooting_frequency_counter % 60 == 0) {
			if (Check_If_Player_Targeted((*i))) {
				Create_Enemy_Bullet((*i));
				shooting_frequency_counter++;
				return;
			}
			else {
				sf::Vector2f player_position = this->player->Get_Position();
				(*i)->Adjust_Angle(player_position);
			}
		}
		else if ((*i)->Get_Shooting_State() == 1 && shooting_frequency_counter % 60 != 0) {
			shooting_frequency_counter++;
		}

		//player and enemy collision
		if (((*i)->Get_Position().x + (*i)->Get_Bounds().width / 2 >= this->player->Get_Position().x &&
			(*i)->Get_Position().x - (*i)->Get_Bounds().width / 2 <= this->player->Get_Position().x &&
			(*i)->Get_Position().y + (*i)->Get_Bounds().height / 2 >= this->player->Get_Position().y &&
			(*i)->Get_Position().y - (*i)->Get_Bounds().height / 2 <= this->player->Get_Position().y) ||
			(this->player->Get_Position().x + this->player->Get_Bounds().width / 2 >= (*i)->Get_Position().x &&
				this->player->Get_Position().x - this->player->Get_Bounds().width / 2 <= (*i)->Get_Position().x &&
				this->player->Get_Position().y + this->player->Get_Bounds().height / 2 >= (*i)->Get_Position().y &&
				this->player->Get_Position().y - this->player->Get_Bounds().height / 2 <= (*i)->Get_Position().y)) {

			this->lifes--;

			delete (*i);
			enemy_vector.erase(i);
			return;
		}

		for (auto j = bullet_vector.begin(); j != bullet_vector.end(); j++) {

			//bullet hit on enemy
			if ((*i)->Get_Position().x + (*i)->Get_Bounds().width / 2 >= (*j)->Get_Position().x &&
				(*i)->Get_Position().x - (*i)->Get_Bounds().width / 2 <= (*j)->Get_Position().x &&
				(*i)->Get_Position().y + (*i)->Get_Bounds().height / 2 >= (*j)->Get_Position().y &&
				(*i)->Get_Position().y - (*i)->Get_Bounds().height / 2 <= (*j)->Get_Position().y) {

				(*i)->Decrease_Health();

				delete (*j);
				bullet_vector.erase(j);

				return;
			}
		}

		//kill enemy
		if ((*i)->Get_Health() == 0) {
			if ((*i)->Get_Size() > 0) {
				this->score = this->score + 10;
			}
			if ((*i)->Get_Size() > 1) {
				int temp_int = (*i)->Get_Size();
				sf::Vector2f temp_pos = (*i)->Get_Position();
				delete (*i);
				enemy_vector.erase(i);
				Enemy* enemy = new Asteroid(temp_pos, temp_int);
				enemy_vector.push_back(enemy);
				enemy = new Asteroid(temp_pos, temp_int);
				enemy_vector.push_back(enemy);
				return;
			}
			else {
				delete (*i);
				enemy_vector.erase(i);
				return;
			}
		}

		if ((*i)->Get_Position().x <= -200 || (*i)->Get_Position().x >= 1200 || (*i)->Get_Position().y <= -200 || (*i)->Get_Position().y >= 1200) {
			delete (*i);
			enemy_vector.erase(i);
			return;
		}
	}
}

In_game_interface::In_game_interface()
{
	Initialize_Background();
	Initialize_Font();
	Initialize_Player();
	Initialize_Variables();
	Initialize_Score();
	Initialize_Lifes();
}

In_game_interface::~In_game_interface()
{
	delete this->player;
	for (auto i = enemy_vector.begin(); i != enemy_vector.end(); i++) {
		delete (*i);
	}
	for (auto i = bullet_vector.begin(); i != bullet_vector.end(); i++) {
		delete (*i);
	}
	enemy_vector.clear();
	bullet_vector.clear();

}

int In_game_interface::Get_Score()
{
	return this->score;
}

int In_game_interface::Get_Wave()
{
	return wave;
}

void In_game_interface::Render(sf::RenderWindow*& target)
{
	target->draw(this->background);
	
	for(int i = 0; i < 3; i++){
		target->draw(this->life_sprite[i]);
	}
	
	target->draw(this->score_text);

	this->player->Render(*target);
	for (auto& b : bullet_vector) {
		b->Render(*target);
	}
	for (auto& enemy : enemy_vector) {
		enemy->Render(*target);
	}
}

void In_game_interface::Update(sf::RenderWindow*& target)
{
	
	this->Update_Score();

	this->Update_Lifes();

	if (this->enemy_vector.empty()) {
		this->Start_Wave();
	}
	
	this->player->Update();
	
	std::thread bullet_thread([this]() { this->Bullet_Update(); });
	std::thread enemy_thread([this]() { this->Enemy_Update(); });


	bullet_thread.join();
	enemy_thread.join();

}

void In_game_interface::Update_Events(sf::RenderWindow*& target, State& state)
{

	if (this->lifes <= 0) {
		state = State::game_over;
	}

	while (target->pollEvent(this->event)) {
		switch (this->event.type) {

		case sf::Event::Closed:
			target->close();
			break;

		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::Escape) {
				//state = State::menu;
				this->lifes = 0;
			}
			if (event.key.code == sf::Keyboard::Space) {
				Create_Bullet();
			}

			break;
		}
	}
}
