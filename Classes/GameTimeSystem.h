// GameTimeSystem.h
#ifndef GAMETIME_SYSTEM_H
#define GAMETIME_SYSTEM_H

#include "cocos2d.h"

class GameTimeSystem : public cocos2d::Ref
{
public:
    static GameTimeSystem* getInstance();
    virtual bool init();
    long getElapsedTime();
private:
    GameTimeSystem();
    virtual ~GameTimeSystem();
    static GameTimeSystem* _instance;

    long _startTime; // ��Ϸ��ʼ��ʱ��
};

#endif // GAMETIME_SYSTEM_H
