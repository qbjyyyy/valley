#ifndef _OUTSIDE_H_
#define _OUTSIDE_H_
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"

class outside : public cocos2d::Layer
{
public:
    //static cocos2d::Scene* createoutsideScene();
    virtual bool init();
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event, cocos2d::TMXTiledMap* tiledMap);
 
    void setViewPointCenter(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap);
    void setPlayerPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap);
    cocos2d::Point tileCoordForPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap);

    static cocos2d::Scene* createSceneWithMapIndex(int mapIndex);
    void loadMapBackground(int mapIndex);

    void onTouchEndedWrapper(cocos2d::Touch* touch, cocos2d::Event* event) {
        onTouchEnded(touch, event, tiledMap_);
    }

    outside() {
        // 初始化游戏开始时间
        gameStartTime = std::chrono::high_resolution_clock::now();
        gameTime = 0; // 游戏开始时，游戏内时间为0
    }


    void updateTime(float dt);
    void iniData(cocos2d::TMXTiledMap* map, cocos2d::Sprite* player);

    void update(float delta, cocos2d::Sprite* _player);
    void changeScene();

    // 显示竖排按钮
    void showVerticalButtons();

    // 移除竖排按钮
    void removeVerticalButtons();

    // 显示新窗口
    void showNewWindow();

    // 键盘指定方法
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 展示个人界面
    void showPersonalInterface();

    // 关闭个人界面
    void closePersonalInterface(Ref* sender);

    // 选择图像
    void selectImage(int index);

    // 切换图像
    void switchImage(int direction);


    CREATE_FUNC(outside);
private:
    //cocos2d::TMXTiledMap* _tiledmap;
    cocos2d::TMXLayer* _background;
    cocos2d::Sprite* _player;
    cocos2d::TMXLayer* _meta;
    cocos2d::TMXLayer* _foreground;
    cocos2d::TMXTiledMap* tiledMap_;
    cocos2d::ui::ImageView* fishImage;
    cocos2d::Sprite* fishman;
    cocos2d::Sprite* spriteFish;
    //cocos2d::TMXTiledMap* tiledMap = nullptr;
    bool _isfishingVisible;
    cocos2d::Rect targetArea;
    cocos2d::Sprite* _lastSprite = nullptr;
    cocos2d::MenuItemImage* _closeButton;   // 关闭按钮
    std::chrono::high_resolution_clock::time_point gameStartTime; // 游戏开始时间
    int gameTime; // 游戏内的时间（以分钟为单位）

    // 用于存储竖排按钮的层
    cocos2d::Layer * _verticalButtonLayer;

    cocos2d::Layer* _personalInterfaceLayer; // 个人界面层
    cocos2d::Sprite* _menuWindow;           // 菜单窗口
    bool _isPersonalInterfaceVisible;      // 跟踪个人界面是否可见
    int _currentImageIndex;                // 当前图像索引
    int _selectedButtonIndex;              // 选择按钮索引

    
};
#endif // !_HELLOWORLD_SCENE_H_