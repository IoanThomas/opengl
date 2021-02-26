add_executable(opengl
    main.cpp)
target_compile_features(opengl PRIVATE cxx_std_17)
set_target_properties(opengl PROPERTIES CXX_EXTENSIONS OFF)
