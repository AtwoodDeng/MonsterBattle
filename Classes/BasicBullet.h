//
//  BasicBullet.h
//  Monster
//
//  Created by Atwood on 16-2-17.
//
//

#ifndef __Monster__BasicBullet__
#define __Monster__BasicBullet__

#include <stdio.h>
#include "Bullet.h"
#include "Monster.h"
#include "MonsterPart.h"
#include "Global.h"

class Bullet;
class Monster;
class MonsterPart;

class FireBullet: public Bullet
{
    float timer=0;
    float dmgValue;
public:
    virtual void init(Damage,Monster*,MonsterPart*,cocos2d::Layer*,std::string,float);
    virtual void update(float);
};

class LightningBullet: public Bullet
{
    bool ifInit=false;
public:
    virtual void init(Damage,Monster*,MonsterPart*,cocos2d::Layer*,std::string,float);
    virtual void update(float);
};

class WaveBullet: public Bullet
{
public:
    virtual void init(Damage,Monster*,MonsterPart*,cocos2d::Layer*,std::string,float);
};

class RockBullet: public Bullet
{
    float timer;
public:
    
    virtual void init(Damage,Monster*,MonsterPart*,cocos2d::Layer*,std::string,float);
};

class BulletFactory
{
public:
    static Bullet* createBullet(Monster*, MonsterPart* , BulletType b );
};

#endif /* defined(__Monster__BasicBullet__) */
