# opengl
find_package(OpenGL REQUIRED)


# glm
add_subdirectory(glm)

# glfw
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)
add_subdirectory(glfw)
# 编译的时候自动链接opengl

# Assimp
set(BUILD_SHARED_LIBS OFF)
if(APPLE)
    set(BUILD_FRAMEWORK ON)
endif()
set(ASSIMP_DOUBLE_PRECISION ON)
set(ASSIMP_BUILD_TESTS OFF)
set(INJECT_DEBUG_POSTFIX ON)
set(ASSIMP_INSTALL_PDB ON)
add_subdirectory(assimp)


# stb
file(GLOB stb_sources CONFIGURE_DEPENDS  "${CMAKE_CURRENT_SOURCE_DIR}/stb/*.h")
add_library(stb INTERFACE ${stb_sources})
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/stb)




# imgui
set(imgui_SOURCE_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

file(GLOB imgui_sources CONFIGURE_DEPENDS  "${imgui_SOURCE_DIR_}/*.cpp")
file(GLOB imgui_impl CONFIGURE_DEPENDS  
"${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.cpp" 
"${imgui_SOURCE_DIR_}/backends/imgui_impl_glfw.h"
"${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.cpp" 
"${imgui_SOURCE_DIR_}/backends/imgui_impl_opengl3.h")
add_library(imgui STATIC ${imgui_sources} ${imgui_impl})
target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${imgui_SOURCE_DIR_}>)
target_include_directories(imgui PUBLIC $<BUILD_INTERFACE:${OPENGL_INCLUDE_DIR}>)
target_link_libraries(imgui PUBLIC glfw ${OPENGL_LIBRARIES})




# glad
set(glad_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set(glad_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad/src)
list(APPEND include_dir "${glad_include_dir}")
file(GLOB_RECURSE glad_headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glad/*.h")
file(GLOB_RECURSE glad_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/glad/*.c")
add_library(glad STATIC ${glad_headers} ${glad_sources})
target_include_directories(glad PUBLIC ${glad_src_dir} ${glad_include_dir})


# 导出
target_link_libraries(glad PUBLIC glfw glm stb imgui assimp)