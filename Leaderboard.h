#pragma once
#include "Interface.h"
#include <vector>
#include <filesystem>
#include <fstream>
#include <string>

class Leaderboard :
    public Interface
{
private:
	//Background
	sf::Texture background_texture;
	sf::Sprite background;

	//Font
	sf::Font font;

	//Event
	sf::Event event;

	//Exit button
	sf::RectangleShape exit_button;
	sf::Text exit_button_text;

	//Mouse position
	sf::Vector2i mouse_position;

	//Scores
	std::vector<std::vector<std::string>> scores;

	//10 higest scores
	std::vector<std::vector<sf::Text>> top_scores;

	//score table background
	sf::RectangleShape table_background;

	//Save file
	std::filesystem::path save_file_path;


	void Initialize_Background();
	void Initialize_Font();
	void Initialize_Exit_Button();
	void Initialize_Score_Table();
	void Fill_Score_Table();

	void Get_Mouse_Position(sf::RenderWindow*& target);
	void Get_Save_file();
public:
	Leaderboard();
	~Leaderboard();

	int Get_Score();
	void Render(sf::RenderWindow*& target);
	void Update(sf::RenderWindow*& target);
	void Update_Events(sf::RenderWindow*& target, State& state);
};

