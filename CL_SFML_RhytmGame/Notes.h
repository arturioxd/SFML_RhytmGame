#pragma once
#include <SFML/Graphics.hpp>
class Notes
{
private:
	// - - - ��'���� �� ����:
	
	//ID �� ��� ���
	int laneId;

	//��'��� ����
	sf::RectangleShape singleNote;
	
	//���� ����
	bool isActive;
	


	// - - - �����������:
	
	//����������� ����
	void initNote();
	
public:

	//�����������
	Notes(int lane);
	
	//����������
	virtual ~Notes();
	
	//HIT
	bool wasHit = false;

	//�������� ��� ���������
	void toDelete();
		
	//�������� �� ����� �� ��� ������
	bool isOffScreen() const;
	
	//�������� ����� ��
	int getLaneId() const;
	
	//�������� ���� ����
	bool getAct();
	
	//�������� ����
	sf::RectangleShape getNote() const;
	
	//���������� ������� ����
	void setPosition(float x, float y);
	
	//���������� ���� ����
	void setFillCol(const sf::Color& color);
	
	//�������� ������ ���� � ���
	bool isTooClose(const Notes& other) const;
	
	//�������� �� ������ ��������� � ����
	bool checkerIntersect(sf::RectangleShape& checker) const;

	//������ ����
	void renderNote(sf::RenderWindow& window);

	//��������� ����
	void updateNote();
};


