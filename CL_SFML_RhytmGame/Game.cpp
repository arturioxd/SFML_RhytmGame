#include "Game.h"
#include "Notes.h"
Game::Game() 
{
	this->currentState = GameState::MENU;
	this->initMenu();
	//this->initMusic();
	this->initWindow();
	this->initInfo();
	this->initVariables();
	this->initNoteLine();
	this->initChecker();
	
	this->keyPressTimers = std::vector<int>(3, 0);
}

Game:: ~Game() 
{
	delete this->window;
}



// - - - private:

void Game::initWindow() 
{
	this->videoMode.height = 800;
	this->videoMode.width = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Rhytm!", sf::Style::Close);

}

void Game::initVariables()
{
	this->spawnTimer = 0.f;
	this->spawnTimerMax = 500.f;
}

void Game::initNoteLine() 
{
	for (int i = 0; i < 3;i++) {
		this->NoteLine.setFillColor(sf::Color::White);
		this->NoteLine.setSize(sf::Vector2f(200.f, 600.f));
		this->NoteLine.setOutlineColor(sf::Color::Black);
		this->NoteLine.setOutlineThickness(3.f);
		this->NoteLine.setPosition(200.f * i, 0.f);
		
		this->noteLines.push_back(this->NoteLine);
	}
}

void Game::initChecker()
{
	this->checker.setFillColor(sf::Color(191.f, 191.f, 191.f));
	this->checker.setSize(sf::Vector2f(600.f, 50.f));
	this->checker.setPosition(0.f, 500.f);
	this->checker.setOutlineColor(sf::Color::Black);
	this->checker.setOutlineThickness(1.f);

}

void Game::initMenu()
{
	if (!this->font.loadFromFile("C:/UN/CL/CL_SFML_RhytmGame/assets/fonts/Nasa21.ttf"))
	{
		std::cout << "Error: Could not load font!\n";
	}

	this->title.setFont(this->font);
	this->title.setString("Rhythm Game");
	this->title.setCharacterSize(50);
	this->title.setFillColor(sf::Color::Black);
	this->title.setPosition(150.f, 200.f);

	this->instructions.setFont(this->font);
	this->instructions.setString("Press Enter to Start");
	this->instructions.setCharacterSize(20);
	this->instructions.setFillColor(sf::Color::Black);
	this->instructions.setPosition(200.f, 300.f);
}

void Game::initMusic()
{
	if (!this->backgroundMusic.openFromFile("C:/UN/CL/CL_SFML_RhytmGame/assets/music/domecano.ogg"))
	{
		std::cout << "Error: Could not load music file!\n";
	}
	else
	{
		this->backgroundMusic.setLoop(true);
		this->backgroundMusic.setVolume(30); 
	}
}

void Game::initInfo()
{
	
	this->showScore.setFont(this->font);
	this->showScore.setCharacterSize(20);
	this->showScore.setFillColor(sf::Color::Black);
	this->showScore.setPosition(50, 650);

	this->showCurrentStreak.setFont(this->font);
	this->showCurrentStreak.setCharacterSize(20);
	this->showCurrentStreak.setFillColor(sf::Color::Black);
	this->showCurrentStreak.setPosition(230, 650);

	this->showBestStreak.setFont(this->font);
	this->showBestStreak.setCharacterSize(20);
	this->showBestStreak.setFillColor(sf::Color::Black);
	this->showBestStreak.setPosition(430, 650);
	
	this->infoShape.setFillColor(sf::Color(225, 192, 203));
	this->infoShape.setPosition(sf::Vector2f(0.f, 600.f));
	this->infoShape.setSize(sf::Vector2f(600.f, 200.f));
}

void Game::spawnNotes()
{
	if ((this->spawnClock.getElapsedTime().asMilliseconds() >= spawnTimerMax)/* && this->notes.size() < 2*/)
	{
		int lane = rand() % 3;
		
		Notes newNote(lane);
		
		bool tooClose = false;

		for (const auto& note : notes)
		{
			if (newNote.isTooClose(note))
			{
				tooClose = true;
				break;
			}
		}

		if (!tooClose)
		{
			this->notes.emplace_back(lane);
		}

		this->spawnClock.restart();
	}
}

// - - - public:

const bool Game::running() 
{
	return this->window->isOpen();
}

void Game::validatedIntersect(int line, int pressTime, sf::Keyboard::Key key)
{
	bool hit = false;
	for (size_t i = 0; i < notes.size(); i++)
	{
		if (notes[i].getLaneId() == line && notes[i].checkerIntersect(this->checker))
		{
			if (((line == 0) && (key == sf::Keyboard::A)) || ((line == 1) && (key == sf::Keyboard::S)) || ((line == 2) && (key == sf::Keyboard::D)))
			{
				notes[i].toDelete();
				notes[i].wasHit = true;
				hit = true;
				this->hitTrue();
				break;
			}
		}
	}
	if (!hit)
	{
		this->hitFalse();
	}
}

void Game::hitTrue()
{
	this->score++;
	this->currentStreak++;
	if (this->bestStreak < currentStreak)
	{
		this->bestStreak = this->currentStreak;
	}

	std::cout << "Hit! Score: " << this->score << " Streak: " << currentStreak << " Best: " << bestStreak << std::endl;
}

void Game::hitFalse()
{
	this->currentStreak = 0;
	std::cout << "Miss" << std::endl;
}

void Game::pollEvents() 
{
	while (this->window->pollEvent(this->ev)) 
	{

		if (this->currentState == GameState::MENU)
		{
			if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Enter)
			{
				this->currentState = GameState::PLAYING;
				this->backgroundMusic.play();

			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}
		else if (this->currentState == GameState::PLAYING)
		{

			switch (this->ev.type)
			{

			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::KeyPressed:
			{
				int currentTime = this->clock.getElapsedTime().asMilliseconds();
				if (ev.key.code == sf::Keyboard::Escape)
				{
					this->window->close();
				}
				else if (ev.key.code == sf::Keyboard::A)
				{
					this->validatedIntersect(0, currentTime, sf::Keyboard::A);
					this->noteLines[0].setFillColor(sf::Color(189, 195, 199));
					this->keyPressTimers[0] = this->clock.getElapsedTime().asMilliseconds();
				}
				else if (ev.key.code == sf::Keyboard::S)
				{
					this->validatedIntersect(1, currentTime, sf::Keyboard::S);
					this->noteLines[1].setFillColor(sf::Color(189, 195, 199));
					this->keyPressTimers[1] = this->clock.getElapsedTime().asMilliseconds();
				}
				else if (ev.key.code == sf::Keyboard::D)
				{
					this->validatedIntersect(2, currentTime, sf::Keyboard::D);
					this->noteLines[2].setFillColor(sf::Color(189, 195, 199));
					this->keyPressTimers[2] = this->clock.getElapsedTime().asMilliseconds();
				}
			}
			}
		}
		
	}
}

void Game::updateChecker()
{
	int currentTime = this->clock.getElapsedTime().asMilliseconds();
	if (currentTime - this->checkerTimer >= 300) {
		this->checker.setFillColor(sf::Color::Black);
	}

}

void Game::updateNoteLine() 
{
	int currentTime = this->clock.getElapsedTime().asMilliseconds();
	for (size_t i = 0; i < this->noteLines.size(); i++) {
		if (currentTime - this->keyPressTimers[i] >= 100) {
			this->noteLines[i].setFillColor(sf::Color::White);
		}
	}
}

void Game::updateMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
	{
		this->currentState = PLAYING;
	}
}

void Game::updateInfo()
{
	this->showScore.setString("Score: " + std::to_string(this->score));
	this->showCurrentStreak.setString("Current streak: " + std::to_string(this->currentStreak));
	this->showBestStreak.setString("Best streak: " + std::to_string(this->bestStreak));
}

void Game::update()
{
	this->pollEvents();
	if (this->currentState == PLAYING)
	{
		this->updateNoteLine();
		this->updateChecker();
		this->updateInfo();
		this->spawnNotes();

		for (size_t i = 0; i < notes.size(); i++)
		{
			if (!notes[i].getAct() || this->notes[i].isOffScreen())
			{
				if (!notes[i].wasHit)
				{
					this->hitFalse();
				}

				this->notes.erase(this->notes.begin() + i);
				i--;
			}
			else
			{
				notes[i].updateNote();
			}
		}
	}
}

void Game::renderChecker()
{
	this->window->draw(checker);
}

void Game::renderNoteLine() 
{
	for (auto& line : this->noteLines) {

		this->window->draw(line);
	}
}

void Game::renderMenu()
{
	this->window->draw(title);
	this->window->draw(instructions);
}

void Game::renderInfo()
{
	this->window->draw(infoShape);
	this->window->draw(showScore);
	this->window->draw(showCurrentStreak);
	this->window->draw(showBestStreak);

}

void Game::render() 
{
	this->window->clear(sf::Color::White);

	if (this->currentState == MENU)
	{
		this->renderMenu();
	}
	else if (this->currentState == PLAYING)
	{
		this->renderInfo();

		this->renderNoteLine();

		this->renderChecker();

		for (auto& note : notes)
		{
			note.renderNote(*this->window);

		}
	}
	this->window->display();
} 