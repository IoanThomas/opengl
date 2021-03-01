set(SOURCE_FILES
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
    entity.cpp
    entity.h
    entity_renderer.cpp
    entity_renderer.h
    glad.c
    main.cpp
    material.cpp
    material.h
    model.cpp
    model.h
    model_cache.cpp
    model_cache.h
    renderer.h
    scene.cpp
    scene.h
    stb_image.cpp
    stb_image.h
    texture_cache.cpp
    texture_cache.h)

add_executable(opengl ${SOURCE_FILES})
target_compile_features(opengl PRIVATE cxx_std_17)
set_target_properties(opengl
    PROPERTIES
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/"
        VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:opengl>")
target_link_libraries(opengl PRIVATE glfw)
target_include_directories(opengl PRIVATE
    "${PROJECT_SOURCE_DIR}/extern/glad/include"
    "${PROJECT_SOURCE_DIR}/extern/glfw/include"
    "${PROJECT_SOURCE_DIR}/extern/glm")

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT opengl)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

add_custom_command(TARGET opengl POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/data/"
        "$<TARGET_FILE_DIR:opengl>/data/")
