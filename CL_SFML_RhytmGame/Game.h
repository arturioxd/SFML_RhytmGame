#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Notes.h"
#include <chrono>
#include <thread>



class Game
{

private:
	
	//Доступні стани гри
	enum GameState { MENU, PLAYING, GAME_OVER };



	// - - - Вікно:
	//Головне вікно
	sf::RenderWindow* window;

	//Виклик івентів
	sf::Event ev;

	//Характеристики вікна
	sf::VideoMode videoMode;

	//Поточний стан гри
	GameState currentState;



	// - - - MENU:

	//Інструкції щодо початку гри
	sf::Text instructions;

	//Заголовок гри
	sf::Text title;



	// - - - Ноти, нотна полоса та чекер:

	//BPM:
	float BPM = 120.0f;
	float spawnInterval = 0.0f;
	sf::Clock noteSpawnClock;
	
	//Полоса для нот
	std::vector<sf::RectangleShape> noteLines;

	//Екземпляр нотної лінії
	sf::RectangleShape NoteLine;

	//Вектор зберігаючий ноти
	std::vector<Notes> notes;

	//Скільки пройшло від останнього спавну
	float spawnTimer;

	//Інтервал спавну нот
	float spawnTimerMax;

	//Лінія перевірки
	sf::RectangleShape checker;

	//Час для натискання чекера
	int checkerTimer;

	//Вектор для часу натискання клавіші нотних ліній
	std::vector<int> keyPressTimers;



	// - - - Інформаційна панель:
	 
	//Панель для відображення інформації
	sf::RectangleShape infoShape;

	//Рахунок гравця
	int score;

	//Поточна серія
	int currentStreak;
	
	//Найкраща серія
	int bestStreak;
	
	//Вивід рахунку
	sf::Text showScore;
	
	//Вивід поточної серії
	sf::Text showCurrentStreak;
	
	//Вивід найкращої серії
	sf::Text showBestStreak;
	


	// - - - Гравець:
	int health;
	
	sf::Text gameOverText;


	// - - - Hit - Miss система:
	
	//Годинник для відображення повідомлень
	sf::Clock hitTextClock;
	
	//Булева змінна потреби виклику повідомлення про попадання
	bool showHitTrueText = false;

	//Булева змінна потреби виклику повідомлення про промах
	bool showHitFalseText = false;

	//Змінна для тексту про попадання
	sf::Text hitTrueText;

	//Змінна для тексту про промах
	sf::Text hitFalseText;

	//Змінна для тривалості відображення повідомлення про попадання/промах
	float hitTextDuration;



	// - - - Інше:
	//Шрифт
	sf::Font font;

	//Музика
	sf::Music backgroundMusic;
	
	//Затримка
	sf::Clock delayMusicClock;
	
	//Затримка перед початком музики
	float delayTime;
	//Булева змінна чи музика грає
	bool isMusicPlaying = false;

	//Годинник
	sf::Clock clock;

	sf::Clock frameClock;

	// - - - Ініціалізація:
	
	//Ініціалізація початкових змінних
	void initVariables();
	//Ініціалізація нотної лінії
	void initNoteLine();
	//Ініціалізація вікна
	void initWindow();
	//Ініціалізація лінії перевірки
	void initChecker();
	//Ініціалізація меню
	void initMenu();
	//Ініціалізація програшу
	void initGameOver();
	//Ініціалізація музики
	void initMusic();
	//Спавн нот
	void spawnNotes();
	//Рестарт гри
	void resetGame();
	//Ініціалізація панелі з інформацією
	void initInfo();


	
public:

	//Конструктор
	Game();

	//Деструктор
	virtual ~Game();
	
	//Перевірка чи вікно відкрите:
	const bool running();
	
	//Валідація нот
	void validatedIntersect(int line, sf::Keyboard::Key);

	//Попадання
	void hitTrue();

	//Не попадання
	void hitFalse();

	//Натискання клавіш
	void pollEvents();
	
	//Оновлення полоси перевірки
	void updateChecker();

	//Оновлення нотної лінії
	void updateNoteLine();

	//Оновлення меню
	void updateMenu();

	//Оновлення панелі інформації
	void updateInfo();

	//Рендер полоси перевірки
	void renderChecker();

	//Рендер нотної лінії
	void renderNoteLine();

	//Рендер меню
	void renderMenu();

	//Рендер інформаційної панелі
	void renderInfo();

	//Рендер екрану програшу
	void renderGameOver();

	//Оновлення усього
	void update();

	//Рендер усього
	void render();
};

