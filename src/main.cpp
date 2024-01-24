#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/platform/platform.hpp>
using namespace geode::prelude;


class $modify(AltMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::get()->getWinSize();	

		auto res_menu = this->getChildByID("close-menu");

		auto res_spr = CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png");
		res_spr->setScale(0.7);
		auto res_btn = CCMenuItemSpriteExtra::create(
			res_spr, 
			this, 
			menu_selector(AltMenuLayer::onRestart));
		res_btn->setContentSize(CCSize(32.2, 33.25));
		res_btn->setPosition(16.1, -19.375);
		res_menu->addChild(res_btn);

		#ifdef GEODE_IS_ANDROID
			auto cls_spr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
			cls_spr->setScale(0.7);
			auto cls_btn = CCMenuItemSpriteExtra::create(
				cls_spr, 
				this, 
				menu_selector(MenuLayer::onQuit));
			cls_btn->setContentSize(CCSize(32.2, 33.25));
			cls_btn->setPosition(16.1, 16.625);
			cls_menu->addChild(cls_btn);
		#endif

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
