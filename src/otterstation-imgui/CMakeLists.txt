set(SOURCES
    imgui/imconfig.h
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imfilebrowser.h
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_internal.h
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_opengl3.h
    imgui/imgui_impl_sdl.cpp
    imgui/imgui_impl_sdl.h
    main.cpp
    host_interface.cpp
    debugger/ee.cpp
    debugger/iop.cpp
)

add_executable(otterstation ${SOURCES})

find_package(SDL2 REQUIRED)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)
target_link_libraries(otterstation ${OPENGL_LIBRARIES})

include_directories(imgui ${SDL2_INCLUDE_DIRS})
target_link_libraries(otterstation core common ${SDL2_LIBRARIES})

find_package(Threads REQUIRED)
find_package(X11 REQUIRED)

target_link_libraries(otterstation ${CMAKE_THREAD_LIBS_INIT} ${X11_LIBRARIES} ${CMAKE_DL_LIBS})