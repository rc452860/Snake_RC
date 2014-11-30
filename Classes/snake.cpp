#include "snake.h"
#include "GameLayer.h"
Snake::Snake()
{
	body = new list<snakeUnit*>();
	corner = new list<cornerUnit*>();
}

Snake::~Snake(){}

void Snake::init(CCPoint start,CCPoint dir)
{
	//头结点
	snakeUnit* head = new snakeUnit(start,dir);
	this->body->push_back(head);
	
	for (int i = 1;i<=3;i++)
	{
		this->body->push_back(new snakeUnit(ccp(head->x-(dir.x*i),head->y-(dir.y*i)),dir));
	}
}
void Snake::setParent(CCNode* pt)
{
	this->parent = pt;
}
CCPoint Snake::getDir()
{
	return this->getHead()->Dir;
}
snakeUnit* Snake::getHead()
{
	return body->front();
}
snakeUnit* Snake::getTail()
{
	return body->back();
}
void Snake::setDir(int x,int y)
{
	this->getHead()->Dir = ccp(x,y);
}


void Snake::shiftSnake()
{
	GameLayer* father = (GameLayer*)parent;
	snakeUnit* head = this->getHead();
	for (list<snakeUnit*>::const_reverse_iterator begin = body->rbegin();begin!= body->rend();begin++)
	{
		snakeUnit* item = *begin;
		item->x+=item->Dir.x;
		item->y+=item->Dir.y;
		reviseOverflow(item);
		if ((head->x+head->Dir.x) == item->x && (head->y+head->Dir.y)== item->y)
		{
			CCLog("溢出");
		}
		/*int mapSize = father->m_MapMaritx.size();
		if (item->x == mapSize)
			item->x = 0;
		else if(item->x < 0)
			item->x = mapSize-1;
		else if(item->y ==mapSize)
			item->y = 0;
		else if(item->y < 0)
			item->y = mapSize-1; */
		list<snakeUnit*>::const_reverse_iterator sawp = begin;
		
		if (++sawp != body->rend())
		{	
			snakeUnit* itemw = *sawp;
			item->Dir.x = itemw->Dir.x;
			item->Dir.y = itemw->Dir.y;
		}
	}
}

void  Snake::reviseOverflow(snakeUnit* item)
{
	GameLayer* father = (GameLayer*)parent;
	int mapSize = father->m_MapMaritx.size();
	if (item->x == mapSize)
		item->x = 0;
	else if(item->x < 0)
		item->x = mapSize-1;
	else if(item->y ==mapSize)
		item->y = 0;
	else if(item->y < 0)
		item->y = mapSize-1;
}
void Snake::pushCorner(bool isCorner)
{
	if (!isCorner)
		return; 
	list<snakeUnit*>::iterator head = body->begin();
	snakeUnit* currDir = *head;
	snakeUnit* beforeDir = *++head;
	cornerUnit* cornerItem = new cornerUnit(ccp(this->getHead()->x,this->getHead()->y),currDir->Dir,beforeDir->Dir);
	corner->push_back(cornerItem);
}

void Snake::clearCorner()
{
	if (!corner->empty())
	{
		
		for (list<cornerUnit*>::iterator cbeign = corner->begin();cbeign!=corner->end();)
		{
			bool isNotinside = true;
			cornerUnit* cornerTemp = *cbeign;
			for (list<snakeUnit*>::iterator sbeign = body->begin();sbeign!=body->end();sbeign++)
			{
				snakeUnit* item = *sbeign;
				//判断该节点是否在转弯节点内,如果蛇身所有节点都不在转弯节点内则清除改节点
				if (item->x == cornerTemp->position.x&&item->y == cornerTemp->position.y)
				{
					isNotinside = false;
					break;
				}

			}
			if (isNotinside)
				corner->erase(cbeign++);
			else
				cbeign++;
		}
	}

}

cornerUnit* Snake::isCorner(snakeUnit* body)
{
	int x = body->x,y = body->y;
	for (list<cornerUnit*>::iterator begin = corner->begin();begin!= corner->end();begin++)
	{
		cornerUnit* temp = *begin;
		if (temp->position.x == x &&temp->position.y == y)
		{
			return temp;
		}
	}
	return NULL;
}

