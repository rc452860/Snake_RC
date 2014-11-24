#include "snake.h"
#include "GameLayer.h"

Snake::Snake()
{
	this->body = new list<CCPoint*>();
	this->head = new CCPoint();
	cornerNum = 0;
	corner = new queue<snakeUnit*>();
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
			if (head->x == (*begin)->x&&head->y+(getDir()->y) == (*begin)->y)
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
	if (head->x+(getDir()->x) == position->x &&head->y+(getDir()->y) == position->y)
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

void Snake::shiftSnake(bool ischangeDir)
{
	list<CCPoint*>::reverse_iterator end = body->rbegin();
	while (end!=body->rend())
	{
		CCPoint* temp = *end;
		list<CCPoint*>::reverse_iterator swap = end;
		
		if (++swap != body->rend())
		{
			CCPoint* pSwapPoint= *swap;
			temp->x =pSwapPoint->x,temp->y = pSwapPoint->y;
		}
		else
		{
			
			GameLayer* pParent = (GameLayer*)this->parent;
			int mapSize = pParent->m_MapMaritx.size();
			head->x+=getDir()->x;
			head->y+=getDir()->y;
			if (head->x == mapSize)
				head->x = 0;
			else if(head->x < 0)
				head->x = mapSize-1;
			else if(head->y ==mapSize)
				head->y = 0;
			else if(head->y < 0)
				head->y = mapSize-1;
		}
		end++;
	}
}

CCPoint* Snake::getDir()
{
	CCPoint* pDir = *Dir;
	return pDir;
}

CCNode* Snake::getParent()
{
	return this->parent;
}
void Snake::setParent(CCNode* parent)
{
	this->parent = parent;
}