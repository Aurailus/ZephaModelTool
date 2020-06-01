//
// Created by aurailus on 2020-05-28.
//

#include "App.h"

App::App() :
    window(),
    camera(window.getSize()),
    renderer(&window, &camera),
    input(window.getInput()),

    controller(input, camera),
    test({
        {{-30, -20, -20}, {0, 0}, {0, 0, 0}},
        {{-30,  20, -20}, {0, 1}, {0, 0, 0}},
        {{-30,  20,  20}, {1, 1}, {0, 0, 0}},
        {{-30, -20,  20}, {1, 0}, {0, 0, 0}},
    }, {0, 3, 2, 2, 1, 0}),
    test2({
        {{30, -20, -20}, {0, 0}, {0, 0, 0}},
        {{30,  20, -20}, {0, 1}, {0, 0, 0}},
        {{30,  20,  20}, {1, 1}, {0, 0, 0}},
        {{30, -20,  20}, {1, 0}, {0, 0, 0}},
    }, {0, 3, 2, 2, 1, 0}),
    tex("../assets/textures/dirt.png") {

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

    glm::mat4 model = glm::mat4(1.0);
    tex.use(0);
    renderer.setModelMatrix(model);
    test.draw();
    test2.draw();

    renderer.swap();
}
