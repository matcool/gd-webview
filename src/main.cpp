#include <Geode/Geode.hpp>
#include "view.hpp"

using namespace geode::prelude;

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer) {
    void onMoreGames(CCObject*) {
        auto* node = WebView::create();
        node->loadURL("https://example.com");
        auto winSize = CCDirector::get()->getWinSize();
        node->setPosition(winSize / 2.f);
        node->setContentSize({winSize.width / 2.f, winSize.height});
        this->addChild(node);
    } 
};
