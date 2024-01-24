#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;


class $modify(AltMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::get()->getWinSize();

		auto res_menu = this->getChildByID("close-menu");

		auto spr = CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png");
		spr->setScale(0.7);
		auto res_btn = CCMenuItemSpriteExtra::create(
			spr, 
			this, 
			menu_selector(AltMenuLayer::onRestart));
		res_btn->setContentSize(CCSize(32.2, 33.25));
		res_btn->setPosition(16.1, -19.375);
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
