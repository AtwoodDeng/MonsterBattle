//
//  Global.cpp
//  Monster
//
//  Created by Atwood on 16-2-15.
//
//

#include <stdio.h>
#include "Global.h"

float randFloat(float min,float max)
{
    float x = min + (float)rand()/((float)RAND_MAX/(max-min));
    return x;
}

Vec2 randVec2()
{
    Vec2 res =Vec2(random(-1,1),random(-1, 1));
    res.normalize();
    return res;
}

cocos2d::Color3B player2Color(int player)
{
    switch (player) {
        case 0:
            return Color3B(255, 50 , 50);
            break;
        case 1:
            return Color3B(50, 255 , 50);
            break;
        case 2:
            return Color3B(50, 50 , 255);
            break;
        case 3:
            return Color3B(255, 255 , 50);
            break;
        default:
            break;
    }
    return Color3B(50, 50 , 50);
}


cocos2d::Vec2 player2arrowPos(int player,Size visibleSize)
{
    
    switch (player) {
        case 0:
            return Vec2(50, 50);
            break;
        case 1:
            return Vec2(visibleSize.width-50,50);
            break;
        case 2:
            return Vec2(visibleSize.width-50,visibleSize.height-50);
            break;
        case 3:
            return Vec2(50,visibleSize.height - 50);
            break;
        default:
            break;
    }
    return Vec2::ZERO;
}