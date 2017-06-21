find_package(Magnum REQUIRED
        SceneGraph
        Shaders
        Text
        MeshTools
        Primitives
        Sdl2Application)

if(CORRADE_TARGET_EMSCRIPTEN)
    find_package(MagnumPlugins REQUIRED StbTrueTypeFont)
    #    find_package(Magnum REQUIRED TgaImporter)
endif()


set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

corrade_add_resource(TransGUI_RESOURCES resources/GUIResources.conf)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/configure.h.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/configure.h)

set(SOURCE_FILES
        MyApplication.cpp
        Types.cpp
        3dObjects/RectangleObject.cpp
        3dObjects/Sphere.cpp)

add_executable(WebGlResourceManager ${SOURCE_FILES} ${TransGUI_RESOURCES})
target_link_libraries(WebGlResourceManager
        Magnum::Application
        Magnum::Magnum
        Magnum::SceneGraph
        Magnum::Shaders
        Magnum::Text
        Magnum::Primitives
        Magnum::MeshTools)

if(CORRADE_TARGET_EMSCRIPTEN)
    target_link_libraries(WebGlResourceManager
            MagnumPlugins::StbTrueTypeFont
            )
endif()


if(CORRADE_TARGET_EMSCRIPTEN)
    install(TARGETS WebGlResourceManager DESTINATION ${CMAKE_INSTALL_PREFIX})
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/WebGLResourceManager.js.mem DESTINATION ${CMAKE_INSTALL_PREFIX} OPTIONAL)
    install(FILES MyApplication.html EmscriptenApplication.js WebApplication.css DESTINATION ${CMAKE_INSTALL_PREFIX})
endif()
