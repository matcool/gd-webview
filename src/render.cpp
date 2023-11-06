#include <include/cef_render_handler.h>
#include <include/cef_client.h>
#include <include/cef_app.h>

#include "render.hpp"
#include <Geode/loader/Log.hpp>

std::function<void(const void*, int, int)>& frameHandler() {
    static std::function<void(const void*, int, int)> handler = [](auto...){};
    return handler;
}

class MyRender : public CefRenderHandler {
public:
    MyRender() {}

    void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override {
        rect = CefRect(0, 0, 1280, 720);
    }

    virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects,
        const void* buffer, int width, int height) override {
        // yeah
        frameHandler()(buffer, width, height);
    }

    IMPLEMENT_REFCOUNTING(MyRender);
};

class BrowserClient : public CefClient, public CefLifeSpanHandler, public CefLoadHandler {
public:
    BrowserClient(MyRender* renderHandler)
        : m_renderHandler(renderHandler) {}

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override {
        return this;
    }

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() {
        return m_renderHandler;
    }

    CefRefPtr<CefRenderHandler> m_renderHandler;

    IMPLEMENT_REFCOUNTING(BrowserClient);
};

struct BrowserView {
    CefRefPtr<CefBrowser> m_browser;
    CefRefPtr<BrowserClient> m_client;
    MyRender* m_renderHandler = nullptr;

    BrowserView() {
        CefWindowInfo windowInfo;
        windowInfo.SetAsWindowless(nullptr);

        m_renderHandler = new MyRender();
        
        CefBrowserSettings browserSettings;
        browserSettings.windowless_frame_rate = 30;

        m_client = new BrowserClient(m_renderHandler);
        m_browser = CefBrowserHost::CreateBrowserSync(windowInfo, m_client.get(), "https://google.com", browserSettings, nullptr, nullptr);
    }

    ~BrowserView() {
        CefDoMessageLoopWork();
        m_browser->GetHost()->CloseBrowser(true);
    }
};

bool initialized = false;
std::shared_ptr<BrowserView> view;

void initBrowser() {
    if (initialized) return;
    initialized = true;

    CefMainArgs args;
    (void) CefExecuteProcess(args, nullptr, nullptr);

    CefSettings settings;
    settings.windowless_rendering_enabled = true;
    settings.no_sandbox = true;
    CefString(&settings.browser_subprocess_path) = "C:\\Users\\Mateus\\Desktop\\coding\\geode\\webview\\build\\RelWithDebInfo\\stupidprocess.exe";

    (void) CefInitialize(args, settings, nullptr, nullptr);

    view = std::make_shared<BrowserView>();
}
