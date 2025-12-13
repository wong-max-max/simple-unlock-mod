#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/GameManager.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

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

// Unlock Shops, Vaults, Paths, Practice Music, etc.
class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType type, int id) {
        if (GameStatsManager::isItemUnlocked(type, id)) return true;
        
        if (type == UnlockType::GJItem) {
            // Practice music sync (17) and items 18-20
            if (id >= 17 && id <= 20) return true;
        }
        
        return false;
    }
    
    // Unlock shops, vaults, and paths
    int getStat(char const* stat) {
        int ret = GameStatsManager::getStat(stat);
        int statInt = std::stoi(stat);
        
        // Main levels (unlock shops)
        if (statInt == 8) return 30;
        
        // Vault of Secrets (unlock vault)
        if (statInt == 12) return 50;
        
        // Paths unlocked (stars)
        if (statInt == 6) return 200;
        
        // Demons unlocked
        if (statInt == 5) return 30;
        
        return ret;
    }
};

// Accurate Percentage (3 decimals) + Auto Save
class $modify(AccuratePctPL, PlayLayer) {
    struct Fields {
        CCLabelBMFont* percentLabel = nullptr;
    };
    
    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        
        // Find the percent label by searching children
        m_fields->percentLabel = nullptr;
        for (int i = 0; i < this->getChildrenCount(); i++) {
            auto child = this->getChildren()->objectAtIndex(i);
            if (auto label = typeinfo_cast<CCLabelBMFont*>(child)) {
                std::string text = label->getString();
                if (text.find("%") != std::string::npos) {
                    m_fields->percentLabel = label;
                    break;
                }
            }
        }
        
        return true;
    }
    
    void updateProgressbar() {
        PlayLayer::updateProgressbar();
        
        if (m_fields->percentLabel) {
            // Get current percentage
            float percent = PlayLayer::getCurrentPercent();
            
            // Format with 3 decimal places
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%.3f%%", percent);
            m_fields->percentLabel->setString(buffer);
        }
    }
    
    void levelComplete() {
        PlayLayer::levelComplete();
        GameManager::get()->save();
    }
    
    void onQuit() {
        GameManager::get()->save();
        PlayLayer::onQuit();
    }
};
