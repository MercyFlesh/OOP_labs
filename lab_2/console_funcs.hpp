#pragma once
#include <iostream>

namespace cls {
    void clear_console()
    {
    #if defined(_WIN32)
        std::system("cls");

    #else
        std::system("clear");
    #endif
    }


    void pause_output_console()
    {
        char ch = getchar();
        while ((ch = getchar()) != EOF && ch != '\n');
    }
}
