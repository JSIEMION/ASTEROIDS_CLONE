#include "Leaderboard.h"

void Leaderboard::Initialize_Background()
{
	if (!this->background_texture.loadFromFile("Textures/Background_Texture.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
	else {
		this->background.setTexture(this->background_texture);
	}
}

void Leaderboard::Initialize_Font()
{
	if (!this->font.loadFromFile("Fonts/Games-XvD2.ttf")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Leaderboard::Initialize_Exit_Button()
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

void Leaderboard::Initialize_Score_Table()
{
	this->table_background.setFillColor(sf::Color(0, 0, 0, 75));
	this->table_background.setSize(sf::Vector2f(900, 750));
	this->table_background.setOrigin(sf::Vector2f(450, 375));
	this->table_background.setPosition(sf::Vector2f(500, 400));

	

	for (int i = 0; i < 11; i++) {
	
	}

	for(int i = 0; i < 10; i++){
		sf::FloatRect textRect;
		sf::Text temp1;
		sf::Text temp2;
		std::vector<sf::Text> temp_vec;

		temp1.setFont(font);
		temp1.setFillColor(sf::Color::White);
		temp1.setString("...");
		temp1.setCharacterSize(50);
		textRect = temp1.getLocalBounds();
		temp1.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		temp1.setPosition(sf::Vector2f(1000 / 4, 75 + (75*i)));

		temp_vec.push_back(temp1);

		temp2.setFont(font);
		temp2.setFillColor(sf::Color::White);
		temp2.setString("...");
		temp2.setCharacterSize(50);
		textRect = temp2.getLocalBounds();
		temp2.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		temp2.setPosition(sf::Vector2f(1000 / 4 * 3, 75 + (75 * i)));

		temp_vec.push_back(temp2);
		
		this->top_scores.push_back(temp_vec);
	}
}

void Leaderboard::Fill_Score_Table()
{
	if (!std::filesystem::exists(save_file_path)) {
		std::cout << "Save file doesn't exist \n";
	}
	else {
		std::ifstream file(save_file_path.string());

		if (file.is_open()) {
			std::string line;
			while (std::getline(file, line)) {
				std::vector<std::string> temp;
				std::istringstream input_string(line);
				std::string name;
				std::string score;
				if (input_string >> name >> score) {
					temp.push_back(name);
					temp.push_back(score);
					this->scores.push_back(temp);
				}
			}

			std::ranges::sort(this->scores, [](std::vector<std::string> vec1, std::vector<std::string> vec2) { return std::stoi(vec1[1]) > std::stoi(vec2[1]); });

			file.close();
		}
		else {
			std::cout << "Save file can't be opened";
		}
	}

	for (int i = 0; i < this->scores.size(); i++) {
		sf::FloatRect textRect;

		this->top_scores[i][0].setString(this->scores[i][0]);
		textRect = this->top_scores[i][0].getLocalBounds();
		this->top_scores[i][0].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

		this->top_scores[i][1].setString(this->scores[i][1]);
		textRect = this->top_scores[i][1].getLocalBounds();
		this->top_scores[i][1].setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	}
}

void Leaderboard::Get_Mouse_Position(sf::RenderWindow*& target)
{
	this->mouse_position = sf::Mouse::getPosition(*target);
}

void Leaderboard::Get_Save_file()
{
	std::filesystem::path temp_path = std::filesystem::current_path();
	this->save_file_path = temp_path.string() + "/Saves/scores.txt";
}

Leaderboard::Leaderboard()
{
	Initialize_Font();
	Initialize_Background();
	Initialize_Exit_Button();
	Initialize_Score_Table();
	Get_Save_file();
	Fill_Score_Table();
}

Leaderboard::~Leaderboard()
{
}

int Leaderboard::Get_Score()
{
	return 0;
}

void Leaderboard::Render(sf::RenderWindow*& target)
{
	target->draw(this->background);

	target->draw(this->table_background);
	
	target->draw(this->exit_button);

	target->draw(this->exit_button_text);

	for (int i = 0; i < 10; i++) {
		target->draw(this->top_scores[i][0]);
		
		target->draw(this->top_scores[i][1]);
	}
}

void Leaderboard::Update(sf::RenderWindow*& target)
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

void Leaderboard::Update_Events(sf::RenderWindow*& target, State& state)
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
