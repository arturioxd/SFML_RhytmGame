#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Notes.h"




class Game
{

private:
	// - - - Вікно:
	//Головне вікно
	sf::RenderWindow* window;

	//Виклик івентів
	sf::Event ev;

	//Характеристики вікна
	sf::VideoMode videoMode;



	// - - - Об'єкти та змінні:

	//Доступні стани гри
	enum GameState { MENU, PLAYING, GAME_OVER };
	
	//Поточний стан гри
	GameState currentState;
	
	//Заголовок гри
	sf::Text title;
	
	//Інструкції щодо початку гри
	sf::Text instructions;
	
	//Шрифт
	sf::Font font;
	
	//Полоса для нот
	std::vector<sf::RectangleShape> noteLines;

	//Екземпляр нотної лінії
	sf::RectangleShape NoteLine;

	//Вектор зберігаючий ноти
	std::vector<Notes> notes;

	//Годиннки спавну нот
	sf::Clock spawnClock;

	//Скільки пройшло від останнього спавну
	float spawnTimer;
	
	//Інтервал спавну нот
	float spawnTimerMax;
	
	//Лінія перевірки
	sf::RectangleShape checker;
	
	//Вектор для часу натискання клавіші нотних ліній
	std::vector<int> keyPressTimers; 

	//Час для натискання чекера
	int checkerTimer;

	//Музика
	sf::Music backgroundMusic;

	//Годинник
	sf::Clock clock;

	//Рахунок гравця
	int score;
	//Поточна серія
	int currentStreak;
	//Найкраща серія
	int bestStreak;

	//Інфо квадрат
	sf::RectangleShape infoShape;

	// Гравець
	/* Not yet*/

	//Вивід рахунку
	sf::Text showScore;
	//Вивід поточної серії
	sf::Text showCurrentStreak;
	//Вивід найкращої серії
	sf::Text showBestStreak;


	sf::Text hitTrueText;
	sf::Text hitFalseText;



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

	//Ініціалізація музики
	void initMusic();

	//Спавн нот
	void spawnNotes();

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
	void validatedIntersect(int line, int pressTime, sf::Keyboard::Key);

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

	//Оновлення усього
	void update();

	//Рендер усього
	void render();
};

