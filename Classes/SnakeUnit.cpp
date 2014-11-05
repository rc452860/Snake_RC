#include "SnakeUnit.h"
#include "GameLayer.h"
#include "VisibleRect.h"

SnakeUnit::SnakeUnit()
{

}

SnakeUnit::~SnakeUnit()
{

}
bool SnakeUnit::init()
{
	return this->init(ccc3(0,0,0));
}
bool SnakeUnit::init(ccColor3B color)
{
	if (!CCSprite::init())
	{
		return false;
	}
	this->setTextureRect(CCRect(0,0,GRID,GRID));
	this->setColor(color);
	return true;
}

SnakeUnit* SnakeUnit::create(ccColor3B color)
{
	SnakeUnit *snake = new SnakeUnit();
	if (snake && snake->init(color))
	{
		snake->autorelease();
		return snake;
	}
	CC_SAFE_DELETE(snake);
	return NULL;
}



void SnakeUnit::setPosition(int x,int y)
{
	/*this->x=x;
	this->y=y;
	checkOverflow(x,y);
	CCPoint point = ccp(VisibleRect::center().x-(WIDTH/2)+((x+1)*GRID)-GRID/2,VisibleRect::center().y-(HEIGHT/2)+((y+1)*GRID)-GRID/2);
	CCSprite::runAction(CCMoveTo::create(0.18f,point));*/
	this->x=x;
	this->y=y;
	checkOverflow(x,y);
	CCPoint point = ccp(VisibleRect::center().x-(WIDTH/2)+((x+1)*GRID)-GRID/2,VisibleRect::center().y-(HEIGHT/2)+((y+1)*GRID)-GRID/2);
	CCSprite::setPosition(point);

}

bool SnakeUnit::checkOverflow(int x,int y)
{
	if (x<0 || x>MARITX_X-1 || y<0 ||y>MARITX_Y-1)
	{
		CCLog("Warning: SnakeUnit Overflow,X:%d ,Y:%d",x,y);
		return true;
	}
	return false;
}
bool SnakeUnit::checkOverflow()
{
	return checkOverflow(this->x,this->y);

}