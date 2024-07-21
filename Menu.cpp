#include "Menu.h"

void Menu::Initialize_Buttons()
{
	


	this->play_button_text.setFont(menu_font);
	this->play_button_text.setFillColor(sf::Color::White);
	this->play_button_text.setString("PLAY");
	this->play_button_text.setCharacterSize(80);
	this->play_button_rect = play_button_text.getLocalBounds();
	this->play_button_text.setOrigin(play_button_rect.left + play_button_rect.width / 2.0f, play_button_rect.top + play_button_rect.height / 2.0f);
	this->play_button_text.setPosition(sf::Vector2f(1000 / 2.0f, 400));

	this->leaderboard_button_text.setFont(menu_font);
	this->leaderboard_button_text.setFillColor(sf::Color::White);
	this->leaderboard_button_text.setString("LEADERBOARD");
	this->leaderboard_button_text.setCharacterSize(80);
	this->leaderboard_button_rect = leaderboard_button_text.getLocalBounds();
	this->leaderboard_button_text.setOrigin(leaderboard_button_rect.left + leaderboard_button_rect.width / 2.0f, leaderboard_button_rect.top + leaderboard_button_rect.height / 2.0f);
	this->leaderboard_button_text.setPosition(sf::Vector2f(1000 / 2.0f, 500));

	this->help_button_text.setFont(menu_font);
	this->help_button_text.setFillColor(sf::Color::White);
	this->help_button_text.setString("HELP");
	this->help_button_text.setCharacterSize(80);
	this-> help_button_rect = help_button_text.getLocalBounds();
	this->help_button_text.setOrigin(help_button_rect.left + help_button_rect.width / 2.0f, help_button_rect.top + help_button_rect.height / 2.0f);
	this->help_button_text.setPosition(sf::Vector2f(1000 / 2.0f, 600));

	this->exit_button_text.setFont(menu_font);
	this->exit_button_text.setFillColor(sf::Color::White);
	this->exit_button_text.setString("EXIT");
	this->exit_button_text.setCharacterSize(80);
	this->exit_button_rect = exit_button_text.getLocalBounds();
	this->exit_button_text.setOrigin(exit_button_rect.left + exit_button_rect.width / 2.0f, exit_button_rect.top + exit_button_rect.height / 2.0f);
	this->exit_button_text.setPosition(sf::Vector2f(1000 / 2.0f, 700));
}

void Menu::Initialize_Title()
{

	sf::FloatRect textRect;
	this->title_text.setFont(menu_font);
	this->title_text.setFillColor(sf::Color::White);
	this->title_text.setString("ASTEROIDS");
	this->title_text.setCharacterSize(80);
	textRect = title_text.getLocalBounds();
	this->title_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->title_text.setPosition(sf::Vector2f(1000 / 2.0f, 100));
}

void Menu::Initialize_Font()
{
	if (!this->menu_font.loadFromFile("Fonts/Games-XvD2.ttf")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Menu::Initialize_Background()
{
	if (!this->background_texture.loadFromFile("Textures/Background_Texture.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
	else {
		this->background.setTexture(this->background_texture);
	}
}

void Menu::Get_Mouse_Position(sf::RenderWindow*& target)
{
	this->mouse_position = sf::Mouse::getPosition(*target);
}

Menu::Menu()
{
	this->Initialize_Font();
	this->Initialize_Title();
	this->Initialize_Buttons();
	this->Initialize_Background();
}

Menu::~Menu()
{

}

int Menu::Get_Score()
{
	return 0;
}

void Menu::Render(sf::RenderWindow*& target)
{
	target->draw(this->background);

	target->draw(this->title_text);
	
	target->draw(this->play_button_text);
	
	target->draw(this->leaderboard_button_text);
	
	target->draw(this->help_button_text);
	
	target->draw(this->exit_button_text);

}

void Menu::Update(sf::RenderWindow*& target)
{
	//this->Update_Events(target);
	this->Get_Mouse_Position(target);

	//Play button outline
	if (mouse_position.x >= play_button_text.getPosition().x - play_button_rect.width/2 &&
		mouse_position.x <= play_button_text.getPosition().x + play_button_rect.width/2
		&& mouse_position.y >= play_button_text.getPosition().y - play_button_rect.height/2 &&
		mouse_position.y <= play_button_text.getPosition().y + play_button_rect.height/2) {
		this->play_button_text.setOutlineColor(sf::Color::Blue);
		this->play_button_text.setOutlineThickness(5);
	}
	else {
		this->play_button_text.setOutlineColor(sf::Color::Transparent);
		this->play_button_text.setOutlineThickness(0);
	}

	//Leaderboard button outline
	if (mouse_position.x >= leaderboard_button_text.getPosition().x - leaderboard_button_rect.width / 2 &&
		mouse_position.x <= leaderboard_button_text.getPosition().x + leaderboard_button_rect.width / 2
		&& mouse_position.y >= leaderboard_button_text.getPosition().y - leaderboard_button_rect.height / 2 &&
		mouse_position.y <= leaderboard_button_text.getPosition().y + leaderboard_button_rect.height / 2) {
		this->leaderboard_button_text.setOutlineColor(sf::Color::Blue);
		this->leaderboard_button_text.setOutlineThickness(5);
	}
	else {
		this->leaderboard_button_text.setOutlineColor(sf::Color::Transparent);
		this->leaderboard_button_text.setOutlineThickness(0);
	}

	//Help button outline
	if (mouse_position.x >= help_button_text.getPosition().x - help_button_rect.width / 2 &&
		mouse_position.x <= help_button_text.getPosition().x + help_button_rect.width / 2
		&& mouse_position.y >= help_button_text.getPosition().y - help_button_rect.height / 2 &&
		mouse_position.y <= help_button_text.getPosition().y + help_button_rect.height / 2) {
		this->help_button_text.setOutlineColor(sf::Color::Blue);
		this->help_button_text.setOutlineThickness(5);
	}
	else {
		this->help_button_text.setOutlineColor(sf::Color::Transparent);
		this->help_button_text.setOutlineThickness(0);
	}

	//Exit button outline
	if (mouse_position.x >= exit_button_text.getPosition().x - exit_button_rect.width / 2 &&
		mouse_position.x <= exit_button_text.getPosition().x + exit_button_rect.width / 2
		&& mouse_position.y >= exit_button_text.getPosition().y - exit_button_rect.height / 2 &&
		mouse_position.y <= exit_button_text.getPosition().y + exit_button_rect.height / 2) {
		this->exit_button_text.setOutlineColor(sf::Color::Blue);
		this->exit_button_text.setOutlineThickness(5);
	}
	else {
		this->exit_button_text.setOutlineColor(sf::Color::Transparent);
		this->exit_button_text.setOutlineThickness(0);
	}
}

void Menu::Update_Events(sf::RenderWindow*& target, State& state)
{
	while (target->pollEvent(this->event)) {
		switch (this->event.type) {

		case sf::Event::Closed:
			target->close();
			break;

		case sf::Event::MouseButtonPressed:
			if (mouse_position.x >= play_button_text.getPosition().x - play_button_rect.width / 2 &&
				mouse_position.x <= play_button_text.getPosition().x + play_button_rect.width / 2
				&& mouse_position.y >= play_button_text.getPosition().y - play_button_rect.height / 2 &&
				mouse_position.y <= play_button_text.getPosition().y + play_button_rect.height / 2) {
				state = State::game;
			}

			if (mouse_position.x >= exit_button_text.getPosition().x - exit_button_rect.width / 2 &&
				mouse_position.x <= exit_button_text.getPosition().x + exit_button_rect.width / 2
				&& mouse_position.y >= exit_button_text.getPosition().y - exit_button_rect.height / 2 &&
				mouse_position.y <= exit_button_text.getPosition().y + exit_button_rect.height / 2) {
				state = State::exit;
			}
			
			if (mouse_position.x >= leaderboard_button_text.getPosition().x - leaderboard_button_rect.width / 2 &&
				mouse_position.x <= leaderboard_button_text.getPosition().x + leaderboard_button_rect.width / 2
				&& mouse_position.y >= leaderboard_button_text.getPosition().y - leaderboard_button_rect.height / 2 &&
				mouse_position.y <= leaderboard_button_text.getPosition().y + leaderboard_button_rect.height / 2) {
				state = State::leaderboard;
			}

			if (mouse_position.x >= help_button_text.getPosition().x - help_button_rect.width / 2 &&
				mouse_position.x <= help_button_text.getPosition().x + help_button_rect.width / 2
				&& mouse_position.y >= help_button_text.getPosition().y - help_button_rect.height / 2 &&
				mouse_position.y <= help_button_text.getPosition().y + help_button_rect.height / 2) {
				state = State::help;
				std::cout << "ok";
			}
			
			break;
		}
	}
}
