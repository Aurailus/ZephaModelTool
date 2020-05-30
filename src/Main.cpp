//
// Created by aurailus on 2020-05-28.
//

#include <iostream>

#include "App.h"

int main(int argc, char* argv[]) {
    try {
        App();
        return 0;
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}