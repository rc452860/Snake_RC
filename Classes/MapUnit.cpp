#include "MapUnit.h"

MapUnit* MapUnit::create(int typeName)
{
	MapUnit *pobSprite = new MapUnit();
	CCString* tempName;
	switch (typeName)
	{
	case 1:
		tempName = CCString::create("floor/01.png");
		break;
	case 2:
		tempName = CCString::create("floor/02.png");
		break;
	case 3:
		tempName = CCString::create("floor/03.png");
		break;
	case 4:
		tempName = CCString::create("floor/04.png");
		break;
	case 5:
		tempName = CCString::create("floor/05.png");
		break;
	case 6:
		tempName = CCString::create("floor/06.png");
		break;
	case 7:
		tempName = CCString::create("floor/07.png");
		break;
	case 8:
		tempName = CCString::create("floor/08.png");
		break;
	default:
		tempName = CCString::create("floor/07.png");
		break;
	}
	if (pobSprite && pobSprite->initWithFile(tempName->getCString()))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}