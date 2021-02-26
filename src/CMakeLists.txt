add_executable(opengl
    glad.c
    stb_image.cpp
    stb_image.h
    main.cpp)
target_compile_features(opengl PRIVATE cxx_std_17)
set_target_properties(opengl PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(opengl PRIVATE glfw)
target_include_directories(opengl PRIVATE
    "${PROJECT_SOURCE_DIR}/extern/glad/include"
    "${PROJECT_SOURCE_DIR}/extern/glfw/include"
    "${PROJECT_SOURCE_DIR}/extern/glm")
