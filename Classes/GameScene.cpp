#include "GameScene.h"

GameScene* GameScene::create(const Color4B& color,PhysicsWorld *_world)
{
		GameScene *pRet = new GameScene();
		pRet->world = _world;
		if (pRet && pRet->initWithColor(color))
		{
			pRet->setName("GameScene");		
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

Scene* GameScene::createScene(const Color4B& color)
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setSpeed(0.3);
	auto lay = GameScene::create(color,scene->getPhysicsWorld());
	scene->addChild(lay,0);//lay - 0
	return scene;
}

bool GameScene::initWithColor(const Color4B& color)
{
	LayerColor::initWithColor(color);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	addbackground();
	paramInit();//init the param
	
	addEdges();
	addControlBlock();
	addblocks();

	//scheduleUpdate();
	return true;
}

/*void GameScene::update(float dt)
{
	for (int i = 0; i < 4;i++)
	{
		;
	}
}*/

void GameScene::paramInit()
{	
	auto bac_pos = bac->getBoundingBox();
	touchEdge = false;
	touchcontrol = false;
	block_init_pos[0] = Vec2(bac_pos.getMinX()+offset, bac_pos.getMaxY()-offset);
	block_init_pos[1] = Vec2(bac_pos.getMaxX()-offset, bac_pos.getMaxY()-offset);
	block_init_pos[2] = Vec2(bac_pos.getMinX()+offset,bac_pos.getMinY()+offset);
	block_init_pos[3] = Vec2(bac_pos.getMaxX()-offset,bac_pos.getMinY()+offset);

	block_init_des[0] = Vect(320, -320);
	block_init_des[1] = Vect(-320,-320);
	block_init_des[2] = Vect(320,320);
	block_init_des[3] = Vect(-320,320);
}
void GameScene::addbackground()
{
	bac = Sprite::create(background);
	bac->setAnchorPoint(Vec2(0, 0));
	bac->setPosition(Vec2(origin.x + (visibleSize.height - bac->getContentSize().height) / 2, origin.y + (visibleSize.height - bac->getContentSize().height) / 2));
	this->addChild(bac, 1);
}

void GameScene::addEdges()
{
	edge = PhysicsBody::createEdgeBox(Size(visibleSize.height + 10, visibleSize.height), PhysicsMaterial(0.1f,1.0f,0.0f), 0.5f);
	auto node = Node::create();                                    //ÃÜ¶È0.1  »Ø¸´Á¦  Ä¦²Á0
	node->setPhysicsBody(edge);
	node->setPosition(Vec2(visibleSize.height/2,visibleSize.height/2));
	this->addChild(node);
}

void GameScene::addControlBlock()
{
	rocker = Sprite::create(squ);
	rocker->setPosition(Vec2(visibleSize.height/2,visibleSize.height/2));
	//rocker->setPhysicsBody(PhysicsBody::createBox(rocker->getContentSize(), PhysicsMaterial(0, 1.0f, 0.0f), Vec2(0.5f, 0.5f)));
	this->addChild(rocker, 2);//control - 2
	/*rocker->getPhysicsBody()->setCategoryBitmask(0x01);//0x01
	rocker->getPhysicsBody()->setContactTestBitmask(0x0f);//0x01 0x02 0x04 0x08
	rocker->getPhysicsBody()->setCollisionBitmask(0x10);//0x10*/
	//
	/*block[i]->getPhysicsBody()->setCategoryBitmask(0x01);
	block[i]->getPhysicsBody()->setContactTestBitmask(mess);
	mess <<= 1;//0xff
	block[i]->getPhysicsBody()->setCollisionBitmask(0x10);*/

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [this](Touch*t, Event *e){
			if (rocker->getBoundingBox().containsPoint(t->getLocation()))
			{
				touchcontrol = true;		
			}		
			return true;
	};
	listener->onTouchMoved = [this](Touch *t, Event *e){
		rocker->setPosition(t->getLocation());
			if (rocker->getBoundingBox().getMinX() <= bac->getBoundingBox().getMinX())
			{
				touchEdge = true;
			}
			else if (rocker->getBoundingBox().getMaxX() >= bac->getBoundingBox().getMaxX())
			{
				touchEdge = true;
			}
			else if (rocker->getBoundingBox().getMinY() <= bac->getBoundingBox().getMinY())
			{
				touchEdge = true;
			}
			else if (rocker->getBoundingBox().getMaxY() >= bac->getBoundingBox().getMaxY())
			{
				touchEdge = true;
			}
			if (touchEdge)
			{
				//log("game over");
				MessageBox("Game Over", "Game msg");
				//handle err code
				touchEdge = false;
			}
	};
	listener->onTouchEnded = [this](Touch*,Event*)
	{ touchcontrol = false; };
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, rocker);
}

void GameScene::addblocks()
{
	int mess = 0x01;
	for (int i = 0; i < 4; i++)
	{
		block[i] = Sprite::create(StringUtils::format("block\\block_%d.png",i+1).c_str());
		block[i]->setPhysicsBody(PhysicsBody::createBox(block[i]->getContentSize(), PhysicsMaterial(0.5f,1.0f,0.0f), Vec2(0.5f,0.5f)));
		this->addChild(block[i], 2);//block - 2
		block[i]->setPosition(block_init_pos[i]);
		block[i]->getPhysicsBody()->setVelocity(block_init_des[i]);
		//block[i]->setName(StringUtils::format("block%d", i));
		block[i]->getPhysicsBody()->setCategoryBitmask(0x01);
		block[i]->getPhysicsBody()->setContactTestBitmask(mess);
		mess<<=1;//0x01 0x02 0x04 0x08
		block[i]->getPhysicsBody()->setCollisionBitmask(0x10);
	
	}
	//this->world->setSpeed(1);
}