#include <Geode/Geode.hpp>
#include "view.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {
        auto* node = WebView::create();
        node->setPosition(CCDirector::get()->getWinSize() / 2.f);
        node->loadURL("https://example.com");
        this->addChild(node);
	} 
};
