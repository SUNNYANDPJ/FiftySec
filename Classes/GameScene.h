#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "MyRes.h"
USING_NS_CC;

class GameScene:public LayerColor
{
public:
	//bool init();
	virtual bool initWithColor(const Color4B& color);
	//virtual void onEnter();
	static Scene *createScene(const Color4B& color);//scene

	//CREATE_FUNC(GameScene);
	static GameScene* create(const Color4B& color, PhysicsWorld *_world);//layer
	
	void paramInit();
	void addbackground();
	void addEdges();
	void addblocks();
	void addControlBlock();
	void setPhyWorld(PhysicsWorld *_world);
	//virtual void update(float dt);

private:
	static Scene *sce;
	Size visibleSize;
	Vec2 origin;
	Sprite *bac;
	PhysicsBody *edge;
	PhysicsWorld*world;

	Sprite *rocker;//control
	Sprite*block[4];
	Vec2 block_init_pos[4];
	Vect  block_init_des[4];

	bool touchEdge;
	bool touchcontrol;

	//EventListenerTouchOneByOne *listener_mainblock;
};

#endif