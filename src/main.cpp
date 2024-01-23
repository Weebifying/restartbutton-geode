#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;


class $modify(AltMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::get()->getWinSize();

		auto res_menu = CCMenu::create();
		res_menu->setPosition(0, 0);
		this->addChild(res_menu);

		auto spr = CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png");
		spr->setScale(0.7);
		auto res_btn = CCMenuItemSpriteExtra::create(
			spr, 
			this, 
			menu_selector(AltMenuLayer::onRestart));
		res_btn->setContentSize(CCSize(32.2, 33.25));
		res_btn->setPosition(18, winSize.height - 54);
		res_menu->addChild(res_btn);

		return true;
	}

	void onRestart(CCObject* sender) {
		geode::createQuickPopup(
			"Restart Game",
			"Are you sure you want to <cr>restart</c>?",
			"Cancel", "Yes",
			[](auto, bool btn2) {
				if (btn2) {
					utils::game::restart();
				}
			}
		);

	}
};
