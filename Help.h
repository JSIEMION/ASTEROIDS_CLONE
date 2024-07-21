#pragma once
#include "Interface.h"
class Help :
    public Interface
{
private:
    //Font
    sf::Font font;

    //Background
    sf::Texture background_texture;
    sf::Sprite background;

    //Event
    sf::Event event;

    //Exit button
    sf::RectangleShape exit_button;
    sf::Text exit_button_text;

    //Mouse position
    sf::Vector2i mouse_position;

    //Text background
    sf::RectangleShape text_background;

    //Text
    std::vector<sf::Text> help_text;

    void Initialize_Background();
    void Initialize_Font();
    void Initialize_Exit_Button();
    void Initialize_Text();

    void Get_Mouse_Position(sf::RenderWindow*& target);

public:
    Help();
    ~Help();

    int Get_Score();
    void Render(sf::RenderWindow*& target);
    void Update(sf::RenderWindow*& target);
    void Update_Events(sf::RenderWindow*& target, State& state);
};

