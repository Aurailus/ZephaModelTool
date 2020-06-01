set(MODELLER_SRC
        graph/Renderer.cpp graph/Renderer.h App.cpp App.h graph/Window.cpp graph/Window.h graph/Shader.cpp graph/Shader.h graph/Camera.h graph/Camera.cpp graph/Mesh.inl graph/Mesh.h graph/Vertex.h graph/Texture.h graph/Texture.cpp input/ViewportControl.cpp input/ViewportControl.h input/Input.cpp input/Input.h)
add_library(${MAIN_LIB_NAME} ${MODELLER_SRC})