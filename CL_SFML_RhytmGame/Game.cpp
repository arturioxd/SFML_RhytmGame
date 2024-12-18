#include "Game.h"
#include "Notes.h"
Game::Game() 
{
	this->currentState = GameState::MENU;
	this->initVariables();
	this->initMenu();
	this->initMusic();
	this->initWindow();
	this->initInfo();
	this->initNoteLine();
	this->initChecker();
	this->initGameOver();
	this->window->setFramerateLimit(60);

	this->keyPressTimers = std::vector<int>(3, 0);
}

Game:: ~Game() 
{
	delete this->window;
}



// - - - private:

void Game::initWindow() 
{
	this->videoMode.height = 700;
	this->videoMode.width = 600;
	this->window = new sf::RenderWindow(this->videoMode, "Rhytm!", sf::Style::Close);

}

void Game::initVariables()
{
	this->spawnTimer = 0.f;
	this->spawnTimerMax = 500.f;

	this->hitTrueText.setString("Good!");
	this->hitTrueText.setFont(this->font);
	this->hitTrueText.setCharacterSize(100);
	this->hitTrueText.setFillColor(sf::Color::Green);
	this->hitTrueText.setPosition(200.f, 100.f);
	this->hitTrueText.setOutlineColor(sf::Color::Black);
	this->hitTrueText.setOutlineThickness(1.f);

	this->hitFalseText.setString("Bad!");
	this->hitFalseText.setFont(this->font);
	this->hitFalseText.setCharacterSize(100);
	this->hitFalseText.setFillColor(sf::Color::Red);
	this->hitFalseText.setPosition(200.f, 100.f);
	this->hitFalseText.setOutlineColor(sf::Color::Black);
	this->hitFalseText.setOutlineThickness(1.f);

	this->hitTextDuration = 0.5f;

	this->BPM = 120.0f;
	this->spawnInterval = (60.0f / this->BPM) * 1000.0f;

	this->delayTime = 3.f;

	this->health = 3;

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
	this->instructions.setString("Press [Enter] to Start\nUse [A] [S] [D] buttons to play!");
	this->instructions.setCharacterSize(20);
	this->instructions.setFillColor(sf::Color::Black);
	this->instructions.setPosition(200.f, 300.f);
}

void Game::initMusic()
{

	if (!this->backgroundMusic.openFromFile("C:/UN/CL/CL_SFML_RhytmGame/assets/music/bitQuest.ogg"))
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
	this->showScore.setCharacterSize(40);
	this->showScore.setFillColor(sf::Color::Black);
	this->showScore.setPosition(20, 620);

	this->showCurrentStreak.setFont(this->font);
	this->showCurrentStreak.setCharacterSize(40);
	this->showCurrentStreak.setFillColor(sf::Color::Black);
	this->showCurrentStreak.setPosition(220, 620);

	this->showBestStreak.setFont(this->font);
	this->showBestStreak.setCharacterSize(40);
	this->showBestStreak.setFillColor(sf::Color::Black);
	this->showBestStreak.setPosition(420, 620);
	
	this->infoShape.setFillColor(sf::Color(225, 192, 203));
	this->infoShape.setPosition(sf::Vector2f(0.f, 600.f));
	this->infoShape.setSize(sf::Vector2f(600.f, 100.f));
}

void Game::initGameOver()
{
	this->gameOverText.setFont(this->font);
	this->gameOverText.setString("Game Over ! \nPress [R] to try again");
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setPosition(100.f, 200.f);
}

void Game::spawnNotes()
{
	if ((this->noteSpawnClock.getElapsedTime().asMilliseconds() >= this->spawnInterval))
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

		this->noteSpawnClock.restart();
	}
}

void Game::resetGame()
{
	this->score = 0;
	this->currentStreak = 0;
	this->bestStreak = 0;
	this->health = 3;

	this->notes.clear(); 
	this->backgroundMusic.stop();
	this->isMusicPlaying = false; 
	this->delayMusicClock.restart();

	this->showHitTrueText = false;
	this->showHitFalseText = false;
}



// - - - public:

const bool Game::running() 
{
	return this->window->isOpen();
}

void Game::validatedIntersect(int line, sf::Keyboard::Key key)
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
	
	this->showHitTrueText = true;
	this->showHitFalseText = false;
	this->hitTextClock.restart();
}

void Game::hitFalse()
{
	this->currentStreak = 0;
	this->health--;

	this->window->draw(hitFalseText);

	this->showHitTrueText = false;
	this->showHitFalseText = true;
	this->hitTextClock.restart();
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

			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}
		else if (this->currentState == GameState::PLAYING)
		{
			if (!isMusicPlaying && delayMusicClock.getElapsedTime().asSeconds() >= delayTime)
			{
				this->backgroundMusic.play();
				isMusicPlaying = true;
			}
			switch (this->ev.type)
			{

			case sf::Event::Closed:
				this->window->close();
				break;

			case sf::Event::KeyPressed:
			{
				if (ev.key.code == sf::Keyboard::Escape)
				{
					this->window->close();
				}
				else if (ev.key.code == sf::Keyboard::A)
				{
					this->validatedIntersect(0, sf::Keyboard::A);
					this->noteLines[0].setFillColor(sf::Color(189, 195, 199));
					this->keyPressTimers[0] = this->clock.getElapsedTime().asMilliseconds();
				}
				else if (ev.key.code == sf::Keyboard::S)
				{
					this->validatedIntersect(1, sf::Keyboard::S);
					this->noteLines[1].setFillColor(sf::Color(189, 195, 199));
					this->keyPressTimers[1] = this->clock.getElapsedTime().asMilliseconds();
				}
				else if (ev.key.code == sf::Keyboard::D)
				{
					this->validatedIntersect(2, sf::Keyboard::D);
					this->noteLines[2].setFillColor(sf::Color(189, 195, 199));
					this->keyPressTimers[2] = this->clock.getElapsedTime().asMilliseconds();
				}
			}
			}
		}
		else if (this->currentState == GAME_OVER)
		{
			if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::R)
			{
				this->resetGame();
				this->currentState = PLAYING;
			}
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
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
	this->showCurrentStreak.setString("Streak: " + std::to_string(this->currentStreak));
	this->showBestStreak.setString("Health: " + std::to_string(this->health));
}

void Game::update()
{
	sf::Time deltaTime = this->frameClock.restart();

	this->pollEvents();
	if (this->currentState == PLAYING && this->health > 0)
	{
		this->updateNoteLine();
		this->updateChecker();
		this->updateInfo();
		this->spawnNotes();

		if (this->hitTextClock.getElapsedTime().asSeconds() >= this->hitTextDuration)
		{
			this->showHitTrueText = false;
			this->showHitFalseText = false;
		}

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
				notes[i].updateNote(deltaTime);
			}
		}
	}
	else if (this->health == 0)
	{
		this->currentState = GAME_OVER;
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

void Game::renderGameOver()
{
	this->window->draw(gameOverText);
	this->backgroundMusic.stop();
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

		if (this->showHitTrueText)
		{
			this->window->draw(hitTrueText);
		}
		else if (this->showHitFalseText)
		{
			this->window->draw(hitFalseText);
		}

	}
	else if (this->currentState == GAME_OVER)
	{
		this->renderGameOver();
	}
	this->window->display();
} 