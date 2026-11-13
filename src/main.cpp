#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

static bool isReload = false;

// --------------------------------------------------
// RESTART
// --------------------------------------------------

void restart() {
    auto scene = CCDirector::get()->getRunningScene();
    if (!scene) return;

    if (
        scene->getChildByID("restart-popup") ||
        scene->getChildByID("reload-popup")
    ) return;

    geode::createQuickPopup(
        "Restart Game",
        "Are you sure you want to <cg>restart</c>?",
        "Cancel",
        "Yes",
        [](auto, bool btn2) {
            if (btn2) {
                utils::game::restart(true);
            }
        }
    )->setID("restart-popup");
}

// --------------------------------------------------
// RELOAD TEXTURES
// --------------------------------------------------

void reload() {
    auto scene = CCDirector::get()->getRunningScene();
    if (!scene) return;

    if (
        scene->getChildByID("restart-popup") ||
        scene->getChildByID("reload-popup")
    ) return;

    geode::createQuickPopup(
        "Reload Textures",
        "Are you sure you want to <cj>reload textures</c>?",
        "Cancel",
        "Yes",
        [](auto, bool btn2) {
            if (btn2) {
                isReload = true;
                GameManager::get()->reloadAll(false, false, true);
            }
        }
    )->setID("reload-popup");
}

// --------------------------------------------------
// MENU LAYER
// --------------------------------------------------

class $modify(AltMenuLayer, MenuLayer) {

    static CCScene* scene(bool p0) {
        if (!isReload) {
            return MenuLayer::scene(p0);
        }

        isReload = false;
        return MenuLayer::scene(false);
    }

    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto winSize = CCDirector::get()->getWinSize();

        // Create button container
        auto menu = this->getChildByID("close-menu");

        if (!menu) {
            menu = CCMenu::create();
            menu->setID("close-menu");
            menu->setContentSize({33.25f, 200.f});
            menu->ignoreAnchorPointForPosition(false);
            this->addChild(menu);
        }

        menu->setAnchorPoint({0.f, 1.f});

        menu->setPosition(
            winSize.width / 300.f,
            winSize.height - winSize.width / 300.f
        );

        auto layout = ColumnLayout::create()
            ->setAxisReverse(true)
            ->setAxisAlignment(AxisAlignment::End)
            ->setGap(4.f)
            ->setCrossAxisOverflow(false);

        menu->setLayout(layout);

        // ------------------------------------------
        // EXIT BUTTON
        // ------------------------------------------

        if (Mod::get()->getSettingValue<bool>("exit")) {

            if (!menu->getChildByID("close-button")) {
                auto sprite =
                    CCSprite::createWithSpriteFrameName(
                        "GJ_closeBtn_001.png"
                    );

                sprite->setScale(0.7f);

                auto button = CCMenuItemSpriteExtra::create(
                    sprite,
                    this,
                    menu_selector(MenuLayer::onQuit)
                );

                button->setID("close-button");
                menu->addChild(button);
            }

        } else {
            menu->removeChildByID("close-button");
        }

        // ------------------------------------------
        // RESTART BUTTON
        // ------------------------------------------

        if (Mod::get()->getSettingValue<bool>("restart")) {

            if (!menu->getChildByID("restart-button")) {
                auto sprite =
                    CCSprite::createWithSpriteFrameName(
                        "GJ_updateBtn_001.png"
                    );

                sprite->setScale(0.7f);

                auto button = CCMenuItemSpriteExtra::create(
                    sprite,
                    this,
                    menu_selector(AltMenuLayer::onRestart)
                );

                button->setID("restart-button");
                menu->addChild(button);
            }

        } else {
            menu->removeChildByID("restart-button");
        }

        // ------------------------------------------
        // RELOAD TEXTURES BUTTON
        // ------------------------------------------

        if (Mod::get()->getSettingValue<bool>("reload-textures")) {

            if (!menu->getChildByID("reload-button")) {
                auto sprite =
                    CCSprite::createWithSpriteFrameName(
                        "GJ_replayBtn_001.png"
                    );

                sprite->setScale(0.525f);

                auto button = CCMenuItemSpriteExtra::create(
                    sprite,
                    this,
                    menu_selector(AltMenuLayer::onReload)
                );

                button->setID("reload-button");
                menu->addChild(button);
            }

        } else {
            menu->removeChildByID("reload-button");
        }

        // ------------------------------------------
        // SIZE
        // ------------------------------------------

        auto scale =
            Mod::get()->getSettingValue<double>("size");

        menu->setScale(static_cast<float>(scale));
        menu->updateLayout();

        return true;
    }

    // ----------------------------------------------
    // BUTTON CALLBACKS
    // ----------------------------------------------

    void onRestart(CCObject*) {
        restart();
    }

    void onReload(CCObject*) {
        reload();
    }
};

// --------------------------------------------------
// KEYBINDS
// --------------------------------------------------

$on_game(Loaded) {

    // Restart keybind
    listenForKeybindSettingPresses(
        "restart-keybind",
        [](Keybind const& keybind, bool down, bool repeat, double timestamp) {

            auto scene = CCDirector::get()->getRunningScene();
            if (!scene) return;

            bool anywhere =
                Mod::get()->getSettingValue<bool>("keybind_anywhere");

            bool allowed = anywhere
                ? LevelEditorLayer::get() == nullptr
                : scene->getChildByID("MenuLayer") != nullptr;

            if (allowed && down && !repeat) {
                restart();
            }
        }
    );

    // Reload textures keybind
    listenForKeybindSettingPresses(
        "reload-keybind",
        [](Keybind const& keybind, bool down, bool repeat, double timestamp) {

            auto scene = CCDirector::get()->getRunningScene();
            if (!scene) return;

            bool anywhere =
                Mod::get()->getSettingValue<bool>("keybind_anywhere");

            bool allowed = anywhere
                ? LevelEditorLayer::get() == nullptr
                : scene->getChildByID("MenuLayer") != nullptr;

            if (allowed && down && !repeat) {
                reload();
            }
        }
    );
}
