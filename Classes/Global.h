//
//  Global.h
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#ifndef Monster_Global_h
#define Monster_Global_h

USING_NS_CC;


static const float SPACE_BOUNDARY = 150;

static const EventKeyboard::KeyCode PLAYER_A_KEY = EventKeyboard::KeyCode::KEY_LEFT_ALT;
static const EventKeyboard::KeyCode PLAYER_B_KEY = EventKeyboard::KeyCode::KEY_RIGHT_ALT;
static const EventKeyboard::KeyCode PLAYER_C_KEY = EventKeyboard::KeyCode::KEY_H;
static const EventKeyboard::KeyCode PLAYER_D_KEY = EventKeyboard::KeyCode::KEY_G;
static const EventKeyboard::KeyCode PLAYER_A_SHOOT_KEY = EventKeyboard::KeyCode::KEY_LEFT_SHIFT;
static const EventKeyboard::KeyCode PLAYER_B_SHOOT_KEY = EventKeyboard::KeyCode::KEY_RIGHT_SHIFT;

static const EventKeyboard::KeyCode START_KEY = EventKeyboard::KeyCode::KEY_SPACE;

static const int Z_LAYER_HEAD = 10;
static const int Z_LAYER_BODY = 5;
static const int Z_LAYER_WING = 1;
static const int Z_LAYER_LEG = 8;
static const int Z_LAYER_ARROW = 0;

static const float SHOOT_INTERVAL = 1;


static const float ARROW_TURN_RANGE = 40;
static const float ARROW_TRUN_SPEED = 15;
static const float ARROW_SCALE_SPEED = 4;

static const float MONSTER_SPEED_MAX = 4;

static const float PART_DROP_POSS = 4;

static const float POINT_READY_TIME = 3.7;

float randFloat(float min,float max);
Vec2  randVec2();
cocos2d::Color3B player2Color(int player);
cocos2d::Vec2 player2arrowPos(int player);
static const int TOTAL_PLAYERS = 2;


static const float PART_OFFSET = 40;
static const int INIT_PARTS = 3;
static const int TOTAL_PARTS = 9;
static const Vec2 HEAD_POS[] = { Vec2(0,PART_OFFSET), Vec2(PART_OFFSET,0), Vec2(0,-PART_OFFSET), Vec2(-PART_OFFSET,0) , Vec2(PART_OFFSET,PART_OFFSET) , Vec2(-PART_OFFSET,PART_OFFSET),Vec2(PART_OFFSET,-PART_OFFSET), Vec2(-PART_OFFSET,-PART_OFFSET), Vec2(0,0) };
static const Vec2 WING_POS = Vec2(0,0);
static const Vec2 LEG_POS = Vec2(0,-40);
static const Vec2 HEALTH_BAR_OFFSET = Vec2(0,100);

enum DamgeType{FireD,WaveD,LightD,RockD};

enum MonsterState{ NONE, ALIVE, DIED };

struct Damage
{
public:
        float value;
        DamgeType type;
};

enum PhysicsCategory {
        None = 0,
        MonsterA = (1 << 0),    // 1
        MonsterB = (1 << 1),    // 2
        Monsters = (int)MonsterA | (int)MonsterB, // 3
        Projectile = (1 << 2),  // 4
        Part = (1<<3),          // 8
        World = 0xFFFFFFFFFF,
};


enum BulletType
{
    FireB,
    Lightening,
    Wave,
    Rock
};


#include "Bullet.h"
#include "Monster.h"
#include "MonsterPart.h"

class Monster;
class Bullet;
class MonsterPart;

class UserData
{
public:
    Monster* monster;
    Bullet* bullet;
    MonsterPart* part;
    
    UserData(){monster=NULL;bullet=NULL;part=NULL;}
};

#endif
