//
//  BasicPart.h
//  Monster
//
//  Created by Atwood on 16-2-16.
//
//

#ifndef __Monster__BasicPart__
#define __Monster__BasicPart__

#include <stdio.h>

#include "MonsterPart.h"
#include "Monster.h"

class PreciseShootHead: public MonsterPart
{
public:
    virtual cocos2d::Vec2 getBulletDierection();
};

class HeartHead: public MonsterPart
{
public:
    virtual void shoot();
};

class HideHead: public MonsterPart
{
public:
    virtual void shoot();
};

class BlockHead: public MonsterPart
{
public:
    virtual void setPartent(Monster* monster);
    virtual void shoot();
    virtual void unlink();
};

class JumpHead : public MonsterPart
{
public:
    virtual void shoot();
    
};

class Wing: public MonsterPart
{
public:
    virtual void shoot();
};

class Leg: public MonsterPart
{
public:
    virtual void shoot();
};

class Body: public MonsterPart
{
public:
    virtual void init(Monster*,cocos2d::Layer*,cocos2d::Vec2,std::string,float,int,bool);
    virtual void update();
    virtual void shoot();
    virtual void adjustMonsterInfo(MonsterInfo);
};

class PartFactory
{
public:
    static MonsterPart* getRandomHead( Monster* parent, cocos2d::Layer* layer );
    static MonsterPart* getRandomHead( Monster* parent, cocos2d::Layer* layer , int ii = -1);
    static MonsterPart* getRandomBody(Monster* parent, cocos2d::Layer* layer);
    static MonsterPart* getRandomWing(Monster* parent, cocos2d::Layer* layer);
    static MonsterPart* getRandomLeg(Monster* parent, cocos2d::Layer* layer);
};

#endif /* defined(__Monster__BasicPart__) */
