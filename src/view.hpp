#pragma once

#include <Geode/Geode.hpp>

using namespace cocos2d;

class WebViewImpl;

class WebView : public CCNode {
public:
    /**
     * Allocates and initializes a WebView.
     */
    static WebView* create();

    /**
     * Set javascript interface scheme.
     *
     * @see WebView::setOnJSCallback()
     */
    void setJavascriptInterfaceScheme(std::string_view scheme);

    // /**
    //  * Sets the main page contents, MIME type, content encoding, and base URL.
    //  *
    //  * @param data The content for the main page.
    //  * @param MIMEType The MIME type of the data.
    //  * @param encoding The encoding of the data.
    //  * @param baseURL The base URL for the content.
    //  */
    // void loadData(const ax::Data& data,
    //               std::string_view MIMEType,
    //               std::string_view encoding,
    //               std::string_view baseURL);

    /**
     * Sets the main page content and base URL.
     *
     * @param string The content for the main page.
     * @param baseURL The base URL for the content.
     */
    void loadHTMLString(std::string_view string, std::string_view baseURL = "");

    /**
     * Loads the given URL. It doesn't clean cached data.
     *
     * @param url Content URL.
     */
    void loadURL(std::string_view url);

    /**
     * Loads the given URL with cleaning cached data or not.
     * @param url Content URL.
     * @cleanCachedData Whether to clean cached data.
     */
    void loadURL(std::string_view url, bool cleanCachedData);

    /**
     * Loads the given fileName.
     *
     * @param fileName Content fileName.
     */
    void loadFile(std::string_view fileName);

    /**
     * Stops the current load.
     */
    void stopLoading();

    /**
     * Reloads the current URL.
     */
    void reload();

    /**
     * Gets whether this WebView has a back history item.
     *
     * @return WebView has a back history item.
     */
    bool canGoBack();

    /**
     * Gets whether this WebView has a forward history item.
     *
     * @return WebView has a forward history item.
     */
    bool canGoForward();

    /**
     * Goes back in the history.
     */
    void goBack();

    /**
     * Goes forward in the history.
     */
    void goForward();

    /**
     * Evaluates JavaScript in the context of the currently displayed page.
     */
    void evaluateJS(std::string_view js);

    /**
     * Set WebView should support zooming. The default value is false.
     */
    void setScalesPageToFit(const bool scalesPageToFit);

    /**
     * Call before a web view begins loading.
     *
     * @param callback The web view that is about to load new content.
     * @return YES if the web view should begin loading content; otherwise, NO.
     */
    void setOnShouldStartLoading(const std::function<bool(WebView* sender, std::string_view url)>& callback);

    /**
     * A callback which will be called when a WebView event happens.
     */
    typedef std::function<void(WebView* sender, std::string_view url)> ccWebViewCallback;

    /**
     * Call after a web view finishes loading.
     *
     * @param callback The web view that has finished loading.
     */
    void setOnDidFinishLoading(const ccWebViewCallback& callback);

    /**
     * Call if a web view failed to load content.
     *
     * @param callback The web view that has failed loading.
     */
    void setOnDidFailLoading(const ccWebViewCallback& callback);

    /**
     * This callback called when load URL that start with javascript interface scheme.
     */
    void setOnJSCallback(const ccWebViewCallback& callback);

    /**
     * Get the callback when WebView is about to start.
     */
    std::function<bool(WebView* sender, std::string_view url)> getOnShouldStartLoading() const;

    /**
     * Get the callback when WebView has finished loading.
     */
    ccWebViewCallback getOnDidFinishLoading() const;

    /**
     * Get the callback when WebView has failed loading.
     */
    ccWebViewCallback getOnDidFailLoading() const;

    /**
     *Get the Javascript callback.
     */
    ccWebViewCallback getOnJSCallback() const;

    /**
     * Set whether the webview bounces at end of scroll of WebView.
     */
    void setBounces(bool bounce);

    // virtual void draw(ax::Renderer* renderer, ax::Mat4 const& transform, uint32_t flags) override;
    virtual void draw() override;

    /**
     * Toggle visibility of WebView.
     */
    virtual void setVisible(bool visible) override;
    /**
     * SetOpacity of webview.
     */
    virtual void setOpacityWebView(float opacity);

    /**
     * getOpacity of webview.
     */
    virtual float getOpacityWebView() const;

    /**
     * set the background transparent
     */
    virtual void setBackgroundTransparent();
    virtual void onEnter() override;
    virtual void onExit() override;

    /**
     * Default constructor.
     */
    WebView();
    virtual ~WebView();

protected:
    std::function<bool(WebView* sender, std::string_view url)> _onShouldStartLoading = nullptr;
    ccWebViewCallback _onDidFinishLoading                                            = nullptr;
    ccWebViewCallback _onDidFailLoading                                              = nullptr;
    ccWebViewCallback _onJSCallback                                                  = nullptr;

private:
    WebViewImpl* _impl = nullptr;
    friend class WebViewImpl;
};