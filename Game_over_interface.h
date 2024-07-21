#pragma once
#include "Interface.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <ranges>
#include <regex>

class Game_over_interface :
    public Interface
{
private:
	int end_score;

	//Font
	sf::Font game_over_font;

	//Background
	sf::Texture background_texture;
	sf::Sprite background;

	//Game over text
	sf::Text game_over_text;

	//Score text
	sf::Text score_text;
	sf::Text your_score_text;
	sf::FloatRect your_score_text_size;

	//Event
	sf::Event event;

	//Nick
	sf::RectangleShape nick_box;
	bool nick_box_clicked;
	sf::Text nick;
	std::string nick_string;
	sf::FloatRect nick_size;
	sf::Text nick_text;
	sf::FloatRect nick_text_size;

	//Mouse position
	sf::Vector2i mouse_position;

	//Save score and exit button
	sf::RectangleShape save_and_exit_button;
	sf::Text save_and_exit_button_text;

	//Save file
	std::filesystem::path save_file_path;

	void Initialize_Font();
	void Initialize_Background();
	void Initialize_Score(int& end_score);
	void Initialize_Text();
	void Initialize_Textbox();
	void Initialize_Variables();
	void Initialize_SE_Button();
	void Get_Save_file();
	void Save_Score();

	void Get_Mouse_Position(sf::RenderWindow*& target);
public:
	Game_over_interface(int& end_score);
	~Game_over_interface();
	int Get_Score();
	void Render(sf::RenderWindow*& target);
	void Update(sf::RenderWindow*& target);
	void Update_Events(sf::RenderWindow*& target, State& state);
};

