//
//  BasicBullet.cpp
//  Monster
//
//  Created by Atwood on 16-2-17.
//
//

#include "BasicBullet.h"
#include "SimpleAudioEngine.h"



void FireBullet::init(Damage _d, Monster * _p, MonsterPart* _part, cocos2d::Layer *layer, std::string spriteName, float _speed)
{
    Bullet::init(_d, _p, _part, layer, spriteName, _speed);
    dmgValue = dmg.value;
}


void FireBullet::update(float delta)
{
    if (ifDead)
        return;
    
    timer += delta;
    
    pos += direction * speed * ( 0.05 + timer / 2);
    
    if (timer < 3 )
    {
        dmg.value = dmgValue * ( 1 / 3 + timer / 3 * 2/3);
        sprite->setScale(dmg.value/18 * 5);
        
    }
    sprite->setPosition(pos);
    
    if (pos.x > parent->visibleSize.width + SPACE_BOUNDARY
        || pos.x < 0 - SPACE_BOUNDARY
        || pos.y > parent->visibleSize.height + SPACE_BOUNDARY
        || pos.y < 0 - SPACE_BOUNDARY)
        expode();

}

void LightningBullet::update(float delta)
{
    
    if (ifDead)
        return;
    sprite->setPosition((part->getSprite()->getPosition()+parent->enermy->GetPosition())/2);
    Vec2 toEnermy = parent->enermy->GetPosition() - part->getSprite()->getPosition();
    sprite->setRotation(toEnermy.getAngle(Vec2(0,1))*180/3.14159);
    sprite->setScale(toEnermy.length() / 600);
}

void LightningBullet::init(Damage _d, Monster * _p, MonsterPart* _part, cocos2d::Layer *layer, std::string spriteName, float _speed)
{
    dmg = _d;
    parent = _p;
    direction = _part->getBulletDierection();
    direction.normalize();
    speed = _speed;
    part = _part;
    
    pos = part->getSprite()->getPosition();
    sprite = Sprite::create(spriteName);
    
    if (parent->enermy == NULL)
        parent->enermy = parent;
    sprite->setPosition((part->getSprite()->getPosition()+parent->enermy->GetPosition())/2);
    Vec2 toEnermy = parent->enermy->GetPosition() - part->getSprite()->getPosition();
    sprite->setRotation(toEnermy.getAngle(Vec2(0,1))*180/3.14159);
    sprite->setScale(toEnermy.length() / 700, toEnermy.length() / 700);
    sprite->setOpacity(0);
    
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
    
    //set animation
    auto out = FadeOut::create(0.03);
    auto delay = DelayTime::create(0.1);
    auto in = FadeIn::create(0.03);
    auto final = CallFunc::create(CC_CALLBACK_0(Bullet::expode,this));
    auto sequence =Sequence::create(in,delay,out,final, NULL);
    sprite->runAction(sequence);
    
    UserData* data = new UserData();
    data->bullet = this;
    sprite->setUserData((void*)data);
    sprite->setPhysicsBody(physicsBody);
    
    parent->push_back_bullet(this);
}

void WaveBullet::init(Damage _d, Monster * _p, MonsterPart* _part, cocos2d::Layer *layer, std::string spriteName, float _speed)
{
    Bullet::init(_d, _p, _part, layer, spriteName, _speed);
    direction += randVec2() * 0.3;
    speed *= 1 + randFloat(-0.3, 0.3);
    direction.normalize();
}

void RockBullet::init(Damage _d, Monster * _p, MonsterPart* _part, cocos2d::Layer *layer, std::string spriteName, float _speed)
{
    log("speed %f" , _speed);
    Bullet::init(_d, _p, _part, layer, spriteName, _speed);
    sprite->runAction(RotateBy::create(10, 720));
}

Bullet* BulletFactory::createBullet(Monster* monster, MonsterPart* part , BulletType type)
{
    Bullet* bullet=NULL;
    Damage dmg;
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    switch (type) {
        case BulletType::FireB :
            
            audio->playEffect("fire.mp3");
            
            bullet = new FireBullet();
            dmg.value = 10 + randFloat(0, 12);
            dmg.type = DamgeType::FireD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-fire.png", 20);
            break;
        case BulletType::Lightening :
            audio->playEffect("electricity.mp3");
            
            bullet = new LightningBullet();
            dmg.value = 2;
            dmg.type = DamgeType::LightD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-lightning.png", 0);
            
            break;
        case BulletType::Wave:
            audio->playEffect("wave.mp3");
            
            bullet = new WaveBullet();
            dmg.value = 4;
            dmg.type = DamgeType::WaveD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-wave.png", 10);
            bullet = new WaveBullet();
            dmg.value = 3;
            dmg.type = DamgeType::WaveD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-wave.png", 13);
            bullet = new WaveBullet();
            dmg.value = 4;
            dmg.type = DamgeType::WaveD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-wave.png", 16);
            bullet = new WaveBullet();
            dmg.value = 3;
            dmg.type = DamgeType::WaveD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-wave.png", 20);
            bullet = new WaveBullet();
            dmg.value = 3;
            dmg.type = DamgeType::WaveD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-wave.png", 25);
            bullet = new WaveBullet();
            
            break;
        case BulletType::Rock :
            audio->playEffect("rock.mp3");
            
            bullet = new RockBullet();
            dmg.value = 11;
            dmg.type = DamgeType::RockD;
            bullet->init(dmg, monster, part, monster->layer, "bullet-rock.png", 8);
            
            break;
            
        default:
            break;
    }
    return bullet;
}