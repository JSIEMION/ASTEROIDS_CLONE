#include "Game_over_interface.h"

void Game_over_interface::Initialize_Font()
{
	if (!this->game_over_font.loadFromFile("Fonts/Games-XvD2.ttf")) {
		std::cerr << "File can't be loaded" << "\n";
	}
}

void Game_over_interface::Initialize_Background()
{
	if (!this->background_texture.loadFromFile("Textures/Background_Texture.png")) {
		std::cerr << "File can't be loaded" << "\n";
	}
	else {
		this->background.setTexture(this->background_texture);
	}
}

void Game_over_interface::Initialize_Score(int& end_score)
{
	this->end_score = end_score;
}

void Game_over_interface::Initialize_Text()
{
	sf::FloatRect textRect;
	this->game_over_text.setFont(game_over_font);
	this->game_over_text.setFillColor(sf::Color::White);
	this->game_over_text.setString("GAME OVER");
	this->game_over_text.setCharacterSize(80);
	textRect = game_over_text.getLocalBounds();
	this->game_over_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->game_over_text.setPosition(sf::Vector2f(1000 / 2.0f, 100));

	this->score_text.setFont(game_over_font);
	this->score_text.setFillColor(sf::Color::White);
	this->score_text.setString("0");
	this->score_text.setCharacterSize(80);
	textRect = score_text.getLocalBounds();
	this->score_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->score_text.setPosition(sf::Vector2f(1000 / 3.0f, 500));
}

void Game_over_interface::Initialize_Textbox()
{
	this->nick_box.setFillColor(sf::Color(200, 200, 200, 255));
	this->nick_box.setSize(sf::Vector2f(300, 100));
	this->nick_box.setOrigin(sf::Vector2f(150, 50));
	this->nick_box.setPosition(sf::Vector2f(1000 * 2 / 3, 500));

	this->nick.setFont(game_over_font);
	this->nick.setFillColor(sf::Color::Black);
	this->nick.setString(nick_string);
	this->nick.setCharacterSize(80);
	this->nick_size = this->nick.getLocalBounds();
	this->nick.setOrigin(nick_size.width / 2, nick_size.height / 2);
	this->nick.setPosition(1000 * 2 / 3, 475);

	this->nick_text.setFont(game_over_font);
	this->nick_text.setFillColor(sf::Color::White);
	this->nick_text.setString("nick:");
	this->nick_text.setCharacterSize(80);
	this->nick_text_size = this->nick_text.getLocalBounds();
	this->nick_text.setOrigin(nick_text_size.width / 2, nick_text_size.height / 2);
	this->nick_text.setPosition(1000 * 2 / 3, 375);

	this->your_score_text.setFont(game_over_font);
	this->your_score_text.setFillColor(sf::Color::White);
	this->your_score_text.setString("score:");
	this->your_score_text.setCharacterSize(80);
	this->your_score_text_size = this->your_score_text.getLocalBounds();
	this->your_score_text.setOrigin(your_score_text_size.width / 2, your_score_text_size.height / 2);
	this->your_score_text.setPosition(1000 / 3, 375);
}

void Game_over_interface::Initialize_Variables()
{
	this->nick_box_clicked = false;
	this->nick_string = "";
}

void Game_over_interface::Initialize_SE_Button()
{
	this->save_and_exit_button.setFillColor(sf::Color(0, 0, 75, 255));
	this->save_and_exit_button.setOutlineColor(sf::Color(0, 0, 175, 255));
	this->save_and_exit_button.setOutlineThickness(5);
	this->save_and_exit_button.setSize(sf::Vector2f(400, 100));
	this->save_and_exit_button.setOrigin(sf::Vector2f(200, 50));
	this->save_and_exit_button.setPosition(sf::Vector2f(1000 / 2, 800));

	sf::FloatRect textRect;
	this->save_and_exit_button_text.setFont(game_over_font);
	this->save_and_exit_button_text.setFillColor(sf::Color::White);
	this->save_and_exit_button_text.setString("SAVE AND EXIT");
	this->save_and_exit_button_text.setCharacterSize(50);
	textRect = save_and_exit_button_text.getLocalBounds();
	this->save_and_exit_button_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	this->save_and_exit_button_text.setPosition(sf::Vector2f(1000 / 2, 800));
}

void Game_over_interface::Get_Save_file()
{
	std::filesystem::path temp_path = std::filesystem::current_path();
	this->save_file_path = temp_path.string() + "/Saves/scores.txt";
}

void Game_over_interface::Save_Score()
{
	if (!std::filesystem::exists(save_file_path)) {
		std::cout << "Save file doesn't exist \n";
		return;
	}
	if (this->nick_string.size() == 0) {
		return;
	}
	std::vector<std::vector<std::string>> scores;
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
				scores.push_back(temp);
			}
		}
		{
			std::vector<std::string> new_score;
			new_score.push_back(this->nick_string);
			new_score.push_back(std::to_string(this->end_score));
			scores.push_back(new_score);
		}
		
		std::ranges::sort(scores, [](std::vector<std::string> vec1, std::vector<std::string> vec2) { return std::stoi(vec1[1]) > std::stoi(vec2[1]); });
		
			file.close();
	}
	else {
		std::cout << "Save file can't be opened";
	}
	std::ofstream output_file(save_file_path.string());
	if (output_file.is_open()) {
		auto expr = std::regex("(\\d|[A-Z]){1,5}");
		for (auto a : scores) {
			if (std::regex_match(a[0], expr)){
				std::string temp;
				temp = a[0] + ' ' + a[1] + '\n';
				output_file << temp;
			}
			else {
				std::cout << "Nick didn't match REGEX";
			}
		}
		output_file.close();
	}
	else {
		std::cout << "Can't access save file";
	}
}

void Game_over_interface::Get_Mouse_Position(sf::RenderWindow*& target)
{
	this->mouse_position = sf::Mouse::getPosition(*target);	
}

Game_over_interface::Game_over_interface(int& end_score)
{
	Initialize_Variables();
	Initialize_Font();
	Initialize_Background();
	Initialize_Score(end_score);
	Initialize_Text();
	Initialize_Textbox();
	Initialize_SE_Button();
	Get_Save_file();
}

Game_over_interface::~Game_over_interface()
{
}

int Game_over_interface::Get_Score()
{
	return 0;
}

void Game_over_interface::Render(sf::RenderWindow*& target)
{
	target->draw(this->background);

	target->draw(this->game_over_text);

	target->draw(this->score_text);

	target->draw(this->nick_box);

	target->draw(this->nick);

	target->draw(this->save_and_exit_button);

	target->draw(this->save_and_exit_button_text);

	target->draw(this->nick_text);

	target->draw(this->your_score_text);
}

void Game_over_interface::Update(sf::RenderWindow*& target)
{

	this->Get_Mouse_Position(target);

	std::string temp_string = this->score_text.getString();
	int temp_score = std::stoi(temp_string);
	if (temp_score < end_score) {
		if (end_score - temp_score > 5000) {
			temp_score += 100;
			this->score_text.setString(std::to_string(temp_score));
		}
		else if (end_score - temp_score > 500) {
			temp_score += 10;
			this->score_text.setString(std::to_string(temp_score));
		}
		else {
			temp_score++;
			this->score_text.setString(std::to_string(temp_score));
		}
	}

	if (mouse_position.x >= save_and_exit_button.getPosition().x - save_and_exit_button.getLocalBounds().width / 2 &&
		mouse_position.x <= save_and_exit_button.getPosition().x + save_and_exit_button.getLocalBounds().width / 2
		&& mouse_position.y >= save_and_exit_button.getPosition().y - save_and_exit_button.getLocalBounds().height / 2 &&
		mouse_position.y <= save_and_exit_button.getPosition().y + save_and_exit_button.getLocalBounds().height / 2) {
		this->save_and_exit_button.setFillColor(sf::Color(0, 0, 175, 255));
	}
	else {
		this->save_and_exit_button.setFillColor(sf::Color(0, 0, 75, 255));
	}
}

void Game_over_interface::Update_Events(sf::RenderWindow*& target, State& state)
{
	while (target->pollEvent(this->event)) {
		switch (this->event.type) {

		case sf::Event::Closed:
			target->close();
			break;

		case sf::Event::MouseButtonPressed:
			if (mouse_position.x >= nick_box.getPosition().x - nick_box.getLocalBounds().width / 2 &&
				mouse_position.x <= nick_box.getPosition().x + nick_box.getLocalBounds().width / 2
				&& mouse_position.y >= nick_box.getPosition().y - nick_box.getLocalBounds().height / 2 &&
				mouse_position.y <= nick_box.getPosition().y + nick_box.getLocalBounds().height / 2) {
				this->nick_box_clicked = true;
				this->nick_box.setFillColor(sf::Color::White);
			}
			else {
				this->nick_box_clicked = false;
				this->nick_box.setFillColor(sf::Color(200,200,200,255));
			}

			if (mouse_position.x >= save_and_exit_button.getPosition().x - save_and_exit_button.getLocalBounds().width / 2 &&
				mouse_position.x <= save_and_exit_button.getPosition().x + save_and_exit_button.getLocalBounds().width / 2
				&& mouse_position.y >= save_and_exit_button.getPosition().y - save_and_exit_button.getLocalBounds().height / 2 &&
				mouse_position.y <= save_and_exit_button.getPosition().y + save_and_exit_button.getLocalBounds().height / 2) {
				Save_Score();
				state = State::menu;
			}
			break;
		case sf::Event::TextEntered:
			if (this->nick_box_clicked) {
				if (this->nick_string.size() < 5 && 
					(this->event.text.unicode >= 48 && this->event.text.unicode <= 57 ||
					this->event.text.unicode >= 65 && this->event.text.unicode <= 90 ||
					this->event.text.unicode >= 97 && this->event.text.unicode <= 122)) {
					if (this->event.text.unicode >= 97 && this->event.text.unicode <= 122) {
						this->event.text.unicode -= 32;
					}
					this->nick_string.push_back((char)this->event.text.unicode);
					this->nick.setString(nick_string);
					this->nick_size = this->nick.getLocalBounds();
					this->nick.setOrigin(nick_size.width / 2, nick_size.height / 2);
				}
				if (this->nick_string.size() > 0 && this->event.text.unicode == 8) {
					this->nick_string.pop_back();
					this->nick.setString(nick_string);
					this->nick_size = this->nick.getLocalBounds();
					this->nick.setOrigin(nick_size.width / 2, nick_size.height / 2);
				}
			}
			break;

		}
	}
}
