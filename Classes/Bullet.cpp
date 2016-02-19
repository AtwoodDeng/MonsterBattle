//
//  Bullet.cpp
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#include "Bullet.h"
#include "Global.h"

USING_NS_CC;

    
void Bullet::init(Damage _d, Monster * _p, MonsterPart* _part, cocos2d::Layer *layer, std::string spriteName, float _speed)
{
    dmg = _d;
    parent = _p;
    part = _part;
    direction = part->getBulletDierection();
    direction.normalize();
    speed = _speed;
    
    pos = part->getSprite()->getPosition();
    sprite = Sprite::create(spriteName);
    sprite->setPosition(pos);
    sprite->runAction(FadeIn::create(0.3));
    
    layer->addChild(sprite, 40);
    
    // set up the physics
    // 1
    auto monsterSize = sprite->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width , monsterSize.height),
                                              PhysicsMaterial(0.1f, 1.0f, 0.0f));
    // 2
    physicsBody->setDynamic(true);
    
    // 3
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::MonsterA);
    
    UserData* data = new UserData();
    data->bullet = this;
    sprite->setUserData((void*)data);
    sprite->setPhysicsBody(physicsBody);
    
    parent->push_back_bullet(this);
}

void Bullet::init(cocos2d::Layer* layer, std::string spriteName, Damage _d, cocos2d::Vec2 initPos, cocos2d::Vec2 dir, float _speed , float _scale)
{
    dmg = _d;
    direction = dir;
    direction.normalize();
    speed = _speed;
    
    pos = initPos;
    sprite = Sprite::create(spriteName);
    sprite->setPosition(pos);
    sprite->runAction(FadeIn::create(0.3));
    sprite->setScale(_scale);
    
    layer->addChild(sprite, 40);
    
    // set up the physics
    // 1
    auto monsterSize = sprite->getContentSize();
    auto physicsBody = PhysicsBody::createBox(Size(monsterSize.width , monsterSize.height),
                                              PhysicsMaterial(0.1f, 1.0f, 0.0f));
    // 2
    physicsBody->setDynamic(true);
    
    // 3
    physicsBody->setCategoryBitmask((int)PhysicsCategory::Projectile);
    physicsBody->setCollisionBitmask((int)PhysicsCategory::None);
    physicsBody->setContactTestBitmask((int)PhysicsCategory::MonsterA);
    
    UserData* data = new UserData();
    data->bullet = this;
    sprite->setUserData((void*)data);
    sprite->setPhysicsBody(physicsBody);
}

void Bullet::expode()
{
    if (ifDead)
        return;
    if (parent != NULL)
        parent->erase(this);
    if (sprite != NULL)
        sprite->removeFromParent();
    ifDead = true;
}

void Bullet::update(float delta)
{
    
    if (ifDead)
        return;
    
    pos += direction * speed;
    sprite->setPosition(pos);
    
    if (parent != NULL)
    if (pos.x > parent->visibleSize.width + SPACE_BOUNDARY
        || pos.x < 0 - SPACE_BOUNDARY
        || pos.y > parent->visibleSize.height + SPACE_BOUNDARY
        || pos.y < 0 - SPACE_BOUNDARY)
        expode();
        
}

Vec2 Bullet::getSpeed()
{
    return direction * speed;
}

Monster* Bullet::getSender()
{
    return parent;
    
}

Damage Bullet::getDamgage()
{
    return dmg;
}