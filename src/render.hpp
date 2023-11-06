#pragma once

#include <functional>

std::function<void(const void*, int, int)>& frameHandler();
void initBrowser();