#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/MenuLayer.hpp>

// Unlock practice music sync
class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int id) {
        if (type == UnlockType::GJItem && id == 17) {
            return true;
        }
        return GameStatsManager::isItemUnlocked(type, id);
    }
};

// Unlock all icons and colors
class $modify(SimpleUnlockGM, GameManager) {
    bool isIconUnlocked(int id, IconType type) {
        if (GameManager::isIconUnlocked(id, type)) return true;
        return id > 0;
    }
    
    bool isColorUnlocked(int id, UnlockType type) {
        if (GameManager::isColorUnlocked(id, type)) return true;
        return true;
    }
    
    // Intercept icon selection to persist choices
    void setPlayerFrame(int id) {
        GameManager::setPlayerFrame(id);
        Mod::get()->setSavedValue("icon.cube", id);
    }
    
    void setPlayerShip(int id) {
        GameManager::setPlayerShip(id);
        Mod::get()->setSavedValue("icon.ship", id);
    }
    
    void setPlayerBall(int id) {
        GameManager::setPlayerBall(id);
        Mod::get()->setSavedValue("icon.ball", id);
    }
    
    void setPlayerBird(int id) {
        GameManager::setPlayerBird(id);
        Mod::get()->setSavedValue("icon.ufo", id);
    }
    
    void setPlayerDart(int id) {
        GameManager::setPlayerDart(id);
        Mod::get()->setSavedValue("icon.wave", id);
    }
    
    void setPlayerRobot(int id) {
        GameManager::setPlayerRobot(id);
        Mod::get()->setSavedValue("icon.robot", id);
    }
    
    void setPlayerSpider(int id) {
        GameManager::setPlayerSpider(id);
        Mod::get()->setSavedValue("icon.spider", id);
    }
    
    void setPlayerSwing(int id) {
        GameManager::setPlayerSwing(id);
        Mod::get()->setSavedValue("icon.swing", id);
    }
    
    void setPlayerColor(int id) {
        GameManager::setPlayerColor(id);
        Mod::get()->setSavedValue("color.primary", id);
    }
    
    void setPlayerColor2(int id) {
        GameManager::setPlayerColor2(id);
        Mod::get()->setSavedValue("color.secondary", id);
    }
    
    void setPlayerGlowColor(int id) {
        GameManager::setPlayerGlowColor(id);
        Mod::get()->setSavedValue("color.glow", id);
    }
};

// Restore saved selections on startup
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        
        auto gm = GameManager::get();
        auto mod = Mod::get();
        
        // Restore icons
        if (auto val = mod->getSavedValue<int>("icon.cube")) gm->setPlayerFrame(val.value());
        if (auto val = mod->getSavedValue<int>("icon.ship")) gm->setPlayerShip(val.value());
        if (auto val = mod->getSavedValue<int>("icon.ball")) gm->setPlayerBall(val.value());
        if (auto val = mod->getSavedValue<int>("icon.ufo")) gm->setPlayerBird(val.value());
        if (auto val = mod->getSavedValue<int>("icon.wave")) gm->setPlayerDart(val.value());
        if (auto val = mod->getSavedValue<int>("icon.robot")) gm->setPlayerRobot(val.value());
        if (auto val = mod->getSavedValue<int>("icon.spider")) gm->setPlayerSpider(val.value());
        if (auto val = mod->getSavedValue<int>("icon.swing")) gm->setPlayerSwing(val.value());
        
        // Restore colors
        if (auto val = mod->getSavedValue<int>("color.primary")) gm->setPlayerColor(val.value());
        if (auto val = mod->getSavedValue<int>("color.secondary")) gm->setPlayerColor2(val.value());
        if (auto val = mod->getSavedValue<int>("color.glow")) gm->setPlayerGlowColor(val.value());
        
        return true;
    }
};
