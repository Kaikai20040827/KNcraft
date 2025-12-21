#include "app.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

int main()
{
    Minecraft app;
    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        // also write to log for headless runs
        std::ofstream log("app_error.log", std::ios::app);
        if (log)
            log << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
