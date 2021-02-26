add_executable(opengl
    opengl/buffer_attribute.cpp
    opengl/buffer_attribute.h
    opengl/buffer_layout.cpp
    opengl/buffer_layout.h
    opengl/data_type.h
    opengl/element_buffer.cpp
    opengl/element_buffer.h
    opengl/shader.cpp
    opengl/shader.h
    opengl/texture.cpp
    opengl/texture.h
    opengl/vertex_array.cpp
    opengl/vertex_array.h
    opengl/vertex_buffer.cpp
    opengl/vertex_buffer.h
    camera.cpp
    camera.h
    camera_movement.h
    entity.cpp
    entity.h
    glad.c
    main.cpp
    material.cpp
    material.h
    model.cpp
    model.h
    model_loader.cpp
    model_loader.h
    renderer.cpp
    renderer.h
    stb_image.cpp
    stb_image.h
    texture_cache.cpp
    texture_cache.h)
target_compile_features(opengl PRIVATE cxx_std_17)
set_target_properties(opengl PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(opengl PRIVATE glfw)
target_include_directories(opengl PRIVATE
    "${PROJECT_SOURCE_DIR}/extern/glad/include"
    "${PROJECT_SOURCE_DIR}/extern/glfw/include"
    "${PROJECT_SOURCE_DIR}/extern/glm")
