#include "Help.h"

void Help::Initialize_Background()
{
	if (!this->background_texture.loadFromFile("Textures/Background_Texture.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
	else {
		this->background.setTexture(this->background_texture);
	}
}

void Help::Initialize_Font()
{
	if (!this->font.loadFromFile("Fonts/Games-XvD2.ttf")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Help::Initialize_Exit_Button()
{
	this->exit_button.setFillColor(sf::Color(0, 0, 75, 255));
	this->exit_button.setOutlineColor(sf::Color(0, 0, 175, 255));
	this->exit_button.setOutlineThickness(5);
	this->exit_button.setSize(sf::Vector2f(300, 100));
	this->exit_button.setOrigin(sf::Vector2f(150, 50));
	this->exit_button.setPosition(sf::Vector2f(1000 / 2, 900));

	sf::FloatRect textRect;
	this->exit_button_text.setFont(font);
	this->exit_button_text.setFillColor(sf::Color::White);
	this->exit_button_text.setString("MAIN MENU");
	this->exit_button_text.setCharacterSize(50);
	textRect = exit_button_text.getLocalBounds();
	this->exit_button_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->exit_button_text.setPosition(sf::Vector2f(1000 / 2, 900));
}

void Help::Initialize_Text()
{
	this->text_background.setFillColor(sf::Color(0, 0, 0, 75));
	this->text_background.setSize(sf::Vector2f(900, 750));
	this->text_background.setOrigin(sf::Vector2f(450, 375));
	this->text_background.setPosition(sf::Vector2f(500, 400));

	for (int i = 0; i < 12; i++) {

		sf::Text temp1;

		temp1.setFont(font);
		temp1.setFillColor(sf::Color::White);
		temp1.setCharacterSize(20);



		this->help_text.push_back(temp1);
	}
	help_text[0].setString("Goal of this game is to destroy enemies");
	help_text[1].setString("and avoid being hit by them or their bullets.");
	help_text[2].setString("Controls:");
	help_text[3].setString("Left/Right arrows: rotate player ship in a corresponding direction");
	help_text[4].setString("Up arrow: move player forwards (towards its facing direction)");
	help_text[5].setString("Space: fire bullet");
	help_text[6].setString("Escepe: end game");
	help_text[7].setString("After game you can save your score.");
	help_text[8].setString("in order to do so you must write your nick after a game on game over screen");
	help_text[9].setString("10 highest scores are displayed in LEADERBOARD panel");
	help_text[10].setString("if you don't write your nick your score wont be saved.");
	help_text[11].setString("Nick can contain only letters and numbers!");
	
	for (int i = 0; i < 12; i++) {
		sf::FloatRect textRect;

		textRect = help_text[i].getLocalBounds();
		help_text[i].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		help_text[i].setPosition(sf::Vector2f(1000 / 2, 75 + (50 * i)));


	}
}

void Help::Get_Mouse_Position(sf::RenderWindow*& target)
{
	this->mouse_position = sf::Mouse::getPosition(*target);
}

Help::Help()
{
	Initialize_Background();
	Initialize_Font();
	Initialize_Exit_Button();
	Initialize_Text();
}

Help::~Help()
{
}

int Help::Get_Score()
{
	return 0;
}

void Help::Render(sf::RenderWindow*& target)
{
	target->draw(this->background);

	target->draw(this->exit_button);

	target->draw(this->exit_button_text);

	target->draw(this->text_background);

	for (int i = 0; i < 12; i++) {
		target->draw(this->help_text[i]);
	}

}

void Help::Update(sf::RenderWindow*& target)
{
	this->Get_Mouse_Position(target);

	if (mouse_position.x >= exit_button.getPosition().x - exit_button.getLocalBounds().width / 2 &&
		mouse_position.x <= exit_button.getPosition().x + exit_button.getLocalBounds().width / 2
		&& mouse_position.y >= exit_button.getPosition().y - exit_button.getLocalBounds().height / 2 &&
		mouse_position.y <= exit_button.getPosition().y + exit_button.getLocalBounds().height / 2) {
		this->exit_button.setFillColor(sf::Color(0, 0, 175, 255));
	}
	else {
		this->exit_button.setFillColor(sf::Color(0, 0, 75, 255));
	}
}

void Help::Update_Events(sf::RenderWindow*& target, State& state)
{
	while (target->pollEvent(this->event)) {
		switch (this->event.type) {

		case sf::Event::Closed:
			target->close();
			break;

		case sf::Event::MouseButtonPressed:

			if (mouse_position.x >= exit_button.getPosition().x - exit_button.getLocalBounds().width / 2 &&
				mouse_position.x <= exit_button.getPosition().x + exit_button.getLocalBounds().width / 2
				&& mouse_position.y >= exit_button.getPosition().y - exit_button.getLocalBounds().height / 2 &&
				mouse_position.y <= exit_button.getPosition().y + exit_button.getLocalBounds().height / 2) {
				state = State::menu;
			}
			break;


		}
	}
}
