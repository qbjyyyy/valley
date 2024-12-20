// GameTimeSystem.cpp
#include "GameTimeSystem.h"
#include <chrono>

using namespace std::chrono;

GameTimeSystem* GameTimeSystem::_instance = nullptr;

GameTimeSystem* GameTimeSystem::getInstance()
{
    if (!_instance)
    {
        _instance = new (std::nothrow) GameTimeSystem();
        if (_instance && _instance->init())
        {
            _instance->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(_instance);
        }
    }
    return _instance;
}

bool GameTimeSystem::init()
{
    _startTime = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    return true;
}

GameTimeSystem::GameTimeSystem()
{
    // 构造函数
}

GameTimeSystem::~GameTimeSystem()
{
    // 析构函数
}

long GameTimeSystem::getElapsedTime()
{
    auto now = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    return now - _startTime;
}
