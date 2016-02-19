//
//  Bullet.h
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#ifndef __Monster__Bullet__
#define __Monster__Bullet__

#include <stdio.h>
#include "Global.h"
#include "Monster.h"
#include "MonsterPart.h"

class Monster;
class MonsterPart;

class Bullet
{
protected:
    Damage dmg;
    cocos2d::Vec2 direction;
    cocos2d::Vec2 pos;
    Monster* parent;
    MonsterPart* part;
    cocos2d::Sprite* sprite;
    float speed;
    bool ifDead = false;
public:
    virtual void init(Damage,Monster*,MonsterPart*,cocos2d::Layer*,std::string,float);
    virtual void init(cocos2d::Layer* layer, std::string spriteName, Damage dmg, cocos2d::Vec2 initPos, cocos2d::Vec2 dir, float _speed , float scale) ;
    virtual void update(float);
    virtual void expode();
    virtual Monster* getSender();
    
    cocos2d::Vec2 getSpeed();
    Damage getDamgage();
};
#endif /* defined(__Monster__Bullet__) */
