#include "End.h"

Scene *End::createScene()
{
	auto scene = Scene::create();
	auto lay = End::create();
	scene->addChild(lay,0);
	return scene;
}

bool End::init()
{
	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	
	//add bac
	addBac();
	addLabel();
	return true;
}

void End::addBac()
{
	bac = Sprite::create(bac_end);
	bac->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bac,1);
}

void End::addLabel()
{
	label = LabelTTF::create("Game Over","verdana",30);
	label->setPosition(Vec2(visibleSize.width / 2,visibleSize.height *3/4 ));
	this->addChild(label,2);
}