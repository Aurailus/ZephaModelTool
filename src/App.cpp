//
// Created by aurailus on 2020-05-28.
//

#include "App.h"

App::App() :
    window(),
    camera(&window),
    renderer(&window, &camera),

    blockManager(&camera, &window),

    input(window.getInput()),
    controller(input, window, camera, blockManager) {

    while (!window.shouldEnd()) {
        update();
        render();
    }
}

void App::update() {
    window.update();
    controller.update();
}

void App::render() {
    renderer.reset();
    blockManager.render(renderer);
    renderer.swap();
}
