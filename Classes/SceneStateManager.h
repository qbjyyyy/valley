#ifndef _SCENESTATEMANAGER_H_
#define _SCENESTATEMANAGER_H_

#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;
// 定义一个单例类，用于保存场景状态
class SceneStateManager {
public:
    static SceneStateManager* getInstance() {
        static SceneStateManager instance;
        return &instance;
    }

    void saveSceneState(const Vec2& characterPosition, const std::string& mapName) {
        _characterPosition = characterPosition;
        _mapName = mapName;
    }

    Vec2 getCharacterPosition() const {
        return _characterPosition;
    }

    std::string getMapName() const {
        return _mapName;
    }

private:
    Vec2 _characterPosition;
    std::string _mapName;
};

#endif // !_SCENESTATEMANAGER.H