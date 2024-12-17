#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Notes.h"




class Game
{

private:
	// - - - ³���:
	//������� ����
	sf::RenderWindow* window;

	//������ ������
	sf::Event ev;

	//�������������� ����
	sf::VideoMode videoMode;



	// - - - ��'���� �� ����:

	//������� ����� ���
	enum GameState { MENU, PLAYING, GAME_OVER };
	
	//�������� ���� ���
	GameState currentState;
	
	//��������� ���
	sf::Text title;
	
	//���������� ���� ������� ���
	sf::Text instructions;
	
	//�����
	sf::Font font;
	
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
	
	//������ ��� ���� ���������� ������ ������ ���
	std::vector<int> keyPressTimers; 

	//��� ��� ���������� ������
	int checkerTimer;

	//������
	sf::Music backgroundMusic;

	//��������
	sf::Clock clock;

	//������� ������
	int score;
	//������� ����
	int currentStreak;
	//�������� ����
	int bestStreak;

	//���� �������
	sf::RectangleShape infoShape;

	// �������
	/* Not yet*/

	//���� �������
	sf::Text showScore;
	//���� ������� ���
	sf::Text showCurrentStreak;
	//���� �������� ���
	sf::Text showBestStreak;


	sf::Text hitTrueText;
	sf::Text hitFalseText;



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

