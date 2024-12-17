#pragma once
#include <SFML/Graphics.hpp>
class Notes
{
private:
	// - - - Об'єкти та змінні:
	
	//ID лінії для нот
	int laneId;

	//Об'єкт ноти
	sf::RectangleShape singleNote;
	
	//Стан ноти
	bool isActive;
	


	// - - - Ініціалізація:
	
	//Ініціалізація ноти
	void initNote();
	
public:

	//Конструктор
	Notes(int lane);
	
	//Деструктор
	virtual ~Notes();
	
	//HIT
	bool wasHit = false;

	//Позначка для видалення
	void toDelete();
		
	//Перевірка на вихід за межі екрану
	bool isOffScreen() const;
	
	//Получити номер лінії
	int getLaneId() const;
	
	//Получити стан ноти
	bool getAct();
	
	//Получити ноту
	sf::RectangleShape getNote() const;
	
	//Встановити позицію ноти
	void setPosition(float x, float y);
	
	//Встановити колір нотм
	void setFillCol(const sf::Color& color);
	
	//Перевірка спавну ноти в ноті
	bool isTooClose(const Notes& other) const;
	
	//Перевірка на успішне попадання в такт
	bool checkerIntersect(sf::RectangleShape& checker) const;

	//Рендер ноти
	void renderNote(sf::RenderWindow& window);

	//Оновлення ноти
	void updateNote();
};


