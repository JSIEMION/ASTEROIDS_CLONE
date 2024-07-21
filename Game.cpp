#include "Game.h"

Game::Game(){
	this->Initialize_Variables();
	this->Initialize_Window();
}

Game::~Game(){

	delete this->interface;
	delete this->window;
}

const bool Game::Is_Window_Open() const{
	return this->window->isOpen();
}

void Game::Run() {
	while (this->Is_Window_Open()) {
		this->Update();
		this->Render();
	}
}

void Game::Update_Events(){
	this->interface->Update_Events(this->window, this->state);
	if (this->state == State::menu) {
		this->state = State::neutral;
		delete this->interface;
		this->interface = new Menu();
		std::cout << "menu";
	}
	if (this->state == State::game) {
		this->state = State::neutral;
		delete this->interface;
		this->interface = new In_game_interface();
		std::cout << "game";
	}
	if (this->state == State::exit) {
		this->state = State::neutral;
		this->window->close();
		std::cout << "exit";
	}
	if (this->state == State::game_over) {
		this->state = State::neutral;
		int temp_score = this->interface->Get_Score();
		delete this->interface;
		this->interface = new Game_over_interface(temp_score);
		std::cout << "game over";
	}
	if (this->state == State::leaderboard) {
		this->state = State::neutral;
		delete this->interface;
		this->interface = new Leaderboard();
		std::cout << "leaderboard";
	}
	if (this->state == State::help) {
		this->state = State::neutral;
		delete this->interface;
		this->interface = new Help();
		std::cout << "help";
	}
}

void Game::Update(){
	this->Update_Events();
	this->interface->Update(this->window);
}

void Game::Render(){
	
	this->window->clear();

	this->interface->Render(this->window);

	this->window->display();
}

void Game::Initialize_Variables(){
	this->window = nullptr;
	this->state = State::neutral;
}

void Game::Initialize_Window(){
	this->video_mode.height = 1000;
	this->video_mode.width = 1000;

	this->window = new sf::RenderWindow(this->video_mode, "ASTEROIDS", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

	this->interface = new Menu;
}

void Game::Initialize_Interface()
{

}

