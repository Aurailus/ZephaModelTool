set(MODELLER_SRC
        Renderer.cpp Renderer.h App.cpp App.h Window.cpp Window.h Shader.cpp Shader.h Camera.h Camera.cpp Mesh.inl Mesh.h Vertex.cpp Vertex.h)
add_library(${MAIN_LIB_NAME} ${MODELLER_SRC})