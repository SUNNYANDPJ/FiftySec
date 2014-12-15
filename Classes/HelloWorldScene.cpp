#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	//layer->setColor(Color3B(255,0,0));
    // add layer as a child to scene
    scene->addChild(layer,0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	addBackground();
    return true;
}

void HelloWorld::addBackground()
{
	bac = Sprite::create(background);
	bac->setPosition(Vec2(visibleSize.width / 2,visibleSize.height / 2));
	this->addChild(bac,2);
}

void HelloWorld::onEnter()
{
	HelloWorld::init();
}
