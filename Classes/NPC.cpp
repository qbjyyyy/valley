#include "NPC.h"

NPC::NPC() : dialogIndex(0) {}

NPC::~NPC() {}

bool NPC::init(const std::string& spriteFile, const NPCType& _npctype)
{
    if (!Sprite::initWithFile(spriteFile)) {
        return false;
    }

    npctype = _npctype;

    switch (npctype) {
        case NPCType::NPC1:
            dialog = NPC1_DIALOG; // 使用类成员
            break;
        case NPCType::NPC2:
            dialog = NPC2_DIALOG; // 使用类成员
            break;
        case NPCType::NPC3:
            dialog = NPC3_DIALOG; // 使用类成员
            break;
        default:
            break;
    }

    return true;
}

NPC* NPC::create(const std::string& spriteFile, const NPCType& _npctype)
{
    NPC* npc = new(std::nothrow) NPC();
    if (npc && npc->init(spriteFile, _npctype)) {
        npc->autorelease();
        return npc;
    }
    else {
        delete npc;
        return nullptr;
    }
}

std::string NPC::getDialog() const
{
    if (dialogIndex < dialog.size()) {
        return dialog[dialogIndex];
    }
    else {
        CCLOG("对话结束！");
        return "";
    }
}

void NPC::advanceDialog()
{
    if (dialogIndex < dialog.size() - 1) {
        dialogIndex++;
    }
    else {
        CCLOG("对话结束！");
    }
}

void NPC::jumpToDialog(int index)
{
    if (index >= 0 && index < dialog.size()) {
        dialogIndex = index;
    }
    else {
        CCLOG("无效的对话索引！");
    }
}
