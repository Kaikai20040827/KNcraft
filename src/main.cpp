#include "app/app.h"
#include "core/debug/debug.h"

#include <iostream>
#include <fstream>

int main()
{
    LOG_PLAN(10000000);

    LOG("main begin");
    App app("KNCraft");
    LOG("App constructed");

    app.run();
    LOG("app.run() returned");

    LOG("main end");
    return 0;
}
