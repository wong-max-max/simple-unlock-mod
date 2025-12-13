#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/GameManager.hpp>

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
    
    // Hook the save function to mark icons as actually unlocked
    void encodeDataTo(DS_Dictionary* dict) {
        // First, mark all icons as unlocked in the manager's state
        // This makes GD think you legitimately own them
        
        // Unlock all cubes (1-484+)
        for (int i = 1; i <= 500; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Cube)].insert(i);
        }
        
        // Unlock all ships
        for (int i = 1; i <= 169; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Ship)].insert(i);
        }
        
        // Unlock all balls
        for (int i = 1; i <= 118; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Ball)].insert(i);
        }
        
        // Unlock all UFOs
        for (int i = 1; i <= 149; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Ufo)].insert(i);
        }
        
        // Unlock all waves
        for (int i = 1; i <= 96; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Wave)].insert(i);
        }
        
        // Unlock all robots
        for (int i = 1; i <= 68; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Robot)].insert(i);
        }
        
        // Unlock all spiders
        for (int i = 1; i <= 69; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Spider)].insert(i);
        }
        
        // Unlock all swings
        for (int i = 1; i <= 43; i++) {
            m_unlockedIcons[static_cast<int>(IconType::Swing)].insert(i);
        }
        
        // Unlock all colors
        for (int i = 0; i <= 105; i++) {
            m_unlockedIcons[static_cast<int>(UnlockType::Col1)].insert(i);
            m_unlockedIcons[static_cast<int>(UnlockType::Col2)].insert(i);
        }
        
        // Now save with all icons marked as unlocked
        GameManager::encodeDataTo(dict);
    }
};

// Practice Music Unlock
class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int id) {
        if (GameStatsManager::isItemUnlocked(type, id)) return true;
        
        // Unlock practice music sync (17) and items 18-20
        if (type == UnlockType::GJItem && id >= 17 && id <= 20) {
            return true;
        }
        
        return false;
    }
};
