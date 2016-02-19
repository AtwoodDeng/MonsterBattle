//
//  Monster.h
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#ifndef Monster_Monster_h
#define Monster_Monster_h

#include <vector>
#include "MonsterPart.h"
#include "Global.h"
#include "Bullet.h"

class MonsterPart;

struct MonsterInfo
{
public:
    float health=200;
    float blockChance=0;
    float reflectChance=0;
    float speed = 1;
};


class Monster
{
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* healthBar;
    cocos2d::Sprite* groupSign;
    cocos2d::PhysicsBody* body;
    
    float health;
    
    cocos2d::Vec2 pos;
    cocos2d::Vec2 vel;
    
    std::vector<MonsterPart*> parts;
    
    std::vector<Bullet*> bullets;
    
    float circleIntense;
    float innerIntense;
    
    MonsterState state;
    
    cocos2d::Sprite* arrow;
    
    
public:
    Monster();
    ~Monster();
    void m_init(cocos2d::Layer*,int);
    void m_update(float);
    
    cocos2d::Vec2 GetPosition();
    
    void hurtBy(Bullet *);
    void hurt(Damage);
    void push_back_bullet(Bullet*);
    void erase(Bullet*);
    
    void Do(cocos2d::Action*);
    cocos2d::Vec2 getRelatedPos(cocos2d::Vec2);
    float getRotation();
    
    cocos2d::Layer* layer;
    PhysicsCategory bodyCategory;
    PhysicsCategory bulletCategory;
    Monster* enermy;
    MonsterInfo info;
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::Color3B color;
    
    void ChangeIntense();
    void dead();
    void updateHealthBar();
    int getHeadOrder();
    
    bool addPart(MonsterPart* part);
    void dropPart();
    float getHealth(){return health;}
    
    virtual cocos2d::Sprite* getSprite(){return sprite;}
    
};

#endif
