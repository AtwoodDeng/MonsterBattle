//
//  Monster.cpp
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#include <stdio.h>
#include "Monster.h"
#include "Global.h"
#include "BasicPart.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

void Monster::m_init(cocos2d::Layer* _layer,int player)
{
    layer = _layer;
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    groupSign = Sprite::create("groupBack.png");
    groupSign->setOpacity(125);
    groupSign->setScale(2.5);
    layer->addChild(groupSign );
    
    
    this->color = player2Color(player);
    groupSign->setColor(color);
    
    
    if (player == 0)
    {
        bodyCategory = PhysicsCategory::MonsterA;
        bulletCategory = PhysicsCategory::MonsterA;
        pos.x = visibleSize.width / 3 + origin.x;
        pos.y = visibleSize.height / 2 + origin.y;
        
    }else if (player == 1)
    {
        bodyCategory = PhysicsCategory::MonsterA;
        bulletCategory = PhysicsCategory::MonsterA;
        pos.x = visibleSize.width / 3 * 2 + origin.x;
        pos.y = visibleSize.height / 2 + origin.y;
        
    }else if (player == 2)
    {
        bodyCategory = PhysicsCategory::MonsterA;
        bulletCategory = PhysicsCategory::MonsterA;
        pos.x = visibleSize.width / 2 + origin.x;
        pos.y = visibleSize.height / 3 + origin.y;
        
    }else if (player == 3)
    {
        bodyCategory = PhysicsCategory::MonsterA;
        bulletCategory = PhysicsCategory::MonsterA;
        pos.x = visibleSize.width / 2 + origin.x;
        pos.y = visibleSize.height / 3 * 2 + origin.y;
    }
    groupSign->setPosition(pos);
    
    
    ///////////////
    /// set up the body
    //////////////
    MonsterPart* bodyPart = PartFactory::getRandomBody(this, layer);
    sprite = bodyPart->getSprite();
    sprite->setPosition(pos);
    
    healthBar = Sprite::create("healthBar.png");
    healthBar->setPosition(pos+HEALTH_BAR_OFFSET);
    layer->addChild(healthBar, 50);
    
     //set up the physics
   //  1
    auto monsterSize = sprite->getContentSize();
    body = PhysicsBody::createBox(Size(monsterSize.width , monsterSize.height),PhysicsMaterial(0.1f, 1.0f, 0.0f));
    // 2
    body->setDynamic(true);
    // 3
    body->setCategoryBitmask(PhysicsCategory::MonsterA);
    body->setCollisionBitmask((int)PhysicsCategory::MonsterA);
    body->setContactTestBitmask((int)(PhysicsCategory::Projectile|PhysicsCategory::Part));
    
    UserData* data = new UserData();
    data->monster = this;
    sprite->setUserData((void*)data);
    sprite->setPhysicsBody(body);
    
    
    vel = randVec2() * 5;
    
    //////////////
    // set up other part of the body
    /////////////
//    MonsterPart* head = PartFactory::getRandomHead(this, layer);
//    parts.push_back(head);
//    MonsterPart* wing = PartFactory::getRandomWing(this, layer);
//    parts.push_back(wing);
//    MonsterPart* leg = PartFactory::getRandomLeg(this, layer);
//    parts.push_back(leg);
    
    for ( int i = 0 ; i < INIT_PARTS ; ++ i )
        addPart(PartFactory::getRandomHead(this, layer, rand()%4));
    
    
    // create arrow
    arrow = Sprite::create("arrow.png");
    layer->addChild(arrow,Z_LAYER_ARROW);
    arrow->setPosition(pos);
    arrow->setScale(0);
    arrow->setColor(color);
    
    
    // set up health
    health = info.health;
    state = MonsterState::ALIVE;
    updateHealthBar();
}

void Monster::ChangeIntense()
{
    circleIntense =randFloat(0.3, 0.8);
    innerIntense =randFloat(2000, 4000);
}

void Monster::m_update(float delta)
{
    for (int i= 0 ; i < bullets.size(); i++) {
        bullets[i]->update(delta);
    }
    
    
    if (state == MonsterState::DIED || state == MonsterState::NONE)
        return;
    
    pos = sprite->getPosition();
    
    //force toward center
    Vec2 toCenter = - pos + Vec2(visibleSize.width/2,visibleSize.height/2);
//    vel += intense * innerIntense * toCenter;
    Vec2 forceRotate = toCenter;
    forceRotate.rotate(Vec2::ZERO, 90);
    vel += circleIntense * forceRotate;
    
//    float innerIntense = toCenter.length();
//
//    vel +=
    
    //set random shaking
//    pos.x = pos.x + randFloat(-1, 1);
//    pos.y = pos.y + randFloat(-1, 1);
    vel += randVec2() * MONSTER_SPEED_MAX / 7;
    
    if ( vel.length() > MONSTER_SPEED_MAX)
    {
        vel.normalize();
        vel = vel * MONSTER_SPEED_MAX;
    }else if (vel.length() < MONSTER_SPEED_MAX / 5)
    {
        vel.normalize();
        vel = vel * MONSTER_SPEED_MAX / 5 ;
    }
    
    pos += vel * info.speed;
    
    //set boundary
    if (pos.x > visibleSize.width - SPACE_BOUNDARY + origin.x)
    {
        pos.x = visibleSize.width - SPACE_BOUNDARY+ origin.x;
        vel.x = -vel.x;
    }
    if (pos.x < SPACE_BOUNDARY+ origin.x )
    {
        pos.x = SPACE_BOUNDARY+ origin.x;
        vel.x = - vel.x;
    }
    if (pos.y > visibleSize.height - SPACE_BOUNDARY + origin.y )
    {
        pos.y = visibleSize.height - SPACE_BOUNDARY + origin.y;
        vel.y = -vel.y;
    }
    if (pos.y < SPACE_BOUNDARY + origin.y)
    {
        pos.y = SPACE_BOUNDARY + origin.y;
        vel.y = - vel.y;
    }
    
    
    sprite->setPosition(pos);
    groupSign->setPosition(pos);
    updateHealthBar();
    
    
    // update arrow
    Vec2 toEnermy = enermy->GetPosition() - GetPosition();
    arrow->setRotation(toEnermy.getAngle(Vec2(0,1)) * 180/3.14159);
    float arrowScale =toEnermy.length()/visibleSize.width;
    if (arrowScale > 1 ) arrowScale = 1;
    if (arrowScale < 0.5 ) arrowScale = 0.5;
    arrow->setPosition(GetPosition());
    arrow->setScale(arrowScale * 3);
    
    
    
    for (int i = 0 ; i < parts.size() && i < TOTAL_PARTS; i++) {
        parts[i]->setLocalPos(HEAD_POS[i]);
        parts[i]->update(delta);
    }
    
}

void Monster::Do(cocos2d::Action *action)
{
    sprite->runAction(action);
}

Vec2 Monster::GetPosition()
{
    return sprite->getPosition();
}

void Monster::hurtBy(Bullet* bullet)
{
    if (state == MonsterState::DIED || state == MonsterState::NONE)
        return;
    
    if (bullet->getSender() != this)
    {
        // check block
        if (rand_0_1() < info.blockChance)
        {
            Sprite* block = Sprite::create("block.png");
            block->setPosition(GetPosition());
            block->setScale(0);
            block->runAction(ScaleTo::create(0.5, 1));
            block->runAction(Sequence::create(FadeIn::create(0.15),DelayTime::create(0.3), FadeOut::create(0.15),NULL));
            layer->addChild(block,40);
        }else
        {
        MoveBy* moveBy = MoveBy::create(0.2, bullet->getSpeed() * bullet->getDamgage().value );
        sprite->runAction(moveBy);
    
        if (bullet->getDamgage().type == DamgeType::RockD)
        {
            // do not expode
            
            MoveBy* moveBy = MoveBy::create(0.2, randVec2() * 50 );
            sprite->runAction(moveBy);
        }
        else
        {
            bullet->expode();
        }
        
        hurt(bullet->getDamgage());
        
            
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            audio->playEffect("hurt.mp3");
            
            std::string bloods[] = {"blood1.png","blood2.png","blood3.png"};
            Sprite* blood = Sprite::create(bloods[rand()%3]);
            blood->setPosition(pos);
            blood->setOpacity(50);
            blood->setColor(color);
            blood->setScale(bullet->getDamgage().value / 10 * randFloat(0.5, 2));
            layer->addChild(blood);
        
        
        // change the enermy
        if (bullet->getSender() != NULL)
            enermy = bullet->getSender();
        
        // randomly drop part of the body
        if (  rand_0_1() < PART_DROP_POSS * bullet->getDamgage().value / info.health * ( parts.size() * parts.size() / 10 + 1 ) )
        {
            dropPart();
        }
        }
        
    }
}

void Monster::hurt(Damage dmg)
{
    health -= dmg.value;
    if (health < 0 )
        dead();
}

void Monster::dead()
{
    for(int i = 0 ; i < TOTAL_PARTS ; ++ i )
        dropPart();
    updateHealthBar();
    state = MonsterState::DIED;
}

void Monster::push_back_bullet(Bullet *b)
{
    bullets.push_back(b);
}

void Monster::erase(Bullet *b)
{
    for (int i= 0 ; i < bullets.size(); i++) {
        if (bullets[i] == b)
        {
            bullets.erase(bullets.begin()+i);
            break;
        }
    }
}

void Monster::updateHealthBar()
{
    if (health < 0)
        healthBar->setScale(0, 0.4);
    else
        healthBar->setScale(health/40, 0.4);
    
    healthBar->setPosition(pos+HEALTH_BAR_OFFSET);
}

Vec2 Monster::getRelatedPos(cocos2d::Vec2 localPos)
{
    float angle = sprite->getRotation();
    Vec2 temPos = localPos + GetPosition();
    temPos.rotate(GetPosition(), - angle / 180 * 3.14159);
    return temPos;
}

float Monster::getRotation()
{
    return sprite->getRotation();
}

int Monster::getHeadOrder()
{
    return parts.size();
}

bool Monster::addPart(MonsterPart *part)
{
    if (part == NULL)
        return false;
    if (getHeadOrder()>=TOTAL_PARTS)
        return false;
    part->setPartent(this);
    parts.push_back(part);
    return true;
}

void Monster::dropPart()
{
    if (parts.size() < 1 )
        return;
    
    int drop = rand() % parts.size();
    parts[drop]->unlink();
    parts[drop]->getSprite()->runAction(MoveBy::create(0.25 + randFloat(0, 0.25), randVec2() * randFloat(120, 280)));
    parts[drop]->getSprite()->runAction(RotateBy::create(0.3, randFloat(0, 1080)));
    parts.erase(parts.begin()+ drop);
    
}
Monster::Monster()
{
}

Monster::~Monster()
{
    
}