#include <Geode/Geode.hpp>
#include "view.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {
		auto* node = WebView::create();
		// node->loadURL("https://example.com");
		node->loadHTMLString("<h1> hello world!</h1>");
		auto winSize = CCDirector::get()->getWinSize();
		node->setPosition(winSize / 2.f);
		node->setContentSize({winSize.width / 2.f, winSize.height - 50.f});
		this->addChild(node);
	} 
};
