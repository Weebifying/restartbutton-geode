#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/loader/SettingEvent.hpp>
using namespace geode::prelude;


class $modify(AltMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto winSize = CCDirector::get()->getWinSize();

		#if defined(GEODE_IS_ANDROID)
			auto res_menu = CCMenu::create();
			res_menu->setID("close-menu");
			res_menu->setContentSize(CCSize(200, 33.25));
			res_menu->ignoreAnchorPointForPosition(false);
			this->addChild(res_menu);

			auto cls_spr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
			cls_spr->setScale(0.7);
			auto cls_btn = CCMenuItemSpriteExtra::create(
				cls_spr, 
				this, 
				menu_selector(MenuLayer::onQuit));
			cls_btn->setContentSize(CCSize(32.2, 33.25));
			cls_btn->setPosition(16.1, 16.625);
			res_menu->addChild(cls_btn);
		#else
			auto res_menu = this->getChildByID("close-menu");
		#endif

		res_menu->setAnchorPoint(CCPoint(0, 1));
		res_menu->setPosition(winSize.width/300.f, winSize.height/0.995703125f);

		auto res_spr = CCSprite::createWithSpriteFrameName("GJ_updateBtn_001.png");
		res_spr->setScale(0.7);
		auto res_btn = CCMenuItemSpriteExtra::create(
			res_spr, 
			this, 
			menu_selector(AltMenuLayer::onRestart));
		res_btn->setContentSize(CCSize(32.2, 33.25));
		res_btn->setPosition(16.1, -19.375);
		res_menu->addChild(res_btn);

		auto scale = Mod::get()->getSettingValue<double>("size");
		res_menu->setScale(scale);

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
