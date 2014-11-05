#include "snake.h"
#include "GameLayer.h"

Snake::Snake(int len)
{
	
	new (this)Snake(len,ccc3(0,128,0));
}
Snake::Snake(int len,ccColor3B color)
{
	Dir = ccp(0,1);//初始化方向为左
	body = new list<SnakeUnit*>();
	this->len = len;
	this->color = color;
	for (int i =0;i<len-1;i++)
	{
		SnakeUnit* snake = SnakeUnit::create(color);
		snake->setPosition(MARITX_X/2,i-1);
		body->push_back(snake);
	}
	head = SnakeUnit::create(color);
	head->setPosition(MARITX_X/2,len-1);
	body->push_back(head);
}
Snake::~Snake()
{

}
bool Snake::checkEatSelf()
{
	list<SnakeUnit*>::iterator begin = body->begin();
	while(begin!=body->end())
	{
		if (*begin != head)
		{
			if (head->x+Dir.x == (*begin)->x&&head->y+Dir.y == (*begin)->y)
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

bool Snake::EatFoot(SnakeUnit* unit)
{
	if (head->x+Dir.x == unit->x &&head->y+Dir.y == unit->y)
	{
		CCLog("eat one");
		unit->setColor(this->color);
		this->body->push_front(unit);
		return true;
	}
	return false;
}