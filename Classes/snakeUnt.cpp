#include "snakeUnit.h"
#include "GameLayer.h"

snakeUnit::snakeUnit()
{

}


snakeUnit::~snakeUnit()
{

}


void snakeUnit::setDir(CCPoint* dir)
{
	this->Dir = CCPoint(dir->x,dir->y);
}