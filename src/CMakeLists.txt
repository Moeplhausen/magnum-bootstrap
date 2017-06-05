find_package(Magnum REQUIRED
        SceneGraph
        Shaders
        MeshTools
        Primitives
        Sdl2Application)

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)


set(SOURCE_FILES
        MyApplication.cpp
        Types.cpp
        3dObjects/RectangleObject.cpp
        3dObjects/Sphere.cpp)

add_executable(WebGlResourceManager ${SOURCE_FILES})
target_link_libraries(WebGlResourceManager
        Magnum::Application
        Magnum::Magnum
        Magnum::SceneGraph
        Magnum::Shaders
        Magnum::Primitives
        Magnum::MeshTools)

if(CORRADE_TARGET_EMSCRIPTEN)
    install(TARGETS WebGlResourceManager DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/WebGLResourceManager.js.mem DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
    install(FILES MyApplication.html EmscriptenApplication.js WebApplication.css DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()
