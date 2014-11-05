#ifndef __GAME_START_H__

#define __GAME_START_H__

#define GRID 20 //���Ӵ�С
#define WIDTH 480
#define HEIGHT 480
#define MARITX_X WIDTH/GRID
#define MARITX_Y HEIGHT/GRID

#include "cocos-ext.h"
#include "cocos2d.h"
#include "snake.h"
#include "GameMapLayer.h"
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;
class GameLayer:public CCLayerColor
{
public:
	GameLayer();
	~GameLayer();
public:
	bool init();
	CREATE_FUNC(GameLayer);
	void Move(float dt);
	void draw();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void GamePause(CCObject *sender);
	void GameRestart(CCObject *sender);
	void BackHome(CCObject *sender);
	void update(float dt);
	void MenuCallBack(CCObject *sender);
	//�������
	void keyArrowClicked(int arrow);  
	void keyEnterClicked();
	void AddFoot();
	//��ʼ����ͼ
	void initMapMaritx();
	void initSnake(int x,int y);
	//�ƶ���ͼ
	void MapMaritx();
public:
	CCSize m_Size;
	CCRect GameMatrix;
	int Maritx[MARITX_X][MARITX_Y];
	SnakeUnit* foot;
	bool isPause;
	bool isChangeDir;
	CCRect GameRect;
	Snake* snake;
	GameMapLayer* pGameMap;
	CCPoint prePoint;
	std::vector<vector<int>> m_MapMaritx;
	std::vector<vector<CCSprite*>> m_MapBlockUnit;
	list<CCPoint> DirList;
protected:
private:
};

#endif