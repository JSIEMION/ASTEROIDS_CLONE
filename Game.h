#pragma once
#include "Player.h"
#include "Interface.h"
#include "Menu.h"
#include "In_game_interface.h"
#include "State.h"
#include "Game_over_interface.h"
#include "Leaderboard.h"
#include "Help.h"


class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;
	Interface* interface;
	State state;

	void Initialize_Variables();
	void Initialize_Window();
	void Initialize_Interface();

public:
	Game();
	~Game();

	const bool Is_Window_Open() const;

	void Run();
	void Update_Events();
	void Update();
	void Render();

};

