/*
0.空白地方
1.可走的地方
2.食物
3.积分片
4.障碍物
5.加速点
6.减速点
7.蛇身

*/

#ifndef __GAMEMAPLAYER_H__
#define __GAMEMAPLAYER_H__


#define GRID 20 //格子大小
#define WIDTH 640
#define HEIGHT 960
#define MARITX_X WIDTH/GRID
#define MARITX_Y HEIGHT/GRID

#include "cocos-ext.h"
#include "cocos2d.h"
#include "snake.h"

USING_NS_CC;
USING_NS_CC_EXT;
class GameMapLayer:public CCLayer
{
//Constructor
public:
	GameMapLayer();
	~GameMapLayer();
	//Method
public:
	CREATE_FUNC(GameMapLayer);
	bool init();
	void initMap();
	void MapMoveDown(float dt);

	//Field
public:
	CCSprite *pGameLayer;
	int Maritx[MARITX_X][MARITX_Y];
	//+2 The screen buffer 
	CCSprite* m_BlokcUnit[MARITX_X+2][MARITX_Y+2];
	Snake* m_Snake;
private:
	
};

#endif