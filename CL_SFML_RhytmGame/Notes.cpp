#include "Notes.h"
#include "Game.h"



// - - - private:

void Notes::initNote()
{
	singleNote.setSize(sf::Vector2f(50.f, 50.f));
	singleNote.setFillColor(sf::Color::Green);
	singleNote.setOutlineColor(sf::Color::Black);
	singleNote.setOutlineThickness(1.f);
	float xPos = 200.f * this->laneId + 70.f;
	singleNote.setPosition(xPos, 0.f);
}



// - - - public:

Notes::Notes(int lane) : laneId(lane), isActive(true)
{
	this->initNote();
}

Notes::~Notes()
{
}

void Notes::toDelete()
{
	this->isActive = false;
}

void Notes::renderNote(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(this->singleNote);
	}
}

void Notes::updateNote()
{
	if (isActive)
	{
		this->singleNote.move(0.f, 0.1);
	}
}

bool Notes::isOffScreen() const
{
	return singleNote.getPosition().y > 550;
}

int Notes::getLaneId() const
{
	return laneId;
}

sf::RectangleShape Notes::getNote() const
{
	return singleNote;
}

void Notes::setPosition(float x, float y)
{
	singleNote.setPosition(x, y);
	
}

void Notes::setFillCol(const sf::Color& color)
{
	singleNote.setFillColor(color);
}

bool Notes::isTooClose(const Notes& other) const
{
	float yDis = std::abs(this->singleNote.getPosition().y - other.singleNote.getPosition().y);
	return yDis < 100.f;
}

bool Notes::checkerIntersect(sf::RectangleShape& checker) const
{
	return this->singleNote.getGlobalBounds().intersects(checker.getGlobalBounds());
}

bool Notes::getAct()
{
	return isActive;
}