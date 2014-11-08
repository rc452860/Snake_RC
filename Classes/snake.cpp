#include "snake.h"
#include "GameLayer.h"

Snake::Snake()
{
	this->body = new list<CCPoint*>();
	this->head = new CCPoint();
}
Snake::~Snake()
{

}
bool Snake::checkEatSelf()
{
	list<CCPoint*>::iterator begin = body->begin();
	while(begin!=body->end())
	{
		if (*begin != head)
		{
			if (head->x == (*begin)->x&&head->y+Dir.y == (*begin)->y)
			{
				CCLog("EatSelf");
				return true;
			}
		}
		else
		{
			begin++;
			continue;
		}
		begin++;
		
	}
	return false;
}

bool Snake::EatFoot(CCPoint* position)
{
	if (head->x+Dir.x == position->x &&head->y+Dir.y == position->y)
	{
		CCLog("eat one");
		return true;
	}
	return false;
}


bool Snake::isInstanceOf(int x,int y)
{
	list<CCPoint*>::iterator begin = body->begin();
	while(begin != body->end())
	{
		CCPoint *pTemp = *begin;
		if (pTemp->x == x&&pTemp->y == y)
		{
			return true;
		}
		begin++;
	}
	return false;
}