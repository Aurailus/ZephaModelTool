//
// Created by aurailus on 2020-05-28.
//

#include "App.h"

App::App() :
    window(),
    camera(&window),
    renderer(&window, &camera),
    input(window.getInput()),

    controller(input, camera),
    blockManager(&camera, &window) {

    while (!window.shouldEnd()) {
        update();
        render();
    }
}

void App::update() {
    window.update();
    controller.update();
    blockManager.update(input, controller);
}

void App::render() {
    renderer.reset();
    blockManager.render(renderer);
    renderer.swap();
}
