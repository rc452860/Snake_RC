#include "snakeUnit.h"
#include "GameLayer.h"

snakeUnit::snakeUnit(CCPoint bodyUnit,CCPoint dir)
{
	this->x = bodyUnit.x;
	this->y = bodyUnit.y;
	this->Dir = dir;
}


snakeUnit::~snakeUnit()
{

}


void snakeUnit::setDir(CCPoint* dir)
{
	this->Dir = CCPoint(dir->x,dir->y);
}
