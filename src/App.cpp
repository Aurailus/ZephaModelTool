//
// Created by aurailus on 2020-05-28.
//

#include "App.h"

App::App() :
    window(),
    camera(window.getSize()),
    renderer(&window, &camera) {

    while (!window.shouldEnd()) {
        update();
        render();
    }
}

void App::update() {

}

void App::render() {
    renderer.reset();



    renderer.swap();
}
