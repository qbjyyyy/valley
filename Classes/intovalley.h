#ifndef _INTOVALLEY_H
#define _INTOVALLEY_H
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "outside.h"
#include "valleybegin.h"


class intovalley : public cocos2d::Layer
{
public:
    friend class valleybegin;
    static cocos2d::Scene* createintovalleyScene();
    virtual bool init();

    CREATE_FUNC(intovalley);
    //进入下一个游戏界面
private:
    CharacterWithTools* characteraction;
};
#endif // !_INTOVALLEY.H


