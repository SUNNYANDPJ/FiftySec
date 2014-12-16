#include "End.h"

Scene *End::createScene(int grade)
{
	auto scene = Scene::create();
	auto lay = End::create(grade);
	scene->addChild(lay,0);
	return scene;
}
End*End::create(int grade)
{
	End *pRet = new End(); 
	pRet->grade = grade;
	if (pRet && pRet->init()) 
	{ 
	pRet->autorelease(); 
	return pRet; 
	} 
	else 
	{ 
	delete pRet; 
	pRet = NULL; 
	return NULL; 
	} 
}
bool End::init()
{
	Layer::init();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	
	//add bac
	addBac();
	addLabel();
	addGrade();
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

void End::addGrade()
{
	auto label_grade = LabelTTF::create(StringUtils::format("%d",grade),"verdana",30);
	label_grade->setPosition(Vec2(visibleSize.width / 2 +30+ label_grade->getContentSize().width / 2,visibleSize.height / 2));
	this->addChild(label_grade,2);//grade done

	auto label_msg = LabelTTF::create("Score:", "verdana", 30);
	label_msg->setPosition(Vec2(visibleSize.width / 2-label_msg->getContentSize().width / 2,visibleSize.height / 2));
	this->addChild(label_msg,2);
}