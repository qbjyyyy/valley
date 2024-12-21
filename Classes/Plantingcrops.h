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

    // ��ȡ�����״̬
    State getState() const;

    // ��ȡ�����λ��
    Vec2 getposition() const;

    // �ջ�����
    void harvest();
};

#endif // __CROP_H__