#include <Geode/Geode.hpp>
#include "render.hpp"
#include <include/cef_app.h>

using namespace geode::prelude;

CCTexture2D* create_texture_rgb(const void* data, unsigned int width, unsigned int height) {
    auto* ret = new (std::nothrow) CCTexture2D;
    if (ret && ret->initWithData(data, kCCTexture2DPixelFormat_RGBA8888, width, height, CCSize(width, height))) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

class BrowserNode : public CCSprite {
public:
    static BrowserNode* create() {
        auto* ret = new (std::nothrow) BrowserNode;
        if (ret && ret->init()) {
            ret->autorelease();
        } else {
            delete ret;
            ret = nullptr;
        }
        return ret;
    }

    bool init() override {
        if (!CCSprite::init()) {
            return false;
        }

        this->scheduleUpdate();

        log::info("gd thread id is: {}", std::this_thread::get_id());

        frameHandler() = [this](const void* buffer, int width, int height) {
            auto* texture = create_texture_rgb(buffer, width, height);
            if (!texture) return;
            this->setTexture(texture);
            auto factor = CCDirector::sharedDirector()->getContentScaleFactor();
            this->setTextureRect(CCRect(0.f, 0.f, static_cast<float>(width) / factor, static_cast<float>(height) / factor));
        };

        return true;
    }

    virtual ~BrowserNode() {
        frameHandler() = [](auto...){};
    }

    void update(float) override {
        CefDoMessageLoopWork();
    }
};

#include <Geode/modify/MenuLayer.hpp>
class $modify(MenuLayer) {
	void onMoreGames(CCObject*) {
		initBrowser();
        auto* node = BrowserNode::create();
        node->setZOrder(90);
        node->setPosition({200, 200});
        this->addChild(node);
	} 
};
