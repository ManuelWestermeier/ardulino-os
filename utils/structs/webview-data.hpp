#pragma once

#include "./mwpl.hpp"

struct WebviewData
{
    char lastScreenData[19][3];
    String title;
    MWPL mwpl;

    WebviewData() {}

    WebviewData(const String &url)
    {
        mwpl = MWPL(url);
        title = url;
    }
};