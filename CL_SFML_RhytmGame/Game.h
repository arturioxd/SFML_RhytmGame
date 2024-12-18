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
	
	//������� ����� ���
	enum GameState { MENU, PLAYING, GAME_OVER };



	// - - - ³���:
	//������� ����
	sf::RenderWindow* window;

	//������ ������
	sf::Event ev;

	//�������������� ����
	sf::VideoMode videoMode;

	//�������� ���� ���
	GameState currentState;



	// - - - MENU:

	//���������� ���� ������� ���
	sf::Text instructions;

	//��������� ���
	sf::Text title;



	// - - - ����, ����� ������ �� �����:

	//BPM:
	float BPM = 120.0f;
	float spawnInterval = 0.0f;
	sf::Clock noteSpawnClock;
	
	//������ ��� ���
	std::vector<sf::RectangleShape> noteLines;

	//��������� ����� ��
	sf::RectangleShape NoteLine;

	//������ ���������� ����
	std::vector<Notes> notes;

	//������ ������� �� ���������� ������
	float spawnTimer;

	//�������� ������ ���
	float spawnTimerMax;

	//˳�� ��������
	sf::RectangleShape checker;

	//��� ��� ���������� ������
	int checkerTimer;

	//������ ��� ���� ���������� ������ ������ ���
	std::vector<int> keyPressTimers;



	// - - - ������������ ������:
	 
	//������ ��� ����������� ����������
	sf::RectangleShape infoShape;

	//������� ������
	int score;

	//������� ����
	int currentStreak;
	
	//�������� ����
	int bestStreak;
	
	//���� �������
	sf::Text showScore;
	
	//���� ������� ���
	sf::Text showCurrentStreak;
	
	//���� �������� ���
	sf::Text showBestStreak;
	


	// - - - �������:
	int health;
	
	sf::Text gameOverText;


	// - - - Hit - Miss �������:
	
	//�������� ��� ����������� ����������
	sf::Clock hitTextClock;
	
	//������ ����� ������� ������� ����������� ��� ���������
	bool showHitTrueText = false;

	//������ ����� ������� ������� ����������� ��� ������
	bool showHitFalseText = false;

	//����� ��� ������ ��� ���������
	sf::Text hitTrueText;

	//����� ��� ������ ��� ������
	sf::Text hitFalseText;

	//����� ��� ��������� ����������� ����������� ��� ���������/������
	float hitTextDuration;



	// - - - ����:
	//�����
	sf::Font font;

	//������
	sf::Music backgroundMusic;
	
	//��������
	sf::Clock delayMusicClock;
	
	//�������� ����� �������� ������
	float delayTime;
	//������ ����� �� ������ ���
	bool isMusicPlaying = false;

	//��������
	sf::Clock clock;

	sf::Clock frameClock;

	// - - - �����������:
	
	//����������� ���������� ������
	void initVariables();
	//����������� ����� ��
	void initNoteLine();
	//����������� ����
	void initWindow();
	//����������� �� ��������
	void initChecker();
	//����������� ����
	void initMenu();
	//����������� ��������
	void initGameOver();
	//����������� ������
	void initMusic();
	//����� ���
	void spawnNotes();
	//������� ���
	void resetGame();
	//����������� ����� � �����������
	void initInfo();


	
public:

	//�����������
	Game();

	//����������
	virtual ~Game();
	
	//�������� �� ���� �������:
	const bool running();
	
	//�������� ���
	void validatedIntersect(int line, sf::Keyboard::Key);

	//���������
	void hitTrue();

	//�� ���������
	void hitFalse();

	//���������� �����
	void pollEvents();
	
	//��������� ������ ��������
	void updateChecker();

	//��������� ����� ��
	void updateNoteLine();

	//��������� ����
	void updateMenu();

	//��������� ����� ����������
	void updateInfo();

	//������ ������ ��������
	void renderChecker();

	//������ ����� ��
	void renderNoteLine();

	//������ ����
	void renderMenu();

	//������ ������������ �����
	void renderInfo();

	//������ ������ ��������
	void renderGameOver();

	//��������� ������
	void update();

	//������ ������
	void render();
};

