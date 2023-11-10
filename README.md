# gd-webview

99.9% code copied from https://github.com/axmolengine/axmol/blob/dev/core/ui/UIWebView/UIWebViewImpl-win32.cpp, but changed to make work with our cocos.

The way it works is it makes a subwindow, since webview2 can't actually render off-screen. This means that the webview is *always* on top of everything ingame, and that it **won't** work in fullscreen.

set it up by downloading webview2:
```powershell
mkdir webview2
curl -sSL "https://www.nuget.org/api/v2/package/Microsoft.Web.WebView2" | tar -xf - -C webview2
```