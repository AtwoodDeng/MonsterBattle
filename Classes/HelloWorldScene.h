#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Monster.h"
#include <vector>

class HelloWorld : public cocos2d::Layer
{
    std::vector<Monster*> monsters;
    
    cocos2d::Sprite* arrowA;
    cocos2d::Sprite* arrowB;
    float shootA=-1;
    float shootB=-1;
    float rotateA = 1;
    float rotateB = -1;
    
    cocos2d::Sprite* point;
    float pointReady;
    
    bool playerAOn;
    bool playerBOn;
    
    bool ifStart = false;
    
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    std::vector<Bullet*> bullets;
    void movePoint();
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void update(float) override;
    bool onContactBegin(cocos2d::PhysicsContact &contact);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void dropPart(int player);
    void shoot(cocos2d::Vec2 initPos, float angle, float scale);
    
};

#endif // __HELLOWORLD_SCENE_H__
