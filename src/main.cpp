#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/MenuLayer.hpp>

// Icon & Color Unlock
class $modify(UnlockGM, GameManager) {
    bool isIconUnlocked(int id, IconType type) {
        if (GameManager::isIconUnlocked(id, type)) return true;
        return id > 0;
    }
    
    bool isColorUnlocked(int id, UnlockType type) {
        if (GameManager::isColorUnlocked(id, type)) return true;
        return true;
    }
};

// Actually unlock everything on startup
class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;
        
        auto gm = GameManager::get();
        
        // Unlock all icons using public methods
        for (int i = 1; i <= 500; i++) {
            gm->unlockIcon(i, IconType::Cube);
        }
        for (int i = 1; i <= 169; i++) {
            gm->unlockIcon(i, IconType::Ship);
        }
        for (int i = 1; i <= 118; i++) {
            gm->unlockIcon(i, IconType::Ball);
        }
        for (int i = 1; i <= 149; i++) {
            gm->unlockIcon(i, IconType::Ufo);
        }
        for (int i = 1; i <= 96; i++) {
            gm->unlockIcon(i, IconType::Wave);
        }
        for (int i = 1; i <= 68; i++) {
            gm->unlockIcon(i, IconType::Robot);
        }
        for (int i = 1; i <= 69; i++) {
            gm->unlockIcon(i, IconType::Spider);
        }
        for (int i = 1; i <= 43; i++) {
            gm->unlockIcon(i, IconType::Swing);
        }
        
        // Unlock all colors
        for (int i = 0; i <= 105; i++) {
            gm->unlockColor(i, UnlockType::Col1);
            gm->unlockColor(i, UnlockType::Col2);
        }
        
        return true;
    }
};

// Practice Music Unlock
class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int id) {
        if (GameStatsManager::isItemUnlocked(type, id)) return true;
        
        if (type == UnlockType::GJItem && id >= 17 && id <= 20) {
            return true;
        }
        
        return false;
    }
};
