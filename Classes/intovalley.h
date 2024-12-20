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
    void update(float delta);

    CREATE_FUNC(intovalley);
    //进入下一个游戏界面
    void intovalley::outdoor(Ref* obj);
    void startTimer();
    virtual void timeupdate(float dt);
private:
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    cocos2d::Label* timelable;
};
#endif // !_INTOVALLEY.H


