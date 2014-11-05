/*
0.�հ׵ط�
1.���ߵĵط�
2.ʳ��
3.����Ƭ
4.�ϰ���
5.���ٵ�
6.���ٵ�
7.����

*/

#ifndef __GAMEMAPLAYER_H__
#define __GAMEMAPLAYER_H__


#define GRID 20 //���Ӵ�С
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