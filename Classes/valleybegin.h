#ifndef _HELLOWORLD_SCENE_H_
#define _HELLOWORLD_SCENE_H_
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"

class valleybegin : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createvalleybeginScene();

    virtual bool init();
    //游戏开始
    void valleybegin::Startgame(Ref* obj);

    //游戏结束
    void valleybegin::Endgame(Ref* obj);

    int gettimebool();
    CREATE_FUNC(valleybegin);
    
    bool timerunning;
private:

};
#endif // !_HELLOWORLD_SCENE_H_