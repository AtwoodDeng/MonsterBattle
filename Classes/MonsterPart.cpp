
//
//  Part.cpp
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#include "MonsterPart.h"
#include "Global.h"
#include "BasicBullet.h"

USING_NS_CC;


void MonsterPart::init(Monster * _parent, cocos2d::Layer * layer, cocos2d::Vec2 _pos , std::string spriteName, float _sInterval , int zLayer , bool ifPhysics , BulletType _bulletType)
{
    // init parameter
    if (_parent != NULL)
    {
        setPartent(_parent);
    }else
        parent = NULL;
    shootInterval = _sInterval;
    this->bulletType = _bulletType;
    
    // set up the sprite
    pos = _pos;
    sprite = Sprite::create(spriteName);
    sprite->setScale(0.5);
    if (parent != NULL)
    {
        sprite->setPosition(parent->getRelatedPos(pos));
        sprite->setColor(parent->color);
    }
    layer->addChild(sprite, zLayer);
    
//    if (ifPhysics)
    {
        //  1
        auto monsterSize = sprite->getContentSize();
        PhysicsBody* body = PhysicsBody::createBox(Size(monsterSize.width , monsterSize.height),PhysicsMaterial(0.1f, 1.0f, 0.0f));
        // 2
        body->setDynamic(true);
        // 3
        body->setCategoryBitmask(PhysicsCategory::Part);
        body->setCollisionBitmask((int)PhysicsCategory::None);
        body->setContactTestBitmask((int)PhysicsCategory::MonsterA);
        
        UserData* data = new UserData();
        data->part = this;
        sprite->setUserData((void*)data);
        sprite->setPhysicsBody(body);
    }

}

void MonsterPart::update(float delta)
{
    if (parent == NULL) // unlink from parent
        return;
    
    timer += delta;
    sprite->setPosition(parent->getRelatedPos(pos));
    sprite->setRotation(parent->getRotation());
    if (timer > shootInterval)
    {
        timer = 0 ;
        shoot();
    }
}

void MonsterPart::unlink()
{
    parent = NULL;
}

void MonsterPart::shoot()
{
    Damage dmg;
    dmg.type = DamgeType::FireD;
    dmg.value = 20;
    
    Bullet* bullet = BulletFactory::createBullet( parent , this , bulletType);
    
    Color3B col = sprite->getColor();
    sprite->runAction(Sequence::create(TintTo::create(0.23, Color3B::WHITE) , TintTo::create(0.23,col), NULL));

//    parent->push_back_bullet(bullet);
//    bullet->init(dmg, parent, pos+parent->GetPosition(), parent->layer, speed );
    
}

Vec2 MonsterPart::getBulletDierection()
{
    
    Vec2 toEnermy = parent->enermy->GetPosition() - parent->GetPosition();
    toEnermy.normalize();
    Vec2 dir = toEnermy * 2 + randVec2();
    dir.normalize();
    
    return dir;
}

void MonsterPart::setPartent(Monster *monster)
{
    parent = monster;
    int order = parent->getHeadOrder();
    if (order >= TOTAL_PARTS )
        return;
    pos = HEAD_POS[order];
}

bool MonsterPart::isLinkable()
{
    return parent == NULL;
}