#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Notes.h"




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
	
	//������ ��� ���
	std::vector<sf::RectangleShape> noteLines;

	//��������� ����� ��
	sf::RectangleShape NoteLine;

	//������ ���������� ����
	std::vector<Notes> notes;

	//�������� ������ ���
	sf::Clock spawnClock;

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
	/* Not yet*/
	


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
	sf::Clock clock;



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
	//����������� ������
	void initMusic();
	//����� ���
	void spawnNotes();
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
	void validatedIntersect(int line, int pressTime, sf::Keyboard::Key);

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

	//��������� ������
	void update();

	//������ ������
	void render();
};

