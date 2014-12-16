#ifndef  __END_H__
#define __END_H__

#include "cocos2d.h"
#include "MyRes.h"
USING_NS_CC;

class End : public Layer
{
public:
	static Scene *createScene();
	virtual bool init();
	CREATE_FUNC(End);
	void addBac();
	void addLabel();
private:
	Size visibleSize;
	Vec2 origin;
	Sprite *bac;
	LabelTTF *label;
};
#endif