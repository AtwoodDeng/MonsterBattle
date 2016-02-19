//
//  Part.h
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#ifndef __Monster__Part__
#define __Monster__Part__

#include <stdio.h>
#include "Monster.h"
#include "Bullet.h"
#include "Global.h"
#include <vector>

class Monster;
class Bullet;

class MonsterPart {
protected:
    Monster* parent;
    cocos2d::Vec2 pos;
    cocos2d::Sprite* sprite;
    float timer;
    float shootInterval;
    BulletType bulletType;
public:
    virtual void init(Monster*,cocos2d::Layer*,cocos2d::Vec2,std::string,float,int,bool,BulletType);
    virtual void update(float);
    virtual void shoot();
    virtual cocos2d::Sprite* getSprite(){return sprite;}
    virtual cocos2d::Vec2 getBulletDierection();
    bool isLinkable();
    virtual void setPartent(Monster* monster);
    virtual void setLocalPos(cocos2d::Vec2 p){pos = p;}
    virtual void unlink();
};


#endif /* defined(__Monster__Part__) */
