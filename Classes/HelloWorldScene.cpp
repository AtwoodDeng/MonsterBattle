#include "HelloWorldScene.h"
#include "Global.h"
#include "MonsterPart.h"
#include "BasicPart.h"
#include "Bullet.h"
#include "BasicBullet.h"
#include <math.h>
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    // init rand seed
    srand (time(NULL));
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    ////////////
    //change background
    ///////////
    
    auto background = DrawNode::create();
    background->drawSolidRect(origin, visibleSize, Color4F(0.6,0.6,0.6,1.0));
    this->addChild(background);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
//    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
//    
//    // position the label on the center of the screen
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//
//    
//    
//    // add the label as a child to this layer
//    this->addChild(label, 1);
//
//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite, 0);
//
    
    // init physics
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    // init update
    this->scheduleUpdate();
    
    // init monsters
    Monster* monsterA = new Monster();
    monsterA->m_init(this,0);
    monsters.push_back(monsterA);
    
    Monster* monsterB = new Monster();
    monsterB->m_init(this,1);
    monsters.push_back(monsterB);
    
    
    Monster* monsterC = new Monster();
    monsterC->m_init(this,2);
    monsters.push_back(monsterC);
    
    
    Monster* monsterD = new Monster();
    monsterD->m_init(this,3);
    monsters.push_back(monsterD);
    
    monsterA->enermy = monsterB;
    monsterB->enermy = monsterC;
    monsterC->enermy = monsterD;
    monsterD->enermy = monsterA;
    
    // system arrow
    arrowA = Sprite::create("arrow.png");
    arrowB = Sprite::create("arrow.png");
    arrowA->setPosition(Vec2(50,50));
    arrowB->setPosition(Vec2(visibleSize.width - 50,50));
    arrowA->setRotation(45);
    arrowB->setRotation(-45);
    arrowA->setColor(player2Color(0));
    arrowB->setColor(player2Color(1));
    this->addChild(arrowA);
    this->addChild(arrowB);
    arrowA->setScale(0.001, 0.001);
    arrowB->setScale(0.001, 0.001);
    
    point = Sprite::create("point.png");
    point->setPosition(visibleSize.width / 2 , visibleSize.height / 2);
    movePoint();
    
    this->addChild(point,55);
    
    
    
    playerAOn=playerBOn=false;
    
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("bgm.mp3");
    
    return true;
}

// Implementation of the keyboard event callback function prototype
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == PLAYER_A_SHOOT_KEY)
    {
        playerAOn = true;
        arrowA->setScale(2);
        shootA = 0;
    }
    
    if (keyCode == PLAYER_B_SHOOT_KEY)
    {
        playerBOn = true;
        arrowB->setScale(2);
        shootB = 0;
    }

}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    
    if (keyCode == PLAYER_A_SHOOT_KEY)
    {
        playerAOn = false;
        arrowA->setScale(0.001, 0.001);
        if (shootA > SHOOT_INTERVAL)
        shoot(arrowA->getPosition(), arrowA->getRotation(), shootA/SHOOT_INTERVAL);
        shootA = -1;
    }
    
    if (keyCode == PLAYER_B_SHOOT_KEY)
    {
        playerBOn = false;
        arrowB->setScale(0.001, 0.001);
        if (shootB > SHOOT_INTERVAL)
            shoot(arrowB->getPosition(), arrowB->getRotation(), shootB/SHOOT_INTERVAL);
        shootB = -1;
    }
    
    if (pointReady > POINT_READY_TIME)
    {
    if (keyCode == PLAYER_A_KEY)
    {
        dropPart(0);
        pointReady=0;
    }
    if (keyCode == PLAYER_B_KEY)
    {
        dropPart(1);
        pointReady=0;
    }
    
    if (keyCode == PLAYER_C_KEY)
    {
        dropPart(2);
        pointReady=0;
    }
    
    if (keyCode == PLAYER_D_KEY)
    {
        dropPart(3);
        pointReady=0;
    }
    }
    
    if (keyCode == START_KEY)
    {
        ifStart = true;
    }
}

bool HelloWorld::onContactBegin(cocos2d::PhysicsContact &contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA == NULL || nodeB == NULL)
        return true;
    
    UserData* dataA = ( UserData* )nodeA->getUserData();
    UserData* dataB = ( UserData* )nodeB->getUserData();

    
    if (dataA->monster != NULL && dataB->bullet != NULL)
    {
        dataA->monster->hurtBy(dataB->bullet);
    }
    
    if (dataB->monster != NULL && dataA->bullet != NULL)
    {
        dataB->monster->hurtBy(dataA->bullet);
    }
    
    if (dataA->monster != NULL && dataB->part != NULL)
    {
        if (dataB->part->isLinkable())
        {
            dataA->monster->addPart(dataB->part);
        }
    }
    
    if (dataB->monster != NULL && dataA->part != NULL)
    {
        if (dataA->part->isLinkable())
        {
            dataB->monster->addPart(dataA->part);
        }
    }

    return true;
}

void HelloWorld::dropPart(int player)
{
    MonsterPart* part = PartFactory::getRandomHead(NULL, this, rand() % 8);
    part->getSprite()->setPosition(point->getPosition());
    part->getSprite()->setColor(player2Color(player));
    part->getSprite()->setScale(0.3);
    auto appear = ScaleTo::create(0.5, 0.5);
    auto ease_in = EaseBackOut::create(appear->clone());
    part->getSprite()->runAction(ease_in);
    
    part->unlink();
}

void HelloWorld::movePoint()
{
    Vec2 to = Vec2(random(SPACE_BOUNDARY , visibleSize.width - SPACE_BOUNDARY) , random(SPACE_BOUNDARY, visibleSize.height - SPACE_BOUNDARY));
    auto moveTo = MoveTo::create(randFloat(0.3,1), to);
    auto final = CallFunc::create(CC_CALLBACK_0(HelloWorld::movePoint,this));
    auto sequence =Sequence::create(moveTo, final, NULL);
    point->runAction(sequence);
}

void HelloWorld::update(float delta)
{
    if (ifStart)
    {
        for (int i = 0 ; i < monsters.size(); i++) {
            monsters[i]->m_update(delta);
        }
        for (int i = 0 ; i < bullets.size(); i++) {
            bullets[i]->update(delta);
        }
    }

    if (ifStart)
    {
        pointReady += delta;
        if (pointReady > POINT_READY_TIME)
        {
            pointReady = 0;
            dropPart(rand() % 4);
        }
    }
    
    point->setScale((pointReady > POINT_READY_TIME)? 1:pointReady/POINT_READY_TIME);
    
    if (playerAOn)
    {
//        if(rand_0_1() < 0.2)
        {
            float angle = arrowA->getRotation();
            if (angle > 45 + ARROW_TURN_RANGE)
                rotateA = -1;
            if (angle < 45 - ARROW_TURN_RANGE)
                rotateA = 1;
            
            angle += rotateA * ARROW_TRUN_SPEED / 5;
                
//            angle += random(-ARROW_TRUN_SPEED, ARROW_TRUN_SPEED);
//            angle = (angle > 45 + ARROW_TURN_RANGE)? 45 + ARROW_TURN_RANGE:angle;
//            angle = ( angle < 45 - ARROW_TURN_RANGE)? 45 - ARROW_TURN_RANGE:angle;
//            float scale = arrowA->getScale();
//            scale *= random( 1/ ARROW_SCALE_SPEED, ARROW_SCALE_SPEED);
//            scale = (scale > 1 ) ? 1 : scale;
            
            arrowA->setRotation(angle);
//            arrowA->runAction(RotateTo::create(0.2, angle ));
//            arrowA->runAction(ScaleTo::create(0.2, scale ));
        }
        arrowA->setScale(shootA/SHOOT_INTERVAL);
        shootA += delta;
        if (shootA > SHOOT_INTERVAL * 3)
            shootA = SHOOT_INTERVAL * 3;
    }
    
    if (playerBOn)
    {
//        if(rand_0_1() < 0.2)
        {
            float angle = arrowB->getRotation();
            
            if (angle > - 45 + ARROW_TURN_RANGE)
                rotateB = -1;
            if (angle < - 45 - ARROW_TURN_RANGE)
                rotateB = 1;
            
            angle += rotateB * ARROW_TRUN_SPEED / 5;
            
//            angle += random(-ARROW_TRUN_SPEED, ARROW_TRUN_SPEED);
//            angle = (angle < -45 + ARROW_TURN_RANGE)? angle:-45 + ARROW_TURN_RANGE;
//            angle = ( angle > -45 - ARROW_TURN_RANGE)? angle:-45 - ARROW_TURN_RANGE;
//            float scale = arrowA->getScale();
//            scale *= random( 1/ ARROW_SCALE_SPEED, ARROW_SCALE_SPEED);
//            scale = (scale > 1 ) ? 1 : scale;
            arrowB->setRotation(angle);
//            arrowB->runAction(RotateTo::create(0.2, angle ));
//            arrowB->runAction(ScaleTo::create(0.2, scale ));
        }
        arrowB->setScale(shootB/SHOOT_INTERVAL);
        shootB += delta;
        if (shootB > SHOOT_INTERVAL * 3)
            shootB = SHOOT_INTERVAL * 3;
    }
    
}

void HelloWorld::shoot(cocos2d::Vec2 initPos, float angle, float scale)
{
    if (!ifStart)
        return;
    RockBullet* rockBullet = new RockBullet();
    Damage dmg;
    dmg.value = scale * 6;
    dmg.type = DamgeType::RockD;
    Vec2 dir = Vec2(sin(angle*3.14159/180),cos(angle*3.14159/180));
    rockBullet->Bullet::init(this, "bullet-rock.png", dmg, initPos, dir, 6, scale / 2 );
    
    bullets.push_back(rockBullet);
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("throw.mp3");
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
