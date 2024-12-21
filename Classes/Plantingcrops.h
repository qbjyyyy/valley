#pragma once


#ifndef __CROP_H__
#define __CROP_H__

#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "menu.h"
#include "characterAciton.h"


USING_NS_CC;

enum class State {
    seed,
    growing,
    matured,
    harvested
};
class Crop :public Sprite {
protected:
    State state;
    double growthTime;
    double matureTime;
public:
    virtual bool init(const std::string& filename);
    static Crop* created(const std::string& filename);
    Crop();
    ~Crop() {};
    void update(float delta);

    // 获取作物的状态
    State getState() const;

    // 获取作物的位置
    Vec2 getposition() const;

    // 收获作物
    void harvest();
};

#endif // __CROP_H__