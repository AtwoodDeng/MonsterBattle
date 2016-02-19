//
//  BasicPart.cpp
//  Monster
//
//  Created by Atwood on 16-2-16.
//
//

#include "BasicPart.h"
#include "MonsterPart.h"
#include "BasicBullet.h"

Vec2 PreciseShootHead::getBulletDierection()
{
    Vec2 toEnermy = parent->enermy->GetPosition() - parent->GetPosition();
    toEnermy.normalize();
    Vec2 speed = toEnermy ;
    speed.normalize();
    
    return speed;
}

void Body::update()
{
    // do nothing
}

void Body::shoot()
{
    // do nothing
}

void Leg::shoot()
{
    // normal leg do nothing
}

void HeartHead::shoot()
{
    // do nothing
    Damage dmg;
    if (parent->info.health > parent->getHealth())
        dmg.value = 0 ;
    else
        dmg.value = - (parent->info.health - parent->getHealth()) * randFloat(0.2, 0.25);
    dmg.type = DamgeType::FireD;
    parent->hurt(dmg);
    
    float scale = sprite->getScale();
    sprite->runAction(Sequence::create(ScaleTo::create(0.3, scale*1.5) , ScaleTo::create(0.3, scale), NULL));
    
}

void HideHead::shoot()
{
    
    float scale = sprite->getScale();
    sprite->runAction(Sequence::create(ScaleTo::create(0.3, scale*1.5) , ScaleTo::create(0.3, scale), NULL));
    float parScale = 0.5;
    parent->getSprite()->runAction(Sequence::create(ScaleTo::create(0.2, parScale * 0.05), DelayTime::create(1), ScaleTo::create(0.2, parScale), NULL));
}

void JumpHead::shoot()
{
    float scale = sprite->getScale();
    Color3B col = sprite->getColor();
    sprite->runAction(Sequence::create(TintTo::create(0.23, Color3B::WHITE) , TintTo::create(0.23,col), NULL));
    parent->getSprite()->runAction(MoveBy::create(0.3, randVec2()*550));
}

void BlockHead::setPartent(Monster *monster)
{
    if (monster == NULL)
        return;
    MonsterPart::setPartent(monster);
    parent->info.blockChance = 0.3;
}

void BlockHead::unlink()
{
    if (parent != NULL)
        parent->info.blockChance = 0;
    MonsterPart::unlink();
}

void BlockHead::shoot()
{
    // do nothing
}

void Wing::shoot()
{
    auto bigger = ScaleTo::create(0.3, 1.3);
    auto remain = ScaleTo::create(0.3, 1);
    auto delay = DelayTime::create(0.1);
    auto seq = Sequence::create(bigger,delay,remain, NULL);
    sprite->runAction(seq);
}

void Body::init(Monster * _parent, cocos2d::Layer * layer, cocos2d::Vec2 _pos , std::string spriteName, float _sInterval , int zLayer , bool ifPhysics )
{
    // init parameter
    parent = _parent;
    shootInterval = _sInterval;
    
    // set up the sprite
    pos = _pos;
    sprite = Sprite::create(spriteName);
    sprite->setScale(0.6);
    sprite->setColor(_parent->color);
    layer->addChild(sprite, zLayer);
}

void Body::adjustMonsterInfo(MonsterInfo _info )
{
    parent->info = _info;
}

MonsterPart* PartFactory::getRandomHead(Monster* parent, cocos2d::Layer* layer )
{
    return getRandomHead(parent, layer, rand() % 7);
}

MonsterPart* PartFactory::getRandomHead(Monster* parent, cocos2d::Layer* layer , int ii )
{
//    int i = rand() % 7;
//    int i = 3;
    
    int i = 0;
    if (ii < 0)
        i = rand() % 8;
    else
        i = ii;
    
    int order = 0;
    if (parent != NULL)
    {
        order = parent->getHeadOrder();
        if (order >= TOTAL_PARTS)
            return NULL;
    }
    
    if (i == 0)
    {
        MonsterPart* res = new PreciseShootHead();
        res->init(parent,layer,HEAD_POS[order],"head-fire.png",4+rand_0_1()*0.4,Z_LAYER_HEAD,true,BulletType::FireB);
        return res;
    }else if (i == 1)
    {
        MonsterPart* res = new PreciseShootHead();
        res->init(parent,layer,HEAD_POS[order],"head-lightening.png",1.2,Z_LAYER_HEAD,true,BulletType::Lightening);
        return res;
    }else if (i == 2)
    {
        MonsterPart* res = new PreciseShootHead();
        res->init(parent,layer,HEAD_POS[order],"head-wave.png",3.2,Z_LAYER_HEAD,true,BulletType::Wave);
        return res;
    }else if (i == 3)
    {
        MonsterPart* res = new PreciseShootHead();
        res->init(parent,layer,HEAD_POS[order],"head-rock.png",7,Z_LAYER_HEAD,true,BulletType::Rock);
        return res;
    }else if (i == 4)
    {
        MonsterPart* res = new HeartHead();
        res->init(parent,layer,HEAD_POS[order],"head-heart.png",6.5+rand_0_1()*0.5,Z_LAYER_HEAD,true,BulletType::Wave);
        return res;
    }else if (i == 5)
    {
        MonsterPart* res = new HideHead();
        res->init(parent,layer,HEAD_POS[order],"head-hide.png",5+rand_0_1()*0.5,Z_LAYER_HEAD,true,BulletType::Wave);
        return res;
    }else if (i == 6)
    {
        MonsterPart* res = new BlockHead();
        res->init(parent,layer,HEAD_POS[order],"head-sheild.png",9999,Z_LAYER_HEAD,true,BulletType::Wave);
        return res;
    }else if (i == 7)
    {
        MonsterPart* res = new JumpHead();
        res->init(parent,layer,HEAD_POS[order],"head-jump.png",4.5+rand_0_1()*0.5,Z_LAYER_HEAD,true,BulletType::Wave);
        return res;
    }
}

MonsterPart* PartFactory::getRandomBody(Monster* parent, cocos2d::Layer* layer)
{
    int i = rand() % 2;
    if (i == 0)
    {
        Body* res = new Body();
        res->init(parent,layer,Vec2::ZERO,"body-circle.png",2,Z_LAYER_BODY,false);
        MonsterInfo info;
        info.health = 200;
        info.speed = 1;
        res->adjustMonsterInfo(info);
        return (MonsterPart*)res;
    }else
    if (i == 1)
    {
        Body* res = new Body();
        res->init(parent,layer,Vec2::ZERO,"body-rectangle.png",2,Z_LAYER_BODY,false);
        MonsterInfo info;
        info.health = 200;
        info.speed = 1;
        res->adjustMonsterInfo(info);
        return (MonsterPart*)res;
    }
    return NULL;
}

MonsterPart* PartFactory::getRandomWing(Monster* parent, cocos2d::Layer* layer)
{
//    int i = rand() % 2;
//    if (i == 0)
//    {
//        MonsterPart* res = new Wing();
//        res->init(parent,layer,WING_POS,"wing1.png",1,Z_LAYER_WING,true);
//        return res;
//    }else if (i == 1)
//    {
//        MonsterPart* res = new Wing();
//        res->init(parent,layer,WING_POS,"wing2.png",2.2,Z_LAYER_WING,true);
//        return res;
//    }
    return NULL;
}

MonsterPart* PartFactory::getRandomLeg(Monster* parent, cocos2d::Layer* layer)
{
//    int i = rand() % 2;
//    if (i == 0)
//    {
//        MonsterPart* res = new Leg();
//        res->init(parent,layer,LEG_POS,"foot1.png",1,Z_LAYER_LEG,true);
//        return res;
//    }else if (i == 1)
//    {
//        MonsterPart* res = new Leg();
//        res->init(parent,layer,LEG_POS,"foot2.png",2.2,Z_LAYER_LEG,true);
//        return res;
//    }
    return NULL;
}