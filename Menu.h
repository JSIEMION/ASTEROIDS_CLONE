#pragma once
#include "Interface.h"

class Menu :
    public Interface
{
private:
	//Font
	sf::Font menu_font;

	//Background
	sf::Texture background_texture;
	sf::Sprite background;

	//Title
	sf::Text title_text;

	//Play button
	sf::FloatRect play_button_rect;
	sf::Text play_button_text;
	
	//Leaderboadr button
	sf::FloatRect leaderboard_button_rect;
	sf::Text leaderboard_button_text;
	
	//Help button
	sf::FloatRect help_button_rect;
	sf::Text help_button_text;

	//Exit button
	sf::FloatRect exit_button_rect;
	sf::Text exit_button_text;

	//Mouse position
	sf::Vector2i mouse_position;

	//Event
	sf::Event event;

	void Initialize_Buttons();
	void Initialize_Title();
	void Initialize_Font();
	void Initialize_Background();

	void Get_Mouse_Position(sf::RenderWindow*& target);

public:
	Menu();
	~Menu();

	int Get_Score();
	void Render(sf::RenderWindow*& target);
	void Update(sf::RenderWindow*& target);
	void Update_Events(sf::RenderWindow*& target, State& state);
};

